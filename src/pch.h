#pragma once

#define TRISYCL_OPENCL
#define BOOST_COMPUTE_USE_CPP11

//standart libraries
#include <iostream>
#include <array>
#include <set>
#include <fstream>
#include <future>
#include <math.h>
#include <algorithm>

//deps
#include "CL/sycl.hpp"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "imgui.h"

#include "GLAbstraction/Renderer.h"