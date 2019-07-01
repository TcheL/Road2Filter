/*
 *                            COPYRIGHT
 *
 *  parabolic.c
 *  Copyright (C) 2014 Exstrom Laboratories LLC
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
 *  http://www.gnu.org/copyleft/gpl.html
 *
 *  or you can write to:
 *
 *  The Free Software Foundation, Inc.
 *  675 Mass Ave
 *  Cambridge, MA 02139, USA
 *
 *  Exstrom Laboratories LLC contact:
 *  stefan(AT)exstrom.com
 *
 *  Exstrom Laboratories LLC
 *  Longmont, CO 80503, USA
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Compile: gcc -lm -o parabolic parabolic.c

int main( int argc, char *argv[] )
{
  if( argc < 5 )
    {
      printf("usage: %s s f a n\n", argv[0]);
      printf("  Generates a parabolic waveform.\n");
      printf("  s = sampling rate\n");
      printf("  f = parabolic wave frequency\n");
      printf("  a = amplitude\n");
      printf("  n = number of samples to generate\n");
      exit( -1 );
    }

  double s = strtod(argv[1], NULL);
  double f = strtod(argv[2], NULL);
  double A = strtod(argv[3], NULL);
  double y; // y = parabolic function value
  long i, n = strtol(argv[4], NULL, 10);
  long m = s/(2.0*f);
  long a = -m;
  long b = 0;

  A*=4.0/(double)(m*m);
  for(i=0; i<n; ++i){
    if( i%m == 0 ) {a+=m; b+=m; A=-A;}
    y = A*(i-a)*(i-b);
    printf("%lf\n", y);}
  return(0);
}
