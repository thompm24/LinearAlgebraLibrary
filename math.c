#include <stdlib.h>
#include <stdio.h>

double powerd(double x, double n);
double sqrtd(double x);
double absd(double x);



double powerd(double x, double n)
{
  double result = 1;
  int i = 0;
  while((i < n) && (result = x))
  {
    if (i != 0)
    {
      result = result * result;
    }
    i++;
    }
  return result;
}

int poweri(int x, int n)
{
  int i = 0;
  int result = 1;
  while ((i < n) && (result = x))
  {
    result = (i != 0) ? (result * result) : result;
    i++;
  }
  return result;
}


double sqrtd(double x) {
    double guess = x;
    double precision = 0.000001; // Precision of the result
    double guessSquared;

    if (x < 0) {
        printf("Negative input to square root function.\n");
        return -1.0; // or handle as desired for negative inputs
    }

    do {
        guessSquared = guess * guess;
        guess = (guess + x / guess) / 2.0;
    } while (absd(guessSquared - x) > precision);

    return guess;
}

double absd(double x)
{
  if (x < 0)
  {
    return (x * -1);
  }
  else
  {
    return x;
  }
}
