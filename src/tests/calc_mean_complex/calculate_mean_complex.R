size <- 11
calculate_mean_complex <- function(window) {
    complex_values <- exp(1i * window)
    mean_complex <- mean(complex_values)
    mean_phase <- Arg(mean_complex)
    
    print("WILL IT WORK?")
    print(sum(cos(window)))
    #print(atan2(mean(sin(window)), mean(cos(window))))
    return(mean_phase)
}
