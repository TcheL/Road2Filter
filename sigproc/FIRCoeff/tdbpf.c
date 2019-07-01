/*
 *                            COPYRIGHT
 *
 *  tdbpf - time domain bandpass filter coefficient calculator.
 *  Copyright (C) 2003, 2004, 2005, 2006 Exstrom Laboratories LLC
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
  int i, nc, nz;
  double d1, d2;
  double fc1, fc2, h;

  if( argc < 6 )
  {
  
    printf("\ntdbpf creates a file of band pass filter coefficients.\n");
    printf("\nUsage: tdbpf outfile fc1 fc2 nc nz\n");
    printf("  outfile = output file\n");
    printf("  fc1 = lower frequency as a fraction of PI [0,1]\n");
    printf("  fc2 = upper frequency as a fraction of PI [0,1]\n");    
    printf("  nc = number of coefficients\n");
    printf("  nz = number of zeros to pad\n");
    return(-1);
  }

  fp = fopen(argv[1], "w");
  if( fp == 0 )
  {
    perror( "Unable to open outfile" );
    return(-1);
  }

  fc1 = atof( argv[2] ) * M_PI;
  fc2 = atof( argv[3] ) * M_PI;
  nc = atoi( argv[4] );
  nz = atoi( argv[5] );

  printf( "\nCreating file\n" );
  fprintf( fp, "# Time domain band pass filter coefficients\n" );
  fprintf( fp, "# %5d : number of coefficients\n", nc );
  fprintf( fp, "# %5d : number of zeros padded on end\n", nz );

  d1 = ((double)nc - 1.0)/2.0;
  
  for( i = 0; i < nc; ++i )
  {
    d2 = (double)i - d1;
    h = d2 == 0 ? (fc2 - fc1) / M_PI : (sin(fc2 * d2) - sin(fc1 * d2)) / (M_PI * d2);
    fprintf( fp, "%1.15lf\n", h );
  }

  for( i = 0; i < nz; ++i )
    fprintf( fp, "0.0\n" );
  
  fclose( fp );
}
