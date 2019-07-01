/*
 *                            COPYRIGHT
 *
 *  brownrv.c
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
#include <time.h> //TcheL: As a patch

// Compile: gcc -lm -o brownrv brownrv.c

int main( int argc, char *argv[] )
{
  if( argc < 4 )
    {
      printf("usage: %s n m a seed\n", argv[0]);
      printf("  Generates n samples of an integrated gaussian random variable\n");
      printf("  where the gaussian has mean=m, stdev=a\n");
      printf("  seed = optional random number seed\n");
      exit( -1 );
    }

  unsigned long i, n = strtoul(argv[1], NULL, 10);
  double m = strtod(argv[2], NULL);
  double a = strtod(argv[3], NULL);
  unsigned int seed;
  double z1, z2, r, d;
  double x = 0.0;

  seed = argc > 4 ? strtoul(argv[4], NULL, 10) : time(NULL);
  srand(seed);

  for(i=0; i<n; ++i){
    do{
      z1 = 2.0*rand()/RAND_MAX - 1.0;
      z2 = 2.0*rand()/RAND_MAX - 1.0;
      r = z1 * z1 + z2 * z2;} while(r >= 1.0);
    d = a * sqrt(-2.0 * log(r) / r);
    x += m + d * z1;
    printf("%lf\n", x);}
  return(0);
}
