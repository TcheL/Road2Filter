/*
 *                            COPYRIGHT
 *
 *  bernrv.c
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

// Compile: gcc -lm -o bernrv bernrv.c

int main( int argc, char *argv[] )
{
  if( argc < 2 )
    {
      printf("usage: %s n seed\n", argv[0]);
      printf("  Generates n random numbers with values -1 or +1");
      printf("  seed = optional random number seed\n");
      exit( -1 );
    }

  unsigned long i, n = strtoul(argv[1], NULL, 10);
  unsigned int seed = argc > 2 ? strtoul(argv[2], NULL, 10) : time(NULL);
  int b;

  srand(seed);

  for(i=0; i<n; ++i){
    b = rand() % 2 ? -1 : 1;
    printf("%d ", b);}

  printf("\n");
  return(0);
}
