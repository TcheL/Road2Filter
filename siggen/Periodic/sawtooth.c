/*
 *                            COPYRIGHT
 *
 *  sawtooth.c
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

// Compile: gcc -lm -o sawtooth sawtooth.c

int main( int argc, char *argv[] )
{
  if( argc < 5 )
    {
      printf("usage: %s s f a n\n", argv[0]);
      printf("  Generates a sawtooth waveform.\n");
      printf("  s = sampling rate\n");
      printf("  f = sawtooth wave frequency\n");
      printf("  a = amplitude\n");
      printf("  n = number of samples to generate\n");
      exit( -1 );
    }

  double s = strtod(argv[1], NULL);
  double f = strtod(argv[2], NULL);
  double a = -strtod(argv[3], NULL);
  unsigned long int i, n = strtoul(argv[4], NULL, 10);
  unsigned long int m = s/f;
  double y; // y = sawtooth function value
  double b = -1.0;
  double d = 2.0/m;

  for(i=0; i<n; ++i){
    if( i%m == 0 ) b += 2.0;
    y = d*i-b;
    printf("%lf\n", y);}
  return(0);
}
