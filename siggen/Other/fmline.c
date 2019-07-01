/*
 *                            COPYRIGHT
 *
 *  fmline.c
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

// Compile: gcc -lm -o fmline fmline.c

typedef struct {
  double c0;
  double s0;
  double cd;
  double sd;
  double x0;
  double y0;
} Tfmline;

int fmlineInit(Tfmline *fml, double f0, double f1, double s, unsigned int n)
{
  double t0 = 2.0*M_PI*f0/s;
  double t1 = 2.0*M_PI*f1/s;
  double td = (t1 - t0)/(double)n;
  fml->c0 = cos(t0);
  fml->s0 = sin(t0);
  fml->cd = cos(td);
  fml->sd = sin(td);
  fml->x0 = 1.0;
  fml->y0 = 0.0;
  return(0);
}

int fmlineEval(Tfmline *fml)
{
  double t = fml->x0;
  fml->x0 = fml->x0*fml->c0 - fml->y0*fml->s0;
  fml->y0 = t*fml->s0 + fml->y0*fml->c0;
  t = fml->c0;
  fml->c0 = fml->c0*fml->cd - fml->s0*fml->sd;
  fml->s0 = t*fml->sd + fml->s0*fml->cd;
  return(0);
}

int main( int argc, char *argv[] )
{
  if(argc < 5)
  {
    printf("usage: %s f0 f1 s n\n", argv[0]);
    printf("  Produces a linear frequency modulated sine wave\n");
    printf("  f0 = start frequency\n");
    printf("  f1 = stop frequency\n");
    printf("  s = sampling frequency\n");
    printf("  n = number of samples\n");
    exit( -1 );
  }

  double f0 = strtod(argv[1], NULL);
  double f1 = strtod(argv[2], NULL);
  double s = strtod(argv[3], NULL);
  unsigned long i, n = strtoul(argv[4], NULL, 10);
  Tfmline *fml = (Tfmline *)malloc(sizeof(Tfmline));
  fmlineInit(fml, f0, f1, s, n);

  for(i=1; i<n; ++i){
    printf("%lf\n", fml->y0);
    fmlineEval(fml);}
  return( 0 );
}
