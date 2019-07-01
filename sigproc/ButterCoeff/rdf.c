/*
 *                            COPYRIGHT
 *
 *  rdf - recursive digital filter program
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

int main( int argc, char *argv[] )
{
  FILE *fp;
  char linebuff[MAXLINESIZE];
  int i, j; /* counters */
  int nc; /* number of ck coeff's */
  int nd; /* number of dk coeff's */
  int sx; /* starting point (zero based) to begin reading data */
  int nx; /* number of data points to filter */
  int ny; /* number of output points */
  double *c; /* array where c coeff's are stored */
  double *d; /* array where d coeff's are stored */
  double *x; /* array where data to be filtered is stored */
  double *y; /* array where recent outputs are stored */  
  double s1; /* a sum of products of dk's and y's */
  double s2; /* a sum of products of ck's and x's */

  if( argc < 6 )
  {
    printf("\n rdf stands for 'recursive digital filter'.\n");
    printf(" This program filters data from an input file, by use of\n");
    printf(" ck and dk coeff's read in from another input file.\n");
    printf(" All lines at top of input files starting with # are ignored.\n");
    printf("\n Usage: rdf infile_filter infile_data sx nx outfile\n");
    printf("  infile_filter = input file containing filter coefficients\n");
    printf("  infile_data = input file containing data to filter\n");
    printf("  sx = starting point (zero based) to begin reading data\n");
    printf("  nx = number of data points to filter\n");
    printf("  outfile = output file where filtered data is stored\n");
    return(-1);
  }

  fp = fopen(argv[1], "r");
  if( fp == 0 )
  {
    perror( "Unable to open input filter file" );
    return(-1);
  }

  printf( "Reading input file: %s\n", argv[1] );

  /* skip header */
  for( i = 0; i < 10000; ++i )
  {
    fgets( linebuff, MAXLINESIZE, fp );
    if( linebuff[0] != '#' ) break;
    printf( "%s", linebuff );
  }

  /* get the first number that's already in linebuff, which is nc */
  sscanf( linebuff, "%d", &nc );

  c = (double *)calloc( nc, sizeof(double) ); /* calloc initializes to zero */

  /* read ck data */
  for( i = 0; i < nc; ++i )
  {
    fscanf( fp, "%lf", &(c[i]) );
  }

  fscanf( fp, "%d", &nd );

  d = (double *)calloc( nd, sizeof(double) ); /* calloc initializes to zero */

  /* read dk data */
  for( i = 0; i < nd; ++i )
  {
    fscanf( fp, "%lf", &(d[i]) );
  }

  fclose( fp ); /* close input filter file */


  /* open input data file */
  fp = fopen(argv[2], "r");
  if( fp == 0 )
  {
    perror( "Unable to open input data file" );
    return(-1);
  }

  sx = atoi( argv[3] );
  nx = atoi( argv[4] );

  printf( "\nReading input file: %s\n", argv[2] );

  /* skip header */
  for( i = 0; i < 10000; ++i )
  {
    fgets( linebuff, MAXLINESIZE, fp );
    if( linebuff[0] != '#' ) break;
    printf( "%s", linebuff );
  }
  printf( "\n" );

  x = (double *)calloc( nx, sizeof(double) ); /* calloc initializes to zero */

  /* skip the first sx points in data */
  for( i = 0; i < sx; ++i )
  {
    fgets( linebuff, MAXLINESIZE, fp );
  }

  /* get the first number that's already in linebuff */
  sscanf( linebuff, "%lf", &(x[0]) );

  for( i = 1; i < nx; ++i )
  {
    fscanf( fp, "%lf", &(x[i]) );
  }

  fclose( fp ); /* close input data file */

  printf( "Output file = %s\n", argv[5] );

  fp = fopen(argv[5], "w");
  if( fp == 0 )
  {
    perror( "Unable to open output file" );
    return(-1);
  }

  fprintf( fp, "# %s  :program that created this file\n", argv[0] );
  fprintf( fp, "# %s  :input file 1, contains filter coeff's\n", argv[1] );
  fprintf( fp, "# %s  :input file 2, contains data that is being filtered\n", argv[2] );
  fprintf( fp, "# %d  :nx, number of points used in input data file\n", nx );

  ny = nx + nc;
  y = (double *)calloc( ny, sizeof(double) ); /* calloc initializes to zero */

  for( i = 0; i < ny; ++i )
  {
    s1 = 0.0;

    for( j = (i < nd ? 0 : i-nd+1); j < i; ++j )
      s1 += d[i-j] * y[j];

    s2 = 0.0;

    for( j = (i < nc ? 0 : i-nc+1); j <= (i<nx ? i : nx-1); ++j )
      s2 += c[i-j] * x[j];

    y[i] = s2 - s1;
    fprintf( fp, "%lf\n", y[i] );
  }

  fclose( fp );
  free( c );
  free( d );
  free( x );
  free( y );
  return(1);
} /* end of program */
