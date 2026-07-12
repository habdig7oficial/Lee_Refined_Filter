TEST_CASE("First integral pass", "[first_pass]"){
    (*Rbind).parseEvalQ("source(\"src/tests/first_integral_pass/filtragem_img_simulada.R\")");

    (*Rbind)["img"] = IMG;
    (*Rbind)["coherence"] = COHERENCE;

    (*Rbind).parseEval("exec(img, coherence)");
}