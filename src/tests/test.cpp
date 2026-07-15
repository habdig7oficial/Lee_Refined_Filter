#include "iostream"
#include "catch2/catch_session.hpp"
#include "config.hpp"

#include "Rcpp.h"
#include "RInside.h"

/* Tests */
#include "gierull/gierull_test.hpp"
#include "first_integral_pass/first_pass_test.hpp"
#include "load_image/load_image.hpp"
#include "window_cut/window_cut.hpp"
#include "magic_points/magic_points_test.hpp"

unique_ptr<RInside> Rbind;

int main( int argc, char* argv[] ) {
    cout << fixed << setprecision(15); 

    Rbind = make_unique<RInside>(argc, argv);

    (*Rbind).parseEvalQ("png(\"gierull_plot.png\", width = 1920, height = 1080)");
    (*Rbind).parseEvalQ("par(mfrow = c(1, 2))");

    int result = Catch::Session().run( argc, argv );

    cout << "C++ version: " << __cplusplus << endl;

    return result;
}