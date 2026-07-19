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

TEST_CASE("Vector test", "[sm_vec]"){
  constexpr size_t len = DIMENSION + 2;
  array<double, len> distance = dist<len>();

  (*Rbind).parseEvalQ("w <- 1 / sqrt((1:13 - 6)^2 + (1:13 - 6)^2)");
  (*Rbind).parseEvalQ("w[6] <- 0  # Delete masked pixels");


  (*Rbind).parseEvalQ("i <- 1");
  for(int i = 0; i < len; i++){
    double r_res = (*Rbind).parseEval("w[[i]]");

    REQUIRE(abs(distance[i] - r_res) < EPSILON);

    (*Rbind).parseEvalQ("i <- i + 1");
  }

}