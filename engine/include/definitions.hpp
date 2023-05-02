#define SCREEN_WIDTH 2560
#define SCREEN_HEIGHT 1440

#if defined(_WIN64)
    #define PLATFORM_NAME "Windows 64-Bit"
    #define PLATFORM_SUPERKEY "CTRL"
    #define PLATFORM_UI_GL_VERSION "#version 410"
#elif defined(__APPLE__) && defined(__MACH__)
    #define PLATFORM_NAME "macOS 64-Bit"
    #define PLATFORM_SUPERKEY "CMND"
    #define PLATFORM_UI_GL_VERSION "#version 410"
#elif defined(__linux__) && defined(__aarch64__)
    #define PLATFORM_NAME "Raspberry Pi ARM64"
    #define PLATFORM_SUPERKEY "CTRL"
    #define PLATFORM_UI_GL_VERSION "#version 300 es"
#elif defined(__linux__)
    #define PLATFORM_NAME "Linux 64-Bit"
    #define PLATFORM_SUPERKEY "CTRL"
    #define PLATFORM_UI_GL_VERSION "#version 410"
#else
    #define PLATFORM_NAME "Unknown 64-bit OS"
    #define PLATFORM_SUPERKEY "CTRL"
    #define PLATFORM_UI_GL_VERSION "#version 410"
#endif

// Determine the appropriate modifier key based on the operating system
#if defined(_WIN32) || defined(__linux__)
#define MODIFIER_KEY GLFW_MOD_CONTROL
#elif defined(__APPLE__)
#define MODIFIER_KEY GLFW_MOD_SUPER
#endif

#define MAX_BONE_INFLUENCE 4