#include <stdio.h>
#include <timer.h>
#include <math.h>

int main()
{
  unsigned int randArray[10];

  startTimer();

  unsigned int time1 = getTimerValue();

  for (int i = 0; i < 10; ++i)
  {
    randArray[i] = getRandomNumber(100, 10);
  }

  unsigned int time2 = getTimerValue();

  stopTimer();

  for (int i = 0; i < 10; ++i)
  {
    printf("Random Array [%d] = %u \n", i, randArray[i]);
  }


  double execution = getExecutionTime(time2, time1);
  printf("Execution Time = %f\n", execution);

  return 0;
}