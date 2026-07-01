#include "/Users/habdig7oficial/projects/IC/Lee_Refined_Filter/src/lib/gierull.hpp"

using namespace std;
using namespace Rcpp;


TEST_CASE("Gierull point", "[point]"){

  char *argv[] = {(char *) "dummy"};
  
  RInside R(1, argv);

  R.parseEvalQ("source(\"src/tests/gierull/gierull_base.R\")");
  NumericVector param = NumericVector::create(0.0, 0.7, 16);


  R["point"] = 0.5;
  R["param"] = param;

  double res = R.parseEval("dFuncGierullEq7(point, param)");

  cout << res << endl;
  
  REQUIRE(1 + 2 == 3);
}
