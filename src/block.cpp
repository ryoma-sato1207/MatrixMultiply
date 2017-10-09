#include "matmul.h"

// TODO generalize.
// calculate only multiples of 4 dimension matrix
template <typename T> void block(const T *a, const T *b, T *c, const int size) {
  T sum[4];
  T tmp;
  // block size depends on a system
  const int block = 4;
  for(int i0 = 0; i0 < size; i0 += block) {
    for(int j0 = 0; j0 < size; j0 += block) {
      for(int k0 = 0; k0 < size; k0 += block) {
        for(int i = i0; i < i0 + block; ++i) {
          for(int j = j0; j < j0 + block; j += 4) {
            sum[0] = 0;
            sum[1] = 0;
            sum[2] = 0;
            sum[3] = 0;
            for(int k = k0; k < k0 + block; ++k) {
              tmp = a[i * size + k];
              sum[0] += tmp * b[k * size + j];
              sum[1] += tmp * b[k * size + j + 1];
              sum[2] += tmp * b[k * size + j + 2];
              sum[3] += tmp * b[k * size + j + 3];
            }
            c[i * size + j] += sum[0];
            c[i * size + j + 1] += sum[1];
            c[i * size + j + 2] += sum[2];
            c[i * size + j + 3] += sum[3];
          }
        }
      }
    }
  }
  return;
}
