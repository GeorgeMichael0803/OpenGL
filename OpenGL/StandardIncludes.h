#ifndef STANDARD_INCLUDES_H
#define STANDARD_INCLUDES_H

// Include standard headers
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

// Windows specific includes and defines
#ifdef _WIN32
#include <windows.h>
#define M_ASSERT(_cond, _msg) \
    if (!(_cond)) { OutputDebugStringA(_msg); std::abort(); glfwTerminate(); }
#endif

// OpenGL/Helper headers
#include <GL/glew.h>      // Include GLEW
#include <GLFW/glfw3.h>   // Include GLFW
#include <glm/glm.hpp>    // Include GLM
#include <glm/gtc/matrix_transform.hpp> // View / Projection

#include "Resolution.h"
#include "Singleton.h"

#endif // STANDARD_INCLUDES_H

