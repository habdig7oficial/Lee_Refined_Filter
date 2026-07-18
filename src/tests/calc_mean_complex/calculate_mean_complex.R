size <- 11
calculate_mean_complex <- function(window) {
    complex_values <- exp(1i * window)
    mean_complex <- mean(complex_values)
    mean_phase <- Arg(mean_complex)
    return(mean_phase)
}
