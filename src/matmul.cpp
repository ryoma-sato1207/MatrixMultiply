#include "matmul.h"

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
