constexpr size_t len = dimension + 2;
constexpr size_t nglen = 2 * (dimension - 1);

TEST_CASE("First integral pass", "[smooth_angles]"){
   (*Rbind).parseEvalQ("source(\"src/tests/smooth_angles/smooth_angles.R\")");

   double l = (*Rbind).parseEval("length(window_angle)");
   (*Rbind).parseEvalQ("i <- 1");

   
   array<double, nglen> distance = adjust_angles(dist<double, len>(), angles);

   for(int i = 0; i < len; i++){
        double r_res = (*Rbind).parseEval("validate(w, window_angle[i])");

        REQUIRE(abs(r_res - distance[i]) < EPSILON);
        //cout << distance[i] << endl;

        (*Rbind).parseEvalQ("i <- i + 1");
   }
}

TEST_CASE("Vector test", "[sm_vec]"){
  array<double, len> distance = dist<double,len>();

  (*Rbind).parseEvalQ("w <- 1 / sqrt((1:13 - 6)^2 + (1:13 - 6)^2)");
  (*Rbind).parseEvalQ("w[6] <- 0  # Delete masked pixels");


  (*Rbind).parseEvalQ("i <- 1");
  for(int i = 0; i < len; i++){
    double r_res = (*Rbind).parseEval("w[[i]]");

    REQUIRE(abs(distance[i] - r_res) < EPSILON);

    (*Rbind).parseEvalQ("i <- i + 1");
  }

}

TEST_CASE("First integral pass", "[smooth_angles2]"){
   (*Rbind).parseEvalQ("source(\"src/tests/smooth_angles/smooth_angles.R\")");

   double l = (*Rbind).parseEval("length(window_angle)");
   (*Rbind).parseEvalQ("i <- 1");
   (*Rbind).parseEvalQ("j <- 1");

   
array<array<double, nglen>, nglen> test = diff(dist<double, len>(), angles);


   for(int i = 0; i < nglen; i++){
      NumericVector r_res = (*Rbind).parseEval("validate_diff(w, window_angle[i])");
       for(int j = 0; j < nglen; j++){

        REQUIRE(abs(r_res[j] - test[i][j]) < EPSILON);
        cout << r_res[j] << " - " << test[i][j] << endl;

        (*Rbind).parseEvalQ("j <- j + 1");
       }
        (*Rbind).parseEvalQ("i <- i + 1");
        (*Rbind).parseEvalQ("j <- 1");
   }
}
