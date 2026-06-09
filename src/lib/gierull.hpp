/* Implementation of Gierull distribution function (Eq7)  */

/*
  X      is the current point                    | x
  
  r (Pc) is the complex correlation coefficient  | param[1]
  theta  is the phase between channels -> double | param[2]
  L      is the number of looks -> int           | param[3]
  
 */

#include "cmath"
#include "iostream"
#include "gsl/gsl_sf_gamma.h"


#include "iomanip"
#include "numbers"

using namespace std;

double gierull(double x, double r, double theta, int L){
  double beta = r * cos(x - theta);
  r = abs(r);
  
  double sum1 = 0.5 * beta *
    exp(
	L * log(1 - pow(r, 2))
	+ gsl_sf_lngamma(L + 0.5)
	- (L + 0.5) * log(1 - pow(beta, 2))
	- gsl_sf_lngamma(L)
    ) / sqrt(numbers::pi);

  double sum2 = 0.5 *
    exp(
	L * log(1 - pow(r, 2))
	+ gsl_sf_lngamma(L - 0.5)
	- L * log(1 - pow(beta, 2))
	- gsl_sf_lngamma(L)
    ) / pow(numbers::pi, 1.5);

  double sum3 = beta * asin(beta) *
    exp(
	L * log(1 - pow(r,2))
	+ gsl_sf_lngamma(L - 0.5)
	+ log(L - 0.5)
	- (L + 0.5)
	* log(1 - pow(beta, 2))
	- gsl_sf_lngamma(L)
	) / pow(numbers::pi, 1.5);
  
  cout << "hello from gierrul" << endl;
  cout << "Beta " << beta << endl;
  cout << "Sum 1: " << sum1 << endl;
  cout << "Sum 2: " << sum2 << endl;
  cout << "Sum 3: " << sum3 << endl;

  cout << "vet: " << 0 << endl;

  /* This part is different from the R code check later if this is correct*/
  double sum4 = 0;
  double acc = 0;
  int c = L - 1;
  for(double i = (L - 1.5); i > 0; i--, c--){
    // cout << c << " "<< i << " gammaratio: " << log(i) << " acc: " << acc << endl;

    sum4 += pow(-1, c + 1) * pow(-1, c - 1) *
      exp(
	  L * log(1 - pow(r, 2))
	  + gsl_sf_gamma(L - c) - gsl_sf_gamma(L)
	  + acc
	  + log(1 + (2 * c - 1) * pow(beta, 2))
	  - (c + 1) * log(1 - pow(beta, 2))
	  ) * 0.25 / numbers::pi;

    cout << sum4 << endl;
    acc += log(i);
  }

  cout << sum4 << endl;
  return sum4;
}
             
