/*
 *                            COPYRIGHT
 *
 *  extract - Extracts the real or imaginary parts or the magnitude
 *  or the phase of an FFT file that was created by the program fft.
 *
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
  char *pchar;
  int i, np;
  double *c;
  double sf;

  if( argc < 5 )
  {
    printf("\n extract will extract the real or imaginary parts of an FFT\n");
    printf(" or the magnitude or the phase.\n");
    printf("\nUsage: extract x infile np outfile\n");
    printf("  x = m to extract magnitude information\n");
    printf("      p to extract phase information\n");
    printf("      r to extract the real part\n");    
    printf("      i to extract the imaginary part\n");
    printf("  infile = input file name\n");
    printf("  np = number of points to use in infile\n");
    printf("  outfile = output file name\n");
    return(-1);
  }

  fp = fopen(argv[2], "r");
  if( fp == 0 )
  {
    perror( "Unable to open fft file" );
    return(-1);
  }

  np = atoi( argv[3] );

  printf( "Reading fft file: %s\n\n", argv[2] );

  /* skip header */
  for( i = 0; i < np; ++i )
  {
    fgets( linebuff, MAXLINESIZE, fp );
    if( linebuff[0] != '#' ) break;
    printf( "%s", linebuff );
  }

  c = (double *)malloc( 2 * np * sizeof(double) );

  /* get the first number that's already in linebuff */
  sscanf( linebuff, "%lf %lf", &(c[0]), &(c[1]) );

  /* read fft data */
  for( i = 1; i < np; ++i )
  {
    fscanf( fp, "%lf %lf", &(c[2*i]), &(c[2*i+1]) );
  }
  fclose( fp );

  fp = fopen(argv[4], "w");
  if( fp == 0 )
  {
    perror( "Unable to open output file" );
    return(-1);
  }

  printf( "Writing output file: %s\n\n", argv[4] );

  switch( argv[1][0] )
  {
    case 'm':
      for( i = 0; i < np; ++i )
        fprintf( fp, "%lf\n", sqrt( c[2*i]*c[2*i] + c[2*i+1]*c[2*i+1] ) );
      break;
      
    case 'p':
      for( i = 0; i < np; ++i )
        fprintf( fp, "%lf\n", atan2( c[2*i+1], c[2*i] ) );
      break;
      
    case 'r':
      for( i = 0; i < np; ++i )
        fprintf( fp, "%lf\n", c[2*i] );
      break;
      
    case 'i':
      for( i = 0; i < np; ++i )
        fprintf( fp, "%lf\n", c[2*i+1] );
      break;
  }
  
  fclose( fp );
  free( c );
}
