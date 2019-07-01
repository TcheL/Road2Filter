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

// Compile: gcc -lm -o chebbsf chebbsf.c
// Filters data read from stdin using a Chebyshev bandstop filter.
// The order of the filter must be a multiple of 4.

int main( int argc, char *argv[] )
{
  if(argc < 6){
    printf("Usage: %s n e s f1 f2\n", argv[0]);
    printf("Chebyshev bandstop filter.\n");
    printf("  n = filter order 4,8,12,...\n");
    printf("  e = epsilon [0,1]\n");
    printf("  s = sampling frequency\n");
    printf("  f1 = upper half power frequency\n");
    printf("  f2 = lower half power frequency\n");
    return(-1);}

  int i, n = (int)strtol(argv[1], NULL, 10);
  if(n % 4){
    printf("Order must be 4,8,12,16,...\n");
    return(-1);}
  int m = n/4; // number of second order sections
  // note: analog filter has order n/2

  double ep = strtod(argv[2], NULL);
  double s = strtod(argv[3], NULL);
  double f1 = strtod(argv[4], NULL);
  double f2 = strtod(argv[5], NULL);
  double a = cos(M_PI*(f1+f2)/s)/cos(M_PI*(f1-f2)/s);
  double a2 = a*a;
  double b = tan(M_PI*(f1-f2)/s);
  double b2 = b*b;
  double u = log((1.0+sqrt(1.0+ep*ep))/ep);
  double su = sinh(2.0*u/(double)n);
  double cu = cosh(2.0*u/(double)n);
  double r, c;
  double *A = (double *)malloc(m*sizeof(double));
  double *d1 = (double *)malloc(m*sizeof(double));
  double *d2 = (double *)malloc(m*sizeof(double));
  double *d3 = (double *)malloc(m*sizeof(double));
  double *d4 = (double *)malloc(m*sizeof(double));
  double *w0 = (double *)calloc(m, sizeof(double));
  double *w1 = (double *)calloc(m, sizeof(double));
  double *w2 = (double *)calloc(m, sizeof(double));
  double *w3 = (double *)calloc(m, sizeof(double));
  double *w4 = (double *)calloc(m, sizeof(double));
  double x;

  for(i=0; i<m; ++i){
    r = sin(M_PI*(2.0*i+1.0)/n)*su;
    c = cos(M_PI*(2.0*i+1.0)/n)*cu;
    c = r*r + c*c;
    s = b2 + 2.0*b*r + c;
    A[i] = 1.0/(4.0*s); // 4.0
    d1[i] = 4.0*a*(c+b*r)/s;
    d2[i] = 2.0*(b2-2.0*a2*c-c)/s;
    d3[i] = 4.0*a*(c-b*r)/s;
    d4[i] = -(b2 - 2.0*b*r + c)/s;}
  r = 4.0*a;
  s = 4.0*a2+2.0;

  ep = 2.0/ep; // used to normalize
  while(scanf("%lf", &x)!=EOF){
    for(i=0; i<m; ++i){
      w0[i] = d1[i]*w1[i] + d2[i]*w2[i]+ d3[i]*w3[i]+ d4[i]*w4[i] + x;
      x = A[i]*(w0[i] - r*w1[i] + s*w2[i]- r*w3[i] + w4[i]);
      w4[i] = w3[i];
      w3[i] = w2[i];
      w2[i] = w1[i];
      w1[i] = w0[i];}
    printf("%lf\n", ep*x);}

  return(0);
}
