#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
  if(argc < 3)
  {
    printf("Usage: %s s f\n", argv[0]);
    printf("Four order zero-phase shift Butterworth lowpass filter.\n");
    printf("  s = sampling frequency, i.e. the number of samples\n");
    printf("  f = half power frequency\n");
    return( - 1);
  }

  double sr = strtod(argv[1], NULL);
  double fc = strtod(argv[2], NULL);
  int N = ceil(sr);
  double *x = (double *) calloc (N, sizeof(double));
  double *y = (double *) calloc (N, sizeof(double));

  int i = 0;
  while(scanf("%lf", &x[i]) != EOF && i < N) i++;
  if(i < N) N = i + 1;

  double wc, k1, k2, k3;
  double a, b, c, d, e;
  wc = tan(fc*M_PI/sr);
  k1 = sqrt(2.0)*wc;
  k2 = wc*wc;
  a = k2/(1 + k1 + k2);
  b = 2*a;
  c = a;
  k3 = b/k2;
  d = - 2*a + k3;
  e = 1 - 2*a - k3;

  double *d1 = (double *) calloc (N + 4, sizeof(double));
  d1[0] = x[0]; d1[1] = x[0];
  d1[N + 2] = x[N - 1]; d1[N + 3] = x[N - 1];
  for(i = 0; i < N; i++)
    d1[i + 2] = x[i];

  double *d2 = (double *) calloc (N + 4, sizeof(double));
  d2[0] = x[0]; d2[1] = x[0];
  for(i = 2; i < N + 2; i++)
    d2[i] = a*d1[i] + b*d1[i - 1] + c*d1[i - 2] +
      d*d2[i - 1] + e*d2[i - 2];
  d2[N + 2] = d2[N + 1]; d2[N + 3] = d2[N + 1];

  double *d3 = (double *) calloc (N + 2, sizeof(double));
  d3[N] = d2[N + 2]; d3[N + 1] = d2[N + 3];
  for(i = - (N - 1); i <= 0; i++)
    d3[ - i] = a*d2[ - i + 2] + b*d2[ - i + 3] + c*d2[ - i + 4] +
      d*d3[ - i + 1] + e*d3[ - i + 2];

  for(i = 0; i < N; i++)
    y[i] = d3[i];

  for(i = 0; i < N; i++)
    printf("%lf\n", y[i]);

  return 0;
}
