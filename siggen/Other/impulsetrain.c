/*
 *                            COPYRIGHT
 *
 *  impulsetrain.c
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

// Compile: gcc -lm -o impulsetrain impulsetrain.c

int main( int argc, char *argv[] )
{
  if( argc < 4 )
    {
      printf("usage: %s a n i1 i2 ...\n", argv[0]);
      printf("  Generates a*d[i] where d[i1]=1, d[i2]=1,... and d[i]=0 otherwise \n");
      printf("  a = amplitude\n");
      printf("  n = number of terms to generate\n");
      printf("  i1, i2, ... = pulse indices\n");
      exit( -1 );
    }

  double a = strtod(argv[1], NULL);
  unsigned long i, n = strtoul(argv[2], NULL, 10);
  int j, np = argc-3;
  unsigned long *ipulse = (unsigned long *)malloc(np*sizeof(unsigned long));

  for(j=0; j<np; ++j) ipulse[j]=strtoul(argv[j+3], NULL, 10);

  for(i=0, j=0; i<n; ++i){
    if(i==ipulse[j] && j<np){
      ++j;
      printf("%lf\n",a);}
    else
      printf("0.0\n");}

  return(0);
}
