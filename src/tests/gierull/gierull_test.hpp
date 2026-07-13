#include "gsl/gsl_integration.h"

using namespace std;
using namespace Rcpp;
using namespace gierull;


extern unique_ptr<RInside> Rbind;

TEST_CASE("Gierull integration", "[integration]"){
  gsl_integration_workspace *w = gsl_integration_workspace_alloc(1000);   

  mt19937 rng(Catch::getSeed());
  uniform_real_distribution<double> distribution(-numbers::pi, numbers::pi);

  (*Rbind).parseEvalQ("source(\"src/tests/gierull/gierull_base.R\")");
  (*Rbind).parseEvalQ("x <- c()");
  (*Rbind).parseEvalQ("y <- c()");

  for(int i = 0; i < REPETITION; i++){
    /* === Rand Params === */

    double point = distribution(rng);
    gierull::Param cpp_param = {
      .r = 0.7,
      .theta = 0,
      .L = 16
    };

    cout << "Point = " << point << endl;
    
    /* === R TESTS === */ 


    NumericVector r_param = NumericVector::create(cpp_param.r, cpp_param.theta, cpp_param.L);


    (*Rbind)["point"] = point;
    (*Rbind)["param"] = r_param;

    (*Rbind).parseEvalQ("");
    (*Rbind).parseEval("r_ypoint = dFuncGierullEq7(point, param)");
    (*Rbind).parseEval("x <- append(x, point)");
    (*Rbind).parseEval("y <- append(y, r_ypoint)");

    double r_ypoint = (*Rbind).parseEval("r_ypoint");
    double r_res = (*Rbind).parseEval("integrate(dFuncGierullEq7, lower = -point, upper = point, subdivisions = 1000, param = param)$value");

    cout << "R point: " << r_ypoint << "\t| integral: " << r_res << endl;


    /* === C++ TESTS === */

    double cpp_ypoint = gierull::gierull(point, (void *) &cpp_param);

    gsl_function F;
    F.function = &gierull::gierull;
    F.params = (void *)&cpp_param;
    double cpp_res, err = 0;

    //gsl_integration_qags(&F, -point, point, 0, 1e-7, 1000, w, &cpp_res, &err);
    integrate(&F, point, &cpp_res, &err);

    cout << "C++ Result: " << cpp_ypoint << "\t| integral: " << cpp_res << endl << endl;

    

    REQUIRE(abs(cpp_ypoint - r_ypoint) < EPSILON);
    REQUIRE(abs(cpp_res - r_res) < EPSILON);
  }   
  gsl_integration_workspace_free(w);
  (*Rbind).parseEvalQ("sorted <- order(x)");
  (*Rbind).parseEvalQ("x <- x[sorted]");
  (*Rbind).parseEvalQ("y <- y[sorted]");
  (*Rbind).parseEvalQ("plot(x, y, type = \"b\")");

}
