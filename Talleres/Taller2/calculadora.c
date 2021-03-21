#include <biblioteca.h>
#include <stdio.h>

int main() {
  float op1 = add(1.5, 5.4);
  float op2 = sub(4.5, 1.2);
  float op3 = mul(4.0, 2.3);
  float op4 = div(3.4, 3.4);


  printf("add = %.4f, sub = %.4f, mul = %.4f, div = %.4f. sqrt = %.4f \n", op1, op2, op3, op4);

  return 0;
}

