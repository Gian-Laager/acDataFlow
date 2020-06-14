# acDataFlow

This is a little library which uses SYCL to work very fast with vectors on the GPU or on AVX. It should be very easy to use.

### Installation

- Create your project with CMake. 
- Set the variable `AC_DATA_FLOW_ROOT_DIR` to the root directory of the acDataFlow library. 
- Then include the acDataFlow CMakeLists.txt like this `include(${AC_DATA_FLOW_ROOT_DIR}/CMakeLists.txt)`
- Copy the `triSYCLConfig.cmake.in` file from the cmake folder in the library in to the cmake folder in your project
- To build boost open a terminal, open the folder `path/to/acDataFlow/deps/boost` and run `./bootstrap.sh`(on macOS) or `.\bootstrap.bat` (on Windows)
- Then you need to execute the `b2` program (via terminal or finder etc)
- Now set the variable `CMAKE_GNUC_COMPILER` in your CMakeLists file to a gcc compiler (version >= 1.65)
- And the variable `CMAKE_GNUCXX_COMPILER` to a g++ compiler (version >= 1.65)