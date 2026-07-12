#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_get_random_seed.hpp"
#include "random"
#include "math.h"
#include "../lib/filter.hpp"

#define EPSILON 1e-14
#define REPETITION 10

#define IMG "img/Simulated/phi_raster_noisy.tif"
#define COHERENCE "img/Simulated/map_coherence_gierull.tif"
#define IMG_TYPE float