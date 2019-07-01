/*
 *                            COPYRIGHT
 *
 *  fm.c
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

// compile: gcc -lm -o fm fm.c

int main( int argc, char *argv[] )
{
  if(argc < 6)
  {
    printf("Usage: %s f0 f1 r s n\n", argv[0]);
    printf("  Produces a frequency modulated sine wave\n");
    printf("  f0 = carrier frequency\n");
    printf("  f1 = modulation frequency\n");
    printf("  r = modulation index\n");
    printf("  s = sampling frequency\n");
    printf("  n = number of samples\n");
    return(-1);
  }

  double f0 = strtod(argv[1],NULL);
  double f1 = strtod(argv[2],NULL);
  double r = strtod(argv[3], NULL);
  double s = strtod(argv[4], NULL);
  unsigned long i, n = atoi(argv[5]);
  double p0 = 2.0*M_PI*f0/s;
  double p1 = 2.0*M_PI*f1/s;
  double y0 = 0.0;
  double y1 = -sin(p1);
  double y2 = 0.0;
  double d = 2.0*cos(p1);

  for(i=0; i<n; ++i)
  {
    printf("%lf\n", sin(p0*i + r*y0));
    y2 = y1;
    y1 = y0;
    y0 = d*y1 - y2;
  }

  return(0);
}
