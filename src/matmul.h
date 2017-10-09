#ifndef _H_MATRIX_MALUTIPLY_
#define _H_MATRIX_MALUTIPLY_
#include <iostream>

#include <cstddef>
#include <cstdlib>
#include <cstring>
#ifdef __MINGW32__
  #include <malloc.h>
#endif
#ifdef _TIME
  #include <chrono>
#endif

#ifdef ENABLE_AVX
  #ifdef __MINGW32__
    #include <intrin.h>
  #else
    #include <x86intrin.h>
  #endif
#endif

#endif // _H_MATRIX_MALUTIPLY_
