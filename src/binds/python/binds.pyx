# distutils: language = c++

cdef extern from "opencv2/opencv.hpp" namespace "cv":
  cdef cppclass Mat:
    Mat() except +	

cdef extern from "../../lib/filter.hpp" :
  cpdef void strideImg(Mat &, Mat &, int)	