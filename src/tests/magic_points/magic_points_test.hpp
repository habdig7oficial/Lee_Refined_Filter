TEST_CASE("First integral pass", "[magic_points]"){
    (*Rbind).parseEvalQ("source(\"src/tests/magic_points/magic_points_test.R\")");
    (*Rbind).parseEvalQ("png(\"magic_point.png\", width = 1920, height = 1080)");
    (*Rbind).parseEvalQ("par(mfrow = c(2, 5))");

    int size = (*Rbind)["size"];
    int side = size / 2;
    for(int i = 0; i < all_windows.size(); i++){
        MagicPoints window = all_windows[i];
        (*Rbind)["i"] = i + 1;

        (*Rbind).parseEvalQ("plot(0,0, xlim = c(-5, 5), ylim = c(-5, 5))");
        LogicalMatrix m = (*Rbind).parseEval("all_windows[[i]]");

        window.traverse([&m, side, i](char rx, char ry, bool scope){
            (*Rbind)["rx"] = (int)rx;
            (*Rbind)["ry"] = (int)ry;

            /* Makes the relative position absolute */
            //cout << i << ") " <<  << endl;
       
            (*Rbind).parseEvalQ("points(rx, ry, pch = 15, col=\"red\", cex = 3)");
            cout << "rx: " << (int)rx + side << " ry: " << (int)ry + side << "\tR value: " << m(ry + side, rx + side) << endl;
            /* acess is column major */
            INFO(i << " - (" << (int)rx << ", " << (int)ry << ")\n" << m);
            REQUIRE(m(ry + side, rx + side));
            m(ry + side, rx + side) = !m(ry + side, rx + side);
            //cout << endl << m << endl;
        });

        (*Rbind).parseEvalQ("axis(side = 1, at = seq(-5, 5, by = 1))");
        (*Rbind).parseEvalQ("axis(side = 2, at = seq(-5, 5, by = 1))");
        (*Rbind).parseEvalQ("grid(nx = NULL, ny = NULL, col = \"black\", lty = \"solid\", lwd = 1)");
        (*Rbind).parseEvalQ("print(all_windows[i])");


        bool has_left = (*Rbind).parseEval("any(all_windows[[i]] == TRUE)");
        cout << "Has Left: " << has_left << endl;
        REQUIRE(!has_left);
    }
        
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