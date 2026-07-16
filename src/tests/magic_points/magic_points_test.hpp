TEST_CASE("First integral pass", "[magic_points]"){
    (*Rbind).parseEvalQ("source(\"src/tests/magic_points/magic_points_test.R\")");
    (*Rbind).parseEvalQ("png(\"magic_point.png\", width = 1920, height = 1080)");
    (*Rbind).parseEvalQ("par(mfrow = c(2, 5))");

    int size = (*Rbind)["size"];
    int side = size / 2;
    

    int second_half = (*Rbind).parseEval("length(all_windows) / 2");
    
    for(int i = 0; i < all_windows.size(); i++){
        MagicPoints window = all_windows[i];
        (*Rbind)["i"] = i + 1;
        (*Rbind)["j"] = i + 1 + second_half;

        (*Rbind).parseEvalQ("plot(0,0, xlim = c(-5, 5), ylim = c(-5, 5))");
        LogicalMatrix m = (*Rbind).parseEval("all_windows[[i]]");
        LogicalMatrix m2 = (*Rbind).parseEval("all_windows[[j]]");

        window.traverse([&m, side, i](char rx, char ry, bool scope){
            (*Rbind)["rx"] = (int)rx;
            (*Rbind)["ry"] = (int)ry;

            /* Makes the relative position absolute */
            //cout << i << ") " <<  << endl;
       
            (*Rbind).parseEvalQ("points(rx, ry, pch = 15, col=\"red\", cex = 3)");
            cout << i << ") rx: " << (int)rx << " ry: " << (int)ry <<" tx: " << (int)rx + side << " ty: " << (int)side - ry << "\tR value: " << m(side - ry, rx + side) << endl;
            /* acess is column major */
            INFO(i << " - (" << (int)rx << ", " << (int)ry << "), (" << side - ry << ", " << side - ry << ")\n" << m);
            
            (*Rbind).parseEvalQ("print(all_windows[i])");

            REQUIRE(m(side - ry, rx + side));
            m(side - ry, rx + side) = !m(side - ry, rx + side);
            //cout << endl << m << endl;
        });

        window.traverse([&m2, side, i](char rx, char ry, bool scope){
            (*Rbind)["rx"] = (int)rx;
            (*Rbind)["ry"] = (int)ry;

            /* Makes the relative position absolute */
            //cout << i << ") " <<  << endl;
       
            (*Rbind).parseEvalQ("points(rx, ry, pch = 15, col=\"red\", cex = 3)");
            cout << i << ") rx: " << (int)rx << " ry: " << (int)ry <<" tx: " << (int)rx + side << " ty: " << (int)side - ry << "\tR value: " << m2(side - ry, rx + side) << endl;
            /* acess is column major */
            INFO(i << " - (" << (int)rx << ", " << (int)ry << "), (" << side - ry << ", " << side - ry << ")\n" << m2);
            
            (*Rbind).parseEvalQ("print(all_windows[i])");

            REQUIRE(m2(side - ry, rx + side));
            m2(side - ry, rx + side) = !m2(side - ry, rx + side);
            //cout << endl << m << endl;
        });
        

        (*Rbind).parseEvalQ("axis(side = 1, at = seq(-5, 5, by = 1))");
        (*Rbind).parseEvalQ("axis(side = 2, at = seq(-5, 5, by = 1))");
        (*Rbind).parseEvalQ("grid(nx = NULL, ny = NULL, col = \"black\", lty = \"solid\", lwd = 1)");
        (*Rbind).parseEvalQ("print(all_windows[i])");


        bool has_left = (*Rbind).parseEval("any(all_windows[[i]] == TRUE)");
        cout << "Has Left: " << has_left << endl;
        REQUIRE(!has_left);

        bool has_left2 = (*Rbind).parseEval("any(all_windows[[j]] == TRUE)");
        cout << "Has Left: " << has_left2 << endl;
        REQUIRE(!has_left2);
        cout << "------------------------------------------------------------------------" << endl;
    }
    
    cout << "Second Half: " << second_half << endl;

}

/* 
        window.traverse([](char rx, char ry, bool scope){
            
            if(rotated == NOT_ROTATED){
                (*Rbind)["rx"] = (int)rx;
                (*Rbind)["ry"] = (int)ry;
                (*Rbind).parseEvalQ("points(rx, ry, pch = 15, col=\"red\", cex = 3)");
                cout << "rx: " << (int)rx << " ry: " << (int)ry << endl; 
            }
            else{
                (*Rbind)["rx"] = (int)rx;
                (*Rbind)["ry"] = (int)ry;
                (*Rbind).parseEvalQ("points(rx, ry, pch = 16, col=\"blue\", cex = 3)");
                cout << "rx: " << (int)rx << " ry: " << (int)ry << endl; 
            }
        });

*/