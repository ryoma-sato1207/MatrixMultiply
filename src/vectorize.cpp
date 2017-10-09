#include "matmul.h"

// TODO generarize.
// calculate only multiples of 4 dimension matrix
template <typename T> void vectorize(const T *a, const T *b, T *c, cont int size) {
  T sum[4];
  T tmp;
  for(int k = 0; k < size; ++k) {
    for(int i = 0; i < size; i += 4) {
      sum[0] = a[i * size + k];
      sum[1] = a[(i + 1) * size + k];
      sum[2] = a[(i + 2) * size + k];
      sum[3] = a[(i + 3) * size + k];
      for(int j = 0; j < size; ++j) {
        tmp = b[k * size + j];
        c[i * size + j] += sum[0] * tmp;
        c[(i + 1) * size + j] += sum[1] * tmp;
        c[(i + 2) * size + j] += sum[2] * tmp;
        c[(i + 3) * size + j] += sum[3] * tmp;
      }
    }
  }
  return;
}

