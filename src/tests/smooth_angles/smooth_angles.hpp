TEST_CASE("First integral pass", "[smooth_angles]"){
   (*Rbind).parseEvalQ("source(\"src/tests/smooth_angles/smooth_angles.R\")");

   (*Rbind).parseEvalQ("print(w)");
}