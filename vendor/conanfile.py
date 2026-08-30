from conan import ConanFile
from conan.tools.files import copy

class BoostConsumer(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        # Specify your desired Boost version
        self.requires("boost/1.84.0")

    def generate(self):
        boost = self.dependencies["boost"]
        # Copies all header files from the cache into a local ./include/boost folder
        copy(self, "*", src=boost.cpp_info.includedirs[0], dst="include/boost")