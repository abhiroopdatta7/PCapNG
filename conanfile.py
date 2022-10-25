from conans import ConanFile, CMake, tools
import os
import sys


class PCapNG(ConanFile):
    name = "pcapng-cpp"
    # version = ""
    # license = ""
    author = "Abhiroop Datta"
    url = "https://github.com/abhiroopdatta7/PCapNG"
    description = "PCap Next Gen C++ library"
    settings = "os", "compiler", "build_type"
    options = {
        "shared": [True, False],
    }

    default_options = {
        "shared": True,
    }
    default_settings = {
        "build_type": "Release"
    }
    requires = []

    generators = "cmake", "cmake_find_package"

    exports_sources = ["*"]

    def set_version(self):
        self.version = os.environ['PCapNG_VERSION']

    def package_id(self):
        self.info.settings.compiler.version = "9"
        del self.info.settings.compiler.libcxx

    def build(self):
        cmake = CMake(self)
        cmake.verbose = True
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="pcapng-lib")
        self.copy("*", dst="bin", src="bin")
        if self.options.shared:
            self.copy("*.so", keep_path=True)
        else:
            self.copy("*.a", keep_path=True)

    def package_info(self):
        self.cpp_info.libs = ["pcapng-cpp"]

    # def imports(self):
    #     self.copy('*.so.*', dst='lib', src='lib')
    #     self.copy('*.so', dst='lib', src='lib')
    #     self.copy('*.a', dst='lib', src='lib')
    #     self.copy('*.h', dst='include', src='include')
    #     self.copy('*', dst='bin', src='bin')
