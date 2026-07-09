#include "../../lib/gierull.hpp"
#include "../config.hpp"

using namespace std;
using namespace Rcpp;
using namespace gierull;


TEST_CASE("Gierull point", "[point]"){

  char *argv[] = {(char *) "dummy"};
  
  RInside R(1, argv);

  for(int i = 0; i < REPETITION; i++){
    /* === Rand Params === */
    //mt19937 rng(seed);
    
    double point = 0.5;
    Param cpp_param = {
      .r = 0,
      .theta = 0.7,
      .L = 16
    };
    
    /* === R TESTS === */ 
    R.parseEvalQ("source(\"src/tests/gierull/gierull_base.R\")");
    NumericVector r_param = NumericVector::create(cpp_param.r, cpp_param.theta, cpp_param.L);


    R["point"] = point;
    R["param"] = r_param;

    double r_res = R.parseEval("dFuncGierullEq7(point, param)");

    cout << "R Result: " << r_res << endl;


    /* === R TESTS === */

    double cpp_res = gierull::gierull(point, (void *) &cpp_param);

    cout << "C++ Result: " << cpp_res << endl;

    cout << rand() << endl;
  
    REQUIRE(abs(cpp_res - r_res) < TOLERANCE);
  }
}
