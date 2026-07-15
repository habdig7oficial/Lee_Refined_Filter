TEST_CASE("First integral pass", "[magic_points]"){
    (*Rbind).parseEvalQ("plot(0,0, xlim = c(-5, 5), ylim = c(-5, 5))");
    
    window4.traverse([](char rx, char ry, bool scope){
        if(scope == SIDE_A || true){
            (*Rbind)["rx"] = (int)rx;
            (*Rbind)["ry"] = (int)ry;
            (*Rbind).parseEvalQ("points(rx, ry, pch = 15, col=\"red\", cex = 3)");
            cout << "rx: " << (int)rx << " ry: " << (int)ry << endl; 
        }
        else
            cout << endl;
    });




    (*Rbind).parseEvalQ("axis(side = 1, at = seq(-5, 5, by = 1))");
    (*Rbind).parseEvalQ("axis(side = 2, at = seq(-5, 5, by = 1))");
    (*Rbind).parseEvalQ("grid(nx = NULL, ny = NULL, col = \"black\", lty = \"solid\", lwd = 1)");
    
}