#include <operaciones.h>
#include <stdio.h>



int main()
{
  float op1 = add(1.7, 6.4);
  float op2 = sub(4.0, 2.2);
  float op3 = mul(9.0, 3.0);
  float op4 = div(3.0, 3.0);
  float op5 = square_root(9.0);


  printf("add = %.4f, sub = %.4f, mul = %.4f, div = %.4f. sqrt = %.4f \n", op1, op2, op3, op4, op5);

  return 0;
}
