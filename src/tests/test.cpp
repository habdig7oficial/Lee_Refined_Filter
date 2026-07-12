#include "iostream"
#include "catch2/catch_session.hpp"
#include "config.hpp"

#include "Rcpp.h"
#include "RInside.h"

/* Tests */
#include "gierull/gierull_test.hpp"
#include "first_integral_pass/first_pass_test.hpp"

unique_ptr<RInside> Rbind;

int main( int argc, char* argv[] ) {

    cout << fixed << setprecision(15); 

    Rbind = make_unique<RInside>(argc, argv);

    //(*Rbind).parseEvalQ("source(\"src/tests/install_libs.R\")");

    int result = Catch::Session().run( argc, argv );

    return result;
}