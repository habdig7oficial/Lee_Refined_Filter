TEST_CASE("First integral pass", "[smooth_angles]"){
   (*Rbind).parseEvalQ("source(\"src/tests/smooth_angles/smooth_angles.R\")");

   int len = (*Rbind).parseEval("length(window_angle)");
   (*Rbind).parseEvalQ("i <- 1");


   for(int i = 0; i < len; i++){
        (*Rbind).parseEvalQ("validate(w, window_angle[i])");
        cout << i << endl;

        (*Rbind).parseEvalQ("i <- i + 1");
   }
}