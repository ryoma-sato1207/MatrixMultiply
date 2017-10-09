#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#ifdef _TIME
#include <chrono>
#endif

#include <immintrin.h>
#include <x86intrin.h>

int main() {
  const int size = 1024;
  double *a = new double[size * size];
  double *b = new double[size * size];
  double *c = new double[size * size];
#if 0 
  const int align = 32;
  double *a;
  double *b;
  posix_memalign(reinterpret_cast<void**>(&a), align, sizeof(double) * size * size);
  posix_memalign(reinterpret_cast<void**>(&y), align, sizeof(double) * size * size);
  free(x);
  free(y)
#endif

  return 0;
}

// normal
void matmul0(const double *a, const double *b, double *c, const int size) {
  double sum;
  for(int j = 0; j < size; ++j) {
    for(int i = 0; i < size; ++i) {
      sum = 0;
      for(int k = 0; k < size; ++k) {
        sum += a[i * size + k] * b[k * size +j];
      }
      c[i * size + j] = sum;
    }
  }
  return;
}

// consider cache hit
void matmul1(const double *a, const double *b, double *c, const int size) {
  double sum;
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

// consider vectorize and cache hit
// calculate only 4 times dimenstion matrix
void matmul2(const double *a, const double *b, double *c, const int size) {
  double sum[4];
  double tmp;
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

#if 0
// consider vectorize using AVX and cache hit
void matmul3(const double *a, const double *b, double *c, const int size) {
  __m256 vsum;
  __m256 tmp;
  __m256 _c;
  for(int k = 0; k < size; ++k) {
    for(int i = 0; i < size; i += 4) {
      vsum = _mm256_load_pd(a + (size * i + 4));
      for(int j = 0; j < size; ++j) {
        tmp = _mm256_load1_pd(b + (size * k + j));
        _c = _mm256_mul_pd(vsum, sum);
        _mm256_store_pd(c, (size * (i + 4) + j), _c);
      }
    }
  }
  return;
}
#endif

// consider blocking
void matmul4(const double *a, const double *b, double *c, const int size) {
  double sum;
  // block size depends on a system
  const int block = 4;
  for(int i = 0; i < size; ++i) {
    for(int j = 0; j < size; ++j) {
      sum = 0;
      for(int k = 0; k < block; ++k) {
        sum += a[i * size + k] * b[k * size + j];
      }
      c[i * size + j] += sum;
    }
  }
  return;
}

// merge matmul2 and matmul4
// calculate only 4 times dimenstion matrix
void matmul5(const double *a, const double *b, double *c, const int size) {
  double sum[4];
  double tmp;
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

// delete wasted address calculation in matmul5
// calculate only 4 times dimenstion matrix
void matmul6(const double *a, const double *b, double *c, const int size) {
  double sum[4];
  double tmp;
  double *ptmp;
  const double *ptmpc;
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

// TO DO
// write Strassen's algorithm
// write karatsuba algorithm
