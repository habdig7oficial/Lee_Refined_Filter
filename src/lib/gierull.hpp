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

using namespace std;

double gierull(double x, double r, double theta, int L){
  double beta = r * cos(x - theta);
  
  double sum1 = 0.5 * beta * exp(L * log(1 - pow(theta, 2)))
    + gsl_sf_lngamma(L + 0.5)
    - (L + 0.5) * log(1 - pow(beta, 2))
    // + gsl_sf_lngamma()
    ; 

  cout << "hello from gierrul" << endl;

  cout << fixed << setprecision(10);
  cout << beta << endl;
  
  
  return sum1;
}
