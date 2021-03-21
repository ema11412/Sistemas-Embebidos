#include <operaciones.h>
#include <stdio.h>

int main()
{
  float operation1 = add(1.5, 3.5);
  float operation2 = sub(4.0, 1.0);
  float operation3 = mul(9.0, 2.0);
  float operation4 = div(3.0, 3.0);
  float operation5 = root(9.0);

  printf("add = %.4f, sub = %.4f, mul = %.4f, div = %.4f. sqrt = %.4f \n", operation1, operation2, operation3, operation4, operation5);

  return 0;
}
