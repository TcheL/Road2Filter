/*
 *                            COPYRIGHT
 *
 *  goertzel - A Goertzel algorithm implementation that calculates the Fourier
 *  transform over a specified frequency range at a specified resolution.
 *  by Stefan Hollos, stefan[AT]exstrom DOT com
 *  and Richard Hollos, richard[AT]exstrom DOT com
 *  Copyright (C) 2006 Exstrom Laboratories LLC
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
 *  info[AT]exstrom DOT com
 *
 *  or you can write to:
 *
 *  Exstrom Laboratories LLC
 *  662 Nelson Park Dr.
 *  Longmont, CO 80503, USA
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAXLINESIZE 128

/*
Calculates the Fourier transform, by use of the Goertzel
algorithm, over Nf points from frequency f1 to frequency f2,
of N (N>1) samples of a signal taken at sps samples per
second.
*/

void goertzel( int N, double *q, double theta, double *Qr, double *Qi )
{
  int n;
  double u0, u1, u2; /* variable of the difference eq: u(k) = f(k) + 2cos(theta)u(k-1) - u(k-2) */
  double C0, S0; /* cos(theta) & sin(theta) */
  double C02; /* 2*cos(theta) */
  double CN, SN; /* cos((N-1)*theta) & sin((N-1)*theta) */
  double yr, yi; /* real and imaginary parts of yN */

  C0 = cos(theta);
  C02 = 2.0*C0;
  S0 = sin(theta);
  CN = cos((N-1)*theta);
  SN = sin((N-1)*theta);
  u0 = 0.0;
  u1 = 0.0;

  for( n = 0; n < N; ++n )
  {
    u2 = q[n] + C02*u1 - u0;
    u0 = u1;
    u1 = u2;
  } /* end for n */

  /* Calculate yN = yr + iyi */
  yr = u2 - C0*u0;
  yi = S0*u0;

  /* Calculate F(theta) = yN*e^(-i(N-1)*theta) */
  *Qr = yr*CN + yi*SN;
  *Qi = yi*CN - yr*SN;
} /* end function goertzel */

/*******************************************************************/

int main( int argc, char *argv[] )
{
  double f1, f2; /* starting frequency f1, and ending frequency f2 [Hz] */
  int Nf; /* number of frequency points at which the FT is calculated */
  double df; /* frequency step size */
  int N; /* number of samples read from the input file, N>1 */
  int i, n; /* index */
  double sps; /* samples per second */
  double theta; /* theta = 2*Pi*f/sps */
  double dtheta; /* theta step size */
  FILE *fp; /* file pointer */
  char linebuff[MAXLINESIZE];
  double *q; /* array where samples are stored */
  double Qr, Qi; /* real & imaginary parts of FT */

  if( argc != 8 )
  {
    printf( "\ngoertzel calculates the Fourier transform at Nf equally\n");
    printf( "spaced points in the frequency interval [f1,f2]\n");
    printf( "usage: goertzel f1 f2 Nf N sps infile outfile\n");
    printf( "  f1 = starting frequency [Hz]\n");
    printf( "  f2 = ending frequency [Hz]\n");
    printf( "  Nf = number of frequency  points to calculate FT\n");
    printf( "  N = number of samples to read from the input file\n");
    printf( "  sps = samples per second\n");
    printf( "  infile = input file\n");
    printf( "  outfile = output file\n");
    exit( -1 );
  }

  f1 = atof( argv[1] );
  f2 = atof( argv[2] );
  Nf = atoi( argv[3] );
  N = atoi( argv[4] );
  sps = atof( argv[5] );

  if( N < 2 )
  {
    printf( "N must be greater than 1\n" );
    exit( -1 );
  }

  /* open file to read */
  if( ( fp = fopen( argv[6], "r" ) ) == NULL )
  {
    perror( "Error opening input file" );
    exit( -1 );
  }
  printf( "Reading data file: %s\n\n", argv[6] );

  /* Any line at the beginning of a data file that */
  /* begins with a "#" is skipped */
  for( n = 0; n < N; ++n )
  {
    fgets( linebuff, MAXLINESIZE, fp );
    if( linebuff[0] != '#' ) break;
    printf( "%s", linebuff );
  }

  /* allocate a double array of size N */
  q = (double *)malloc( N * sizeof(double) );

  /* get the first number that's already in linebuff */
  sscanf( linebuff, "%lf", &(q[0]) );
  /* read the rest of the sample data */
  for( n = 1; n < N; ++n )
  {
    fscanf( fp, "%lf", &(q[n]) );
  }
  fclose( fp ); /* close input file */

  if( ( fp = fopen( argv[7], "w" ) ) == NULL )
  {
    perror("Error opening output file" );
    exit( -1 );
  }
  printf( "Opening output file: %s\n", argv[7] );  
  
  df = (f2-f1)/((double)(Nf-1));

  /* write the header of the output file */
  fprintf( fp, "# This file produced by program goertzel\n" );
  fprintf( fp, "# %20f  :f1, starting frequency [Hz]\n", f1 );
  fprintf( fp, "# %20f  :f2, ending frequency [Hz]\n", f2 );
  fprintf( fp, "# %20f  :df, frequency step size [Hz]\n", df );
  fprintf( fp, "# %20d  :Nf, number of frequency points at which FT was calculated\n", Nf );
  fprintf( fp, "# %20d  :N, number of samples read from the input file, N>1\n", N );
  fprintf( fp, "# %20f  :sps, samples per second\n", sps );
  fprintf( fp, "# %s  :input file name\n", argv[6] );
  fprintf( fp, "# Left column: real part of FT, Right column: imaginary part\n" );

  theta = 2.0 * M_PI * f1 / sps;
  dtheta = 2.0 * M_PI * df / sps;

  for( i = 0; i < Nf; ++i )
  {
    goertzel( N, q, theta, &Qr, &Qi );
    fprintf( fp, "%lf %lf\n", Qr, Qi );
    theta += dtheta;
  } /* end for i */

  fclose( fp );
  free( q );
  return( 0 );
}
