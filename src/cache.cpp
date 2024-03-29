#include "matmul.h"

template <typename T> void cache(const T *a, const T *b, T *c, const int size) {
  T sum;
  for(int i = 0; i < size; ++i) {
    for(int j = 0; j < size; ++j) {
      sum = 0;
      for(int k = 0; k < size; ++k) {
        sum += a[i * size + k] * b[k * size + j];
      }
      c[i * size + j] = sum;
    }
  }
  return;
}
