#include "matmul.h"

// TODO generalize.
// calculate only multiples of 4 dimension matrix
template <typename T> void address(const T *a, const T *b, T *c, const int size) {
  T sum[4];
  T tmp;
  T *ptmp;
  const T *ptmpc;
  // block size depends on a system
  const int block = 4;
  for(int i0 = 0; i0 < size; i0 += block) {
    for(int j0 = 0; j0 < size; j0 += block) {
      for(int k0 = 0; k0 < size; k0 += block) {
        for(int i = i0; i < i0 + block; ++i) {
          for(int j = j0; j < j0 + block; j += 4) {
            sum[0] = 0;
            *(double *)(sum + 1) = 0;
            *(double *)(sum + 2) = 0;
            *(double *)(sum + 3) = 0;
            ptmpc = &b[k0 * size + j];
            for(int k = k0; k < k0 + block; ++k) {
              tmp = a[i * size + k];
              sum[0] += tmp * (*ptmpc);
              *(double *)(sum + 1) += tmp * (*(double *)(ptmpc + 1));
              *(double *)(sum + 2) += tmp * (*(double *)(ptmpc + 2));
              *(double *)(sum + 3) += tmp * (*(double *)(ptmpc + 3));
              ptmpc = (double *)(ptmpc + size);
            }
            ptmp = &c[i * size + j];
            *ptmp += *sum;
            *(double *)(ptmp + 1) += *(double *)(sum + 1);
            *(double *)(ptmp + 2) += *(double *)(sum + 2);
            *(double *)(ptmp + 3) += *(double *)(sum + 3);
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
