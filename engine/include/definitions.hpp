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

#define MAX_BONE_INFLUENCE 4