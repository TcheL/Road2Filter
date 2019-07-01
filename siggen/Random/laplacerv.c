/*
 *                            COPYRIGHT
 *
 *  laplacerv.c
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

// Compile: gcc -lm -o laplacerv laplacerv.c

int main( int argc, char *argv[] )
{
  if( argc < 4 )
    {
      printf("usage: %s n a b seed\n", argv[0]);
      printf("  Generates n random numbers from a Laplace distribution\n");
      printf("  a = center of the distribution\n");
      printf("  2*b^2 = variance\n");
      printf("  seed = optional random number seed\n");
      exit( -1 );
    }

  unsigned long i, n = strtoul(argv[1], NULL, 10);
  double a = strtod(argv[2], NULL);
  double b = strtod(argv[3], NULL);
  unsigned int seed = argc > 4 ? strtoul(argv[4], NULL, 10) : time(NULL);
  double u, x;

  srand(seed);

  for(i=0; i<n; ++i){
    u = (double)rand()/RAND_MAX;
    x = u < 0.5 ? a+b*log(2.0*u) : a-b*log(2.0*(1.0-u));
    printf("%lf\n", x);}

  return(0);
}
