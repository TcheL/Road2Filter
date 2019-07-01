/*
 *                            COPYRIGHT
 *
 *  rffr - calculates the frequency response of a recursive filter.
 *  Copyright (C) 2003, 2004, 2005 Exstrom Laboratories LLC
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  A copy of the GNU General Public License is available on the internet at:
 *
 *  http://www.gnu.org/copyleft/gpl.html
 *
 *  or you can write to:
 *
 *  The Free Software Foundation, Inc.
 *  675 Mass Ave
 *  Cambridge, MA 02139, USA
 *
 *  You can contact Exstrom Laboratories LLC via Email at:
 *
 *  info(AT)exstrom.com
 *
 *  or you can write to:
 *
 *  Exstrom Laboratories LLC
 *  P.O. Box 7651
 *  Longmont, CO 80501, USA
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAXLINESIZE 128

void FFT( double *c, int N, int isign );

int main( int argc, char *argv[] )
{
  FILE *fp;
  char linebuff[MAXLINESIZE];
  int i;
  int np; /* number of FFT points */
  int nc; /* number of c coefficients in input file */
  int nd; /* number of d coefficients in input file */
  double *c; /* where c coefficients are stored, and where its FFT is stored */
  double *d; /* where d coefficients are stored, and where its FFT is stored */
  double mc, pc; /* magnitude & phase of ck coeff */
  double md, pd; /* magnitude & phase of dk coeff */

  if( argc < 4 )
  {
    printf("\n rffr stands for 'recursive filter frequency response'.\n");
    printf(" This program will read a file containing the filter coefficients\n");
    printf(" of a recursive filter, putting the ck's in one array,\n");
    printf(" and the dk's in another array, each of size np, that is\n");
    printf(" padded with zeros. The FFT of each array is then taken.\n");
    printf(" The FFT's are divided, ci(omega)/di(omega), then the result\n");
    printf(" is put in an output file in terms of magnitude and phase.\n");
    printf(" The input file has the following structure: # of ck coeff's,\n");
    printf(" the ck coeff's, # of dk coeff's, the dk coeff's.\n");
    printf("\nUsage: rffr infile np outfile\n");
    printf("  infile = input file name\n");
    printf("  np = number of points wanted in FFT result\n");
    printf("  outfile = output file name\n");
    return(-1);
  }

  fp = fopen(argv[1], "r");
  if( fp == 0 )
  {
    perror( "Unable to open input file" );
    return(-1);
  }

  np = atoi( argv[2] );

  printf( "Reading input file: %s\n", argv[1] );

  /* skip header */
  for( i = 0; i < np; ++i )
  {
    fgets( linebuff, MAXLINESIZE, fp );
    if( linebuff[0] != '#' ) break;
    printf( "%s", linebuff );
  }

  c = (double *)calloc( 2 * np, sizeof(double) ); /* calloc initializes to zero */
  d = (double *)calloc( 2 * np, sizeof(double) );

  /* get the first number that's already in linebuff, which is nc */
  sscanf( linebuff, "%d", &nc );

  /* read ck data */
  for( i = 0; i < nc; ++i )
  {
    fscanf( fp, "%lf", &(c[2*i]) );
  }

  fscanf( fp, "%d", &nd );

  /* read dk data */
  for( i = 0; i < nd; ++i )
  {
    fscanf( fp, "%lf", &(d[2*i]) );
  }

  fclose( fp ); /* close input file */

  printf( "Processing...\n" );

  FFT( c, np, 1 );
  FFT( d, np, 1 );

  for( i = 0; i < np; ++i )
  {
    /* convert complex numbers to magnitude and phase */
    mc = sqrt( c[2*i]*c[2*i] + c[2*i+1]*c[2*i+1] );
    pc = atan2( c[2*i+1], c[2*i] );
    md = sqrt( d[2*i]*d[2*i] + d[2*i+1]*d[2*i+1] );
    pd = atan2( d[2*i+1], d[2*i] );
    /* divide the FFT's and store the result in c */
    c[2*i] = mc/md;
    c[2*i+1] = pc-pd;
  }

  fp = fopen(argv[3], "w");
  if( fp == 0 )
  {
    perror( "Unable to open output file" );
    return(-1);
  }

  printf( "Writing output file: %s\n\n", argv[3] );

  fprintf( fp, "# This file is the output of the program rffr\n" );
  fprintf( fp, "# The input file was: %s\n", argv[1] );
  fprintf( fp, "# Each line below contains first a magnitude, then a phase.\n" );
  for( i = 0; i < np; ++i )
    fprintf( fp, "%lf %lf\n", c[2*i], c[2*i+1] );

  fclose( fp ); /* close output file */
  free( c );
  free( d );
}
/**********************************************************************
  FFT - calculates the discrete fourier transform of an array of double
  precision complex numbers using the FFT algorithm.

  c = pointer to an array of size 2*N that contains the real and
    imaginary parts of the complex numbers. The even numbered indices contain
    the real parts and the odd numbered indices contain the imaginary parts.
      c[2*k] = real part of kth data point.
      c[2*k+1] = imaginary part of kth data point.
  N = number of data points. The array, c, should contain 2*N elements
  isign = 1 for forward FFT, -1 for inverse FFT.
*/

void FFT( double *c, int N, int isign )
{
  int n, n2, nb, j, k, i0, i1;
  double wr, wi, wrk, wik;
  double d, dr, di, d0r, d0i, d1r, d1i;
  double *cp;

  j = 0;
  n2 = N / 2;
  for( k = 0; k < N; ++k )
  {
    if( k < j )
    {
      i0 = k << 1;
      i1 = j << 1;
      dr = c[i0];
      di = c[i0+1];
      c[i0] = c[i1];
      c[i0+1] = c[i1+1];
      c[i1] = dr;
      c[i1+1] = di;
    }
    n = N >> 1;
    while( (n >= 2) && (j >= n) )
    {
      j -= n;
	  n = n >> 1;
    }
    j += n;
  }

  for( n = 2; n <= N; n = n << 1 )
  {
    wr = cos( 2.0 * M_PI / n );
    wi = sin( 2.0 * M_PI / n );
    if( isign == 1 ) wi = -wi;
    cp = c;
    nb = N / n;
    n2 = n >> 1;
    for( j = 0; j < nb; ++j )
    {
      wrk = 1.0;
      wik = 0.0;
      for( k = 0; k < n2; ++k )
      {
        i0 = k << 1;
        i1 = i0 + n;
        d0r = cp[i0];
        d0i = cp[i0+1];
        d1r = cp[i1];
        d1i = cp[i1+1];
        dr = wrk * d1r - wik * d1i;
        di = wrk * d1i + wik * d1r;
        cp[i0] = d0r + dr;
        cp[i0+1] = d0i + di;
        cp[i1] = d0r - dr;
        cp[i1+1] = d0i - di;
        d = wrk;
        wrk = wr * wrk - wi * wik;
        wik = wr * wik + wi * d;
      }
      cp += n << 1;
    }
  }
}
