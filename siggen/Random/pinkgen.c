/*
 *                            COPYRIGHT
 *
 *  pinkgen.c
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

// Compile: gcc -lm -o pinkgen pinkgen.c
// Note: audio sample rate = 44100 samples/second

int main( int argc, char *argv[] )
{
  if(argc < 4)
  {
      printf("Usage: %s n m a seed\n", argv[0]);
      printf("Pink noise generator.\n");
      printf("  n = filter order\n");
      printf("  m = number of output samples\n");
      printf("  a = variance\n");
      printf("  seed = optional random number seed\n");
      return(-1);
  }

  int j, n = (int)strtol(argv[1], NULL, 10);
  unsigned int m = strtoul(argv[2], NULL, 10);
  double a = strtod(argv[3], NULL);
  unsigned int i, seed;
  double z1, z2, r;
  double *w0 = (double *)calloc(n, sizeof(double));
  double *w1 = (double *)calloc(n, sizeof(double));
  double *c = (double *)calloc(n, sizeof(double));
  double d = cos(2.0*M_PI/((double)(2*n+1)));
  double x;

  for(i=0; i<n; ++i)
    switch(i){
    case 0:
      c[0] = d; break;
    case 1:
      c[1] = 2.0*d*d - 1.0; break;
    default:
      c[i] = 2.0*d*c[i-1] - c[i-2]; break;}

  seed = argc > 3 ? strtoul(argv[4], NULL, 10) : time(NULL);
  srand(seed);

  for(i=0; i<m; ++i){
    do{
      z1 = 2.0*rand()/RAND_MAX - 1.0;
      z2 = 2.0*rand()/RAND_MAX - 1.0;
      r = z1 * z1 + z2 * z2;} while(r >= 1.0);
    x = a * z1 * sqrt(-2.0 * log(r) / r);
    for(j=0; j<n; ++j){
      w0[j] = x - c[j]*w1[j];
      x = w0[j] - c[j]*w1[j];
      w1[j] = w0[j];}
    printf("%lf\n", x);}

  return(0);
}
