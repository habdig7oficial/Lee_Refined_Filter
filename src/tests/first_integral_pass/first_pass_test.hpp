TEST_CASE("First integral pass", "[first_pass]"){
    (*Rbind).parseEvalQ("source(\"src/tests/first_integral_pass/filtragem_img_simulada.R\")");

    /* === Parameters === */
    gierull::Param gsl_params = {
        .r = 0.7,
        .theta = 0.0,
        .L = 16
    };
        
    gsl_function F;
    F.function = &gierull::gierull;
    F.params = (void *)&gsl_params;

    mt19937 rng(Catch::getSeed());
    uniform_real_distribution<double> distribution(0, 1);
    

    /* Run less tests because R it's to slow */
    for(int i = 0; i < 2; i++){
        double rand = distribution(rng);

        (*Rbind)["img"] = IMG;
        (*Rbind)["coherence"] = COHERENCE;
        (*Rbind)["random"] = rand;

        /* === R === */
        double r_res = (*Rbind).parseEval("exec(img, coherence, random)");

        /* === C++ === */
        auto [cpp_res, aprox, iter] = match_area_x(&F, -numbers::pi, numbers::pi, rand);

        double places = (*Rbind)["places"];
        double rounded = (double)round(cpp_res * pow(10, places)) / pow(10, places); 

        cout << "R: " << r_res << endl;
        cout << "C++: " << cpp_res << " Rounded (" << places << "): " << rounded << endl;


        double reduced_tolerance = (*Rbind)["v"];
        REQUIRE(abs(rounded - r_res) < reduced_tolerance);
    }
}