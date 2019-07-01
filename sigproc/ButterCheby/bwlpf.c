/*
 *                            COPYRIGHT
 *
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

// Compile: gcc -lm -o bwlpf bwlpf.c

int main( int argc, char *argv[] )
{
  if(argc < 4)
  {
      printf("Usage: %s n s f\n", argv[0]);
      printf("Butterworth lowpass filter.\n");
      printf("  n = filter order 2,4,6,...\n");
      printf("  s = sampling frequency\n");
      printf("  f = half power frequency\n");
      return(-1);
  }

  int i, n = (int)strtol(argv[1], NULL, 10);
  n = n/2;
  double s = strtod(argv[2], NULL);
  double f = strtod(argv[3], NULL);
  double a = tan(M_PI*f/s);
  double a2 = a*a;
  double r;
  double *A = (double *)malloc(n*sizeof(double));
  double *d1 = (double *)malloc(n*sizeof(double));
  double *d2 = (double *)malloc(n*sizeof(double));
  double *w0 = (double *)calloc(n, sizeof(double));
  double *w1 = (double *)calloc(n, sizeof(double));
  double *w2 = (double *)calloc(n, sizeof(double));
  double x;

  for(i=0; i<n; ++i){
    r = sin(M_PI*(2.0*i+1.0)/(4.0*n));
    s = a2 + 2.0*a*r + 1.0;
    A[i] = a2/s;
    d1[i] = 2.0*(1-a2)/s;
    d2[i] = -(a2 - 2.0*a*r + 1.0)/s;}

  while(scanf("%lf", &x)!=EOF){
    for(i=0; i<n; ++i){
      w0[i] = d1[i]*w1[i] + d2[i]*w2[i] + x;
      x = A[i]*(w0[i] + 2.0*w1[i] + w2[i]);
      w2[i] = w1[i];
      w1[i] = w0[i];}
    printf("%lf\n", x);}

  return(0);
}
