#include "matmul.h"

#ifdef ENABLE_AVX
void avx(const double *a, const double *b, double *c, const int size) {
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

void avx(const float *a, const float *b, float *c, const int size) {
  __m256 vsum;
  __m256 tmp;
  __m256 _c;
  for(int k = 0; k < size; ++k) {
    for(int i = 0; i < size; i += 8) {
      vsum = _mm256_load_pd(a + (size * i + 8));
      for(int j = 0; j < size; ++j) {
        tmp = _mm256_load1_pf(b + (size * k + j));
        _c = _mm256_mul_ps(vsum, sum);
        _mm256_store_pd(c, (size * (i + 8) + j), _c);
      }
    }
  }
  return;
}
#endif
