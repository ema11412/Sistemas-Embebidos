#include <math.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

unsigned int hex2dec(char *hex)
{
  unsigned int value = 0;
  unsigned int decimal = 0;


  int counter = 8;
  counter--;

  for (int i = 0; i < 8; i++)
  {
    /* Find the decimal representation of hex[i] */
    if (hex[i] >= '0' && hex[i] <= '9')
    {
      value = hex[i] - 48;
    }
    else if (hex[i] >= 'a' && hex[i] <= 'f')
    {
      value = hex[i] - 97 + 10;
    }
    else if (hex[i] >= 'A' && hex[i] <= 'F')
    {
      value = hex[i] - 65 + 10;
    }

    decimal += value * pow(16, counter);
    counter--;
  }

  return decimal;
}

int startTimer(void)
{
  int file;

  file = open("/dev/timer", O_WRONLY);
  if (file == -1)
  {
    fprintf(stderr, "Failed to open timer for start!\n");
    return -1;
  }

  write(file, "1", 1);
  close(file);
}

int stopTimer(void)
{
  int file;

  file = open("/dev/timer", O_WRONLY);
  if (file == -1)
  {
    fprintf(stderr, "Failed to open timer for stop!\n");
    return -1;
  }

  write(file, "0", 1);
  close(file);
}

unsigned int getTimerValue(void)
{
  char strValue[8];
  memset(strValue, 0, 8);
  int file;
  int bytes;

  file = open("/dev/timer", O_RDONLY);
  if (file == -1)
  {
    fprintf(stderr, "Failed to open timer value for reading!\n");
    return (-1);
  }

  if (bytes = read(file, strValue, 8) == -1)
  {
    fprintf(stderr, "Failed to read value!\n");
    return (-1);
  }

  close(file);

  return hex2dec(strValue);
}

unsigned int getRandomNumber(unsigned int upper, unsigned int lower)
{
  unsigned int random = getTimerValue();

  return (random % (upper - lower + 1)) + lower;
}

double getExecutionTime(unsigned int upperTime, unsigned int lowerTime)
{
  unsigned int difference = upperTime - lowerTime;

  return (difference / 0.3E9);
}