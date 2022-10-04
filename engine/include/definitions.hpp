#define SCREEN_WIDTH 2560
#define SCREEN_HEIGHT 1440

#if defined(_WIN64)
    #define PLATFORM_NAME "Windows 64-Bit"
    #define PLATFORM_SUPERKEY "CTRL"
#elif defined(__APPLE__) && defined(__MACH__)
    #define PLATFORM_NAME "macOS 64-Bit"
    #define PLATFORM_SUPERKEY "CMND"
#elif defined(__linux__)
    #define PLATFORM_NAME "Linux 64-Bit"
    #define PLATFORM_SUPERKEY "CTRL"
#else
    #define PLATFORM_NAME "Unknown 64-bit OS"
    #define PLATFORM_SUPERKEY "CTRL"
#endif

#include <iostream>

#include "../external/imgui-docking/imgui.h"
#include "../external/imgui-docking/backends/imgui_impl_glfw.h"
#include "../external/imgui-docking/backends/imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// GLM (OpenGL Maths library so that we don't have to write our own!)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// using namespace glm;
using namespace std;

#include <map>
#include <cmath>

#include <fstream>
#include <string>
#include <sstream>

#include <string.h>
#include <vector>