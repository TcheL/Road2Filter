/*
 *                            COPYRIGHT
 *
 *  sines.c
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
#include <math.h>

// Compile: gcc -lm -o sines sines.c
// Input file format
// n (number of sines)
// a1 (amplitude) f1 (frequency) p1 (phase)
// a2             f2             p2
// an             fn             pn

double sumarray(int n, double *a)
{
  int i;
  double s = 0.0;

  for(i=0; i<n; ++i) s+=a[i];
  return(s);
}

int main( int argc, char *argv[] )
{
  if( argc != 4 )
  {
    printf("Usage: %s file s n\n", argv[0]);
    printf("Produces n samples of the sine waves defined in file.\n");
    printf("  s = sampling frequency\n");
    exit( -1 );
  }

  FILE *fp = fopen(argv[1], "r");
  double s = strtod(argv[2], NULL);
  unsigned long is, ns = strtoul(argv[3], NULL, 10);
  int i, n;

  fscanf(fp, "%d", &n);

  double a, f, p, t;
  double *x = (double *)malloc(n*sizeof(double));
  double *y = (double *)malloc(n*sizeof(double));
  double *cs = (double *)malloc(n*sizeof(double));
  double *sn = (double *)malloc(n*sizeof(double));

  for(i=0; i<n; ++i){
    fscanf(fp, "%lf %lf %lf", &a, &f, &p);
    t = 2.0*M_PI*f/s;
    cs[i] = cos(t);
    sn[i] = sin(t);
    x[i] = a*cos(p);
    y[i] = a*sin(p);}

  printf("%lf\n", sumarray(n,y));
  for(is=1; is<ns; ++is){
    for(i=0; i<n; ++i){
    t = x[i];
    x[i] = cs[i]*x[i] - sn[i]*y[i]; // x = samples of a*cos(2*pi*f*t + p)
    y[i] = sn[i]*t + cs[i]*y[i];}   // y = samples of a*sin(2*pi*f*t + p)
    printf("%lf\n", sumarray(n,y));}

  return( 0 );
}
