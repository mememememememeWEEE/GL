#ifndef KXRM
#define KXRM

#ifdef __APPLE__
#define KXRM_PLATFORM_APPLE
#else

//#ifdef _WIN32
#define KXRM_PLATFORM_WINDOWS
#endif

#define STB_IMAGE_IMPLEMENTATION

#ifdef DEBUG
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG(...) 
#endif

namespace KXRP {};

#endif