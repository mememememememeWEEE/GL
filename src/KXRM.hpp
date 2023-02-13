#pragma once

#define STB_IMAGE_IMPLEMENTATION

#ifdef DEBUG
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG(...) 
#endif



namespace KXRP {};