/*constexpr array w0_arr = {
        Magic::Point{0, 1}, 
        Magic::Point{1, 1}, Magic::Point{1, 0}, Magic::Point{1, -1},
        Magic::Point{2, 1}, Magic::Point{2, 0}, Magic::Point{2, -1},
        Magic::Point{3, 1}, Magic::Point{3, 0}, Magic::Point{3, -1},
        Magic::Point{4, 1}, Magic::Point{4, 0}, Magic::Point{4, -1},
        Magic::Point{5, 1}, Magic::Point{5, 0}, Magic::Point{5, -1}
};
//constinit auto window0 = magic_points_factory<w0_arr, dimension_inner, 0>();

constexpr array w1_arr = {
        Magic::Point{1, -1}, Magic::Point{0, 1},
        Magic::Point{1, 1}, Magic::Point{1, 0},
        Magic::Point{2, 2}, Magic::Point{2, 1}, Magic::Point{2, 0},
        Magic::Point{3, 2}, Magic::Point{3, 1}, Magic::Point{3, 0},
        Magic::Point{4, 2}, Magic::Point{4, 1}, Magic::Point{4, 0},
        Magic::Point{5, 2}, Magic::Point{5, 1}, Magic::Point{5, 0}, 
};
//constinit auto window1 = magic_points_factory<w1_arr, dimension_inner, 1>();

constexpr array w2_arr = {
        Magic::Point{0, 1},
        Magic::Point{1, 1}, Magic::Point{1, 0}, Magic::Point{1, -1},
        Magic::Point{2, 2}, Magic::Point{2, 1}, Magic::Point{2, 0},
        Magic::Point{3, 2}, Magic::Point{3, 1},
        Magic::Point{4, 3}, Magic::Point{4, 2}, Magic::Point{4, 1},
        Magic::Point{5, 3}, Magic::Point{5, 2}, Magic::Point{5, 1}
    };
//constinit auto window2 = magic_points_factory<w2_arr, dimension_inner, 2>();

constexpr array w3_arr = {
        Magic::Point{0, 1}, Magic::Point{-1, 1}, 
        Magic::Point{1, 1}, Magic::Point{1, 0},
        Magic::Point{2, 2}, Magic::Point{2, 1}, Magic::Point{2, 0},
        Magic::Point{3, 2}, Magic::Point{3, 1},
        Magic::Point{4, 3}, Magic::Point{4, 2}, Magic::Point{4, 1},
        Magic::Point{5, 4}, Magic::Point{5, 3}, Magic::Point{5, 2}
};
//constinit auto window3 = magic_points_factory<w3_arr, dimension_inner, 3>();

constexpr array w4_arr = {
        Magic::Point{0, 1}, 
        Magic::Point{1, 1}, Magic::Point{1, 0}, Magic::Point{1, -1},
        Magic::Point{2, 2}, Magic::Point{2, 1}, Magic::Point{2, 0},
        Magic::Point{3, 3}, Magic::Point{3, 2}, Magic::Point{3, 1},
        Magic::Point{4, 4}, Magic::Point{4, 3}, Magic::Point{4, 2},
        Magic::Point{5, 5}, Magic::Point{5, 4}, Magic::Point{5, 3}
};
//constinit auto window4 = magic_points_factory<w4_arr, dimension_inner, 4>();

constexpr array w5_arr = {
        Magic::Point{0, 1},
        Magic::Point{1, 1}, Magic::Point{1, 0}, Magic::Point{1, 2}, 
        Magic::Point{2, 3}, Magic::Point{2, 2}, Magic::Point{2, 1},
        Magic::Point{3, 4}, Magic::Point{3, 3}, Magic::Point{3, 2},
        Magic::Point{4, 5}, Magic::Point{4, 4}, Magic::Point{4, 3},
        Magic::Point{5, 5}, Magic::Point{5, 4}
    };
//constinit auto window5 = magic_points_factory<w5_arr, dimension_inner, 5>();

constexpr array w6_arr = {
        Magic::Point{0, 1},
        Magic::Point{1, 3}, Magic::Point{1, 2}, Magic::Point{1, 1}, Magic::Point{1, 0},
        Magic::Point{2, 4}, Magic::Point{2, 3}, Magic::Point{2, 2}, Magic::Point{2, 1}, Magic::Point{2, 0},
        Magic::Point{3, 5}, Magic::Point{3, 4}, Magic::Point{3, 3}, Magic::Point{3, 2}, Magic::Point{3, 1},
        Magic::Point{4, 5}, Magic::Point{4, 4},
        Magic::Point{5, 5}
};
//constinit auto window6 = magic_points_factory<w6_arr, dimension_inner, 6>();

constexpr array w7_arr = {
        Magic::Point{0, 1},
        Magic::Point{1, 4}, Magic::Point{1, 3}, Magic::Point{1, 2}, Magic::Point{1, 1}, Magic::Point{1, 0},
        Magic::Point{2, 5}, Magic::Point{2, 4}, Magic::Point{2, 3}, Magic::Point{2, 2}, Magic::Point{2, 1}, Magic::Point{2, 0},
        Magic::Point{3, 5}, Magic::Point{3, 4},
        Magic::Point{4, 5}
};
//constinit auto window7 = magic_points_factory<w7_arr, dimension_inner, 7>();

constexpr array w8_arr = {
        Magic::Point{0, 4}, Magic::Point{0, 3}, Magic::Point{0, 2}, Magic::Point{0, 1},
        Magic::Point{1, 5}, Magic::Point{1, 4}, Magic::Point{1, 3}, Magic::Point{1, 2}, Magic::Point{1, 1}, Magic::Point{1, 0},
        Magic::Point{2, 5}, Magic::Point{2, 4}, Magic::Point{2, 3},
        Magic::Point{3, 5}
};
//constinit auto window8 = magic_points_factory<w8_arr, dimension_inner, 8>();

constexpr array w9_arr = {
        Magic::Point{0, 5}, Magic::Point{0, 4}, Magic::Point{0, 3}, Magic::Point{0, 2}, Magic::Point{0, 1},
        Magic::Point{1, 5}, Magic::Point{1, 4}, Magic::Point{1, 3}, Magic::Point{1, 2}, Magic::Point{1, 1}, Magic::Point{1, 0}, Magic::Point{1, -1}, 
        Magic::Point{2, 5}, Magic::Point{2, 4}, Magic::Point{2, 3}
};
//constinit auto window9 = magic_points_factory<w9_arr, dimension_inner, 9>();


//auto all_windows = tie(window0, window1, window2, window3, window4, window5, window6, window7, window8, window9);
auto hardcoded_windows = tie(w0_arr, w1_arr, w2_arr, w3_arr, w4_arr, w5_arr, w6_arr, w7_arr, w8_arr, w9_arr);
*/