TEST_CASE("First integral pass", "[magic_points]"){
    (*Rbind).parseEvalQ("source(\"src/tests/magic_points/magic_points_test.R\")");
    (*Rbind).parseEvalQ("png(\"magic_point.png\", width = 3500, height = 1080)");
    (*Rbind).parseEvalQ("par(mfrow = c(2, 10))");

    int size = (*Rbind)["size"];
    int side = size / 2;

    int i = 0;
    apply([&i, side](auto&&... args){
        (*Rbind)["i"]  = i + 1;
        LogicalMatrix m = (*Rbind).parseEval("first_half[[i]]");
        ((
            (*Rbind).parseEvalQ("plot(0,0, xlim = c(-5, 5), ylim = c(-5, 5))"),
            args.traverse([&i, side](char rx, char ry, bool scope){
                (*Rbind)["rx"] = (int)rx;
                (*Rbind)["ry"] = (int)ry;
                
                LogicalMatrix m = (*Rbind).parseEval("first_half[[i]]");

                (*Rbind).parseEvalQ("axis(side = 1, at = seq(-5, 5, by = 1))");
                (*Rbind).parseEvalQ("axis(side = 2, at = seq(-5, 5, by = 1))");
                
                (*Rbind).parseEvalQ("points(rx, ry, pch = 15, col=\"red\", cex = 3)");
                        
                cout << i << ") rx: " << (int)rx << " ry: " << (int)ry <<" tx: " << (int)rx + side << " ty: " << (int)side - ry << endl;

                INFO(i << " - (" << (int)rx << ", " << (int)ry << "), (" << side - ry << ", " << side - ry << ")\n" << m);
                REQUIRE(m(side - ry, rx + side));
                m(side - ry, rx + side) = !m(side - ry, rx + side);
                (*Rbind).parseEval("print(first_half[[i]])");
            }),
            (*Rbind).parseEvalQ("grid(nx = NULL, ny = NULL, col = \"black\", lty = \"solid\", lwd = 1)"),
            (*Rbind).parseEvalQ("i <- i + 1"),
            i++
        ), ...);
        (*Rbind).parseEvalQ("print(first_half)");
        bool has_left = (*Rbind).parseEval("any(sapply(first_half, any))");
        cout << "Has Left: " << has_left << endl;
        INFO("first half\n" << m);
        REQUIRE(!has_left);
    }, all_windows);

    (*Rbind).parseEvalQ("i <- 0"),
    i = 0;
    apply([&i, side](auto&&... args){
        (*Rbind)["i"]  = i + 1;
        LogicalMatrix m = (*Rbind).parseEval("second_half[[i]]");
        ((
            (*Rbind).parseEvalQ("plot(0,0, xlim = c(-5, 5), ylim = c(-5, 5))"),
            args.traverse_inverse([&i, side](char rx, char ry, bool scope){
                (*Rbind)["rx"] = (int)rx;
                (*Rbind)["ry"] = (int)ry;
                
                LogicalMatrix m = (*Rbind).parseEval("second_half[[i]]");

                (*Rbind).parseEvalQ("axis(side = 1, at = seq(-5, 5, by = 1))");
                (*Rbind).parseEvalQ("axis(side = 2, at = seq(-5, 5, by = 1))");
                
                (*Rbind).parseEvalQ("points(rx, ry, pch = 16, col=\"blue\", cex = 3)");
                        
                cout << i << ") rx: " << (int)rx << " ry: " << (int)ry <<" tx: " << (int)rx + side << " ty: " << (int)side - ry << endl;

                INFO(i << " - (" << (int)rx << ", " << (int)ry << "), (" << side - ry << ", " << side - ry << ")\n" << m);
                REQUIRE(m(side - ry, rx + side));
                m(side - ry, rx + side) = !m(side - ry, rx + side);
            }),
            (*Rbind).parseEvalQ("grid(nx = NULL, ny = NULL, col = \"black\", lty = \"solid\", lwd = 1)"),
            (*Rbind).parseEvalQ("i <- i + 1"),
            i++
        ), ...);
        //(*Rbind).parseEvalQ("print(second_half)");
        bool has_left = (*Rbind).parseEval("any(sapply(second_half, any))");
        cout << "Has Left: " << has_left << endl;
        INFO("second half\n" << m);
        REQUIRE(!has_left);
    }, all_windows);
}


TEST_CASE("angles", "[angles]"){
    (*Rbind).parseEvalQ("window_angle <- seq(0,19)*pi/20");

    (*Rbind).parseEvalQ("i <- 1");
    apply([](auto&&... args){
        double angle_r;
        ((
            cout << args.get_win_num() << " - " << args.angle() << endl,
            angle_r = (*Rbind).parseEval("window_angle [[i]]"),
            (void)[&](){ REQUIRE(abs(angle_r - args.angle()) < EPSILON); }(),
            (*Rbind).parseEvalQ("i <- i + 1")
        ), ...);
    }, all_windows);


    apply([](auto&&... args){
        double angle_r;
        ((
            cout << args.get_mirror_num() << " - " << args.angle_inverse() << endl,
            angle_r = (*Rbind).parseEval("window_angle [[i]]"),
            (void)[&](){ REQUIRE(abs(angle_r - args.angle_inverse()) < EPSILON); }(),
            (*Rbind).parseEvalQ("i <- i + 1")
        ), ...);
    }, all_windows);
}

