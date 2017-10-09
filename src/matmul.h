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

template <typename T> void normal(const T *a, const T *b, T *c, const int size);
template <typename T> void cache(const T *a, const T *b, T *c, const int size);
template <typename T> void vectorize(const T * a, const T *b, T *c, const int size);
void avx(const double *a, const double *b, double *c, const int size);
void avx(const float *a, const float *b, float *c, const int size);
template <typename T> void block(const T *a, const T *b, T *c, const int size);
template <typename T> void address(const T *a, const T *b, T *c, const int size);

#endif // _H_MATRIX_MALUTIPLY_
