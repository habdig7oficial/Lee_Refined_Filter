

TEST_CASE("Mean Complex win0", "[mean_complex]"){
    (*Rbind).parseEvalQ("source(\"src/tests/calc_mean_complex/calculate_mean_complex.R\")");

    mt19937 rng(Catch::getSeed());
    uniform_real_distribution<double> distribution(-numbers::pi, numbers::pi);

    array<double, 121>arr;
    
    for(int i = 0; i < REPETITIONS; i++){
        generate(arr.begin(), arr.end(), [&distribution, &rng](){
            return distribution(rng);
        });

        cv::Mat arr_mat(arr, false);

        Mat test = arr_mat.reshape(0, 11);

        (*Rbind).parseEvalQ("matrix <- matrix(0, nrow = size, ncol = size)");

        for(int k = 0; k < test.cols; k++){
            for(int m = 0; m < test.rows; m++){
                (*Rbind)["k"] = k + 1;
                (*Rbind)["m"] = m + 1;
                (*Rbind)["val"] = test.at<double>(k, m);
                (*Rbind).parseEvalQ("matrix[k, m] <- val");
                cout << "C++: " << test.at<double>(k, m) << endl;
                (*Rbind).parseEvalQ("print(matrix[k, m])");
            }
        }
        (*Rbind).parseEvalQ("source(\"src/tests/calc_mean_complex/load_matrix.R\")");

        //(*Rbind).parseEvalQ("print(all_windows)");
        //(*Rbind).parseEvalQ("print(calculate_mean_complex(window1))");

        int j = 0;
        apply([&j, &test](auto&&... args){
            double r_res, cpp_res;
            ((
                (*Rbind)["j"] = j + 1,
                //(*Rbind).parseEvalQ("print(matrix)"),
                
                r_res = (*Rbind).parseEval("calculate_mean_complex(all_windows[[j]])"), 
                cpp_res = calc_mean_complex<double>(test, 5, 5, args, true),

                cout << j << ") R complex_avg: " << r_res << endl,
                cout << j << ") C++ complex_avg: " << cpp_res << endl,
                j++
            ), ...);
        }, all_windows);

        cout << "..................." << endl;
        



        
        break;
    }


}