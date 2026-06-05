from setuptools import Extension, setup
from Cython.Build import cythonize

ext_modules = [
    Extension("binds",
              sources=["binds.pyx"],
              include_dirs=["/usr/include/opencv4"],
              libraries=["m"]  # Unix-like specific
              )
]

setup(name="LeeFilter",
      ext_modules=cythonize(ext_modules))
