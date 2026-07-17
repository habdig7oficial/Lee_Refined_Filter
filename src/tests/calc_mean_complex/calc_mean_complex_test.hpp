

TEST_CASE("Mean Complex win0", "[mean_complex]"){
    (*Rbind).parseEvalQ("source(\"src/tests/calc_mean_complex/load_matrix.R\")");

    vector<float>arr(121);
    std::fill(arr.begin(), arr.end(), 5);
    cv::Mat arr_mat(arr, false);

    Mat test1 = arr_mat.reshape(0, 11);

    calc_mean_complex<float>(test1, 5, 5, window0, true);

    (*Rbind)["matrix"] = arr;
    (*Rbind).parseEvalQ("matrix <- dim(matrix) <- c(11,11)");
    (*Rbind).parseEvalQ("print(matrix)");
    (*Rbind).parseEvalQ("window1[5:7,1:11]<- 5");
    (*Rbind).parseEvalQ("print(calculate_mean_complex(window1))");

    REQUIRE(1);
}