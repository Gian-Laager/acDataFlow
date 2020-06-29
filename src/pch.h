#pragma once

//#define TRISYCL_OPENCL
//#define TRISYCL_USE_OPENCL_ND_RANGE
#define OMP_NUM_THREADS 8
#define BOOST_COMPUTE_USE_CPP11

//standart libraries
#include <iostream>
#include <array>
#include <set>
#include <fstream>
#include <future>
#include <math.h>
#include <algorithm>
#include <functional>
#include <chrono>
#include <vector>

//deps
#include "CL/sycl.hpp"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "imgui.h"

#include "GLAbstraction/Renderer.h"