TEST_CASE("First integral pass", "[relevant_points]"){
    (*Rbind).parseEvalQ("source(\"src/tests/magic_points/magic_points_test.R\")");
    (*Rbind).parseEvalQ("png(\"magic_point2.png\", width = 3500, height = 1080)");
    (*Rbind).parseEvalQ("par(mfrow = c(2, 10))");

    int size = (*Rbind)["size"];
    int side = size / 2;

    int i = 0;
    apply([&i, side](auto&&... args){
        (*Rbind)["i"]  = i + 1;
        LogicalMatrix m = (*Rbind).parseEval("first_half[[i]]");
        ((
            (*Rbind).parseEvalQ("plot(0,0, xlim = c(-7, 7), ylim = c(-7, 7))"),
            args.traverse([&i, side](char rx, char ry, bool scope){
                (*Rbind)["rx"] = (int)rx;
                (*Rbind)["ry"] = (int)ry;
                
                LogicalMatrix m = (*Rbind).parseEval("first_half[[i]]");

                (*Rbind).parseEvalQ("axis(side = 1, at = seq(-5, 5, by = 1))");
                (*Rbind).parseEvalQ("axis(side = 2, at = seq(-5, 5, by = 1))");
                
                (*Rbind).parseEvalQ("points(rx, ry, pch = 15, col=\"red\", cex = 3)");
                        
                //cout << i << ") rx: " << (int)rx << " ry: " << (int)ry <<" tx: " << (int)rx + side << " ty: " << (int)side - ry << endl;
            }),
            (void)[&args](){ 
                auto a = args.show_filtered(); 
                for(int i = 0; i < a.size(); i++){
                    (*Rbind)["ex"] = (int) a[i].first;
                    (*Rbind)["ey"] = (int) a[i].second;
                    //cout << i << ") rx: " <<  (int) a[i].first << " ry: " << (int) a[i].second << endl;
                    (*Rbind).parseEvalQ("points(ex, ey, pch = 17, col=\"green\", cex = 3)");
                }
            }(),
            args.traverse_relevant([](char rx, char ry, bool scope){
                (*Rbind)["ex"] = (int) rx;
                (*Rbind)["ey"] = (int) ry;
                //cout << i << ") rx: " <<  (int) a[i].first << " ry: " << (int) a[i].second << endl;
                //(*Rbind).parseEvalQ("points(ex, ey, pch = 18, col=\"orange\", cex = 3)");
            }),
            (*Rbind).parseEvalQ("grid(nx = NULL, ny = NULL, col = \"black\", lty = \"solid\", lwd = 1)"),
            (*Rbind).parseEvalQ("i <- i + 1"),
            i++
        ), ...);
    }, all_windows);

    i = 0;
    apply([&i, side](auto&&... args){
        (*Rbind)["i"]  = i + 1;
        LogicalMatrix m = (*Rbind).parseEval("second_half[[i]]");
        ((
            (*Rbind).parseEvalQ("plot(0,0, xlim = c(-7, 7), ylim = c(-7, 7))"),
            args.traverse_inverse([&i, side](char rx, char ry, bool scope){
                (*Rbind)["rx"] = (int)rx;
                (*Rbind)["ry"] = (int)ry;
                
                LogicalMatrix m = (*Rbind).parseEval("second_half[[i]]");

                (*Rbind).parseEvalQ("axis(side = 1, at = seq(-5, 5, by = 1))");
                (*Rbind).parseEvalQ("axis(side = 2, at = seq(-5, 5, by = 1))");
                
                (*Rbind).parseEvalQ("points(rx, ry, pch = 15, col=\"blue\", cex = 3)");
                        
                //cout << i << ") rx: " << (int)rx << " ry: " << (int)ry <<" tx: " << (int)rx + side << " ty: " << (int)side - ry << endl;
            }),
            (void)[&args](){ 
            
                auto a = args.show_marked(); 
                for(int i = 0; i < a.size(); i++){
                    (*Rbind)["ex"] = (int) a[i].first;
                    (*Rbind)["ey"] = (int) a[i].second;
                    //cout << i << ") rx: " <<  (int) a[i].first << " ry: " << (int) a[i].second << endl;
                    (*Rbind).parseEvalQ("points(ey, ex, pch = 17, col=\"green\", cex = 3)"); // inverted intencionally
                }
            }(),
            args.traverse_relevant_inverse([](char rx, char ry, bool scope){
                (*Rbind)["ex"] = (int) rx;
                (*Rbind)["ey"] = (int) ry;
                //cout << i << ") rx: " <<  (int) a[i].first << " ry: " << (int) a[i].second << endl;
                //(*Rbind).parseEvalQ("points(ex, ey, pch = 16, col=\"orange\", cex = 3)"); 
            }),
            (*Rbind).parseEvalQ("grid(nx = NULL, ny = NULL, col = \"black\", lty = \"solid\", lwd = 1)"),
            (*Rbind).parseEvalQ("i <- i + 1"),
            i++
        ), ...);
    }, all_windows);
}