TEST_CASE("First integral pass", "[load_image]"){
    (*Rbind).parseEvalQ("source(\"src/tests/load_image/load_image.R\")");

    (*Rbind)["img"] = IMG;
    (*Rbind)["coherence"] = COHERENCE;

    NumericMatrix r_img= (*Rbind).parseEval("load(img)");
    NumericMatrix r_map = (*Rbind).parseEval("load(coherence)");


    //cout << "Matrix Img: " << r_img << endl;
    //cout << "Matrix Map: " << r_map << endl;

    Mat cpp_img = imread(IMG, IMREAD_UNCHANGED);
    Mat cpp_map = imread(COHERENCE, IMREAD_UNCHANGED );


    cout << "R   IMG dimension (" << r_img.nrow() << ", " << r_img.nrow() << " )" << endl;
    cout << "R   MAP dimension (" << r_map.nrow() << ", " << r_map.nrow() << " )" << endl;
    cout << "C++ IMG dimension (" << cpp_img.rows << ", " << cpp_img.cols << " )" << endl;
    cout << "C++ MAP dimension (" << cpp_map.rows << ", " << cpp_map.cols << " )" << endl;

    REQUIRE(cpp_img.rows == r_img.rows());
    REQUIRE(cpp_map.cols == r_map.ncol());


    for(int i = 0; i < r_img.rows(); i++){
        for(int j = 0; j < r_img.ncol(); j++){
            cout << "R MATRIX (" << i << ", " << j << ") = " << r_img(i, j) << endl << "C++ MATRIX (" << i << ", " << j << " ) = " << cpp_img.at<IMG_TYPE>(i, j) << endl << endl;
            if(r_img(i, j) != cpp_img.at<IMG_TYPE>(i, j)){
                FAIL("Both Matrices must be equal!");
            }
        }
        cout << endl;
    }


    REQUIRE(cpp_map.rows == r_map.nrow());
    REQUIRE(cpp_map.cols == r_map.ncol());


    for(int i = 0; i < r_map.rows(); i++){
        for(int j = 0; j < r_map.ncol(); j++){
            cout << "R MATRIX (" << i << ", " << j << ") = " << r_map(i, j) << endl << "C++ MATRIX (" << i << ", " << j << " ) = " << cpp_map.at<IMG_TYPE>(i, j) << endl << endl;
            if(r_map(i, j) != cpp_map.at<IMG_TYPE>(i, j)){
                FAIL("Both Matrices must be equal!");
            }
        }
        cout << endl;
    }
}