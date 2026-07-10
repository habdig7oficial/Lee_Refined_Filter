#include "iostream"
#include "catch2/catch_session.hpp"
#include "config.hpp"

#include "Rcpp.h"
#include "RInside.h"

/* Tests */
#include "gierull/gierull_test.hpp"

unique_ptr<RInside> Rbind;

int main( int argc, char* argv[] ) {

    cout << fixed << setprecision(15); 

    Rbind = make_unique<RInside>(argc, argv);

    int result = Catch::Session().run( argc, argv );

    return result;
}