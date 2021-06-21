#include <sys/mman.h> /* mmap */
#include <err.h>      /* error handling */
#include <fcntl.h>    /* file ops */
#include <unistd.h>   /* usleep */
#include <stdio.h>
#include <string.h>
#include <math.h>

/* Static base address */
static unsigned GPIO_BASE = 0x3f200000;

/* Register pointers */
volatile unsigned int *gpfsel0;
volatile unsigned int *gpset0;
volatile unsigned int *gpclr0;
volatile unsigned int *gplev0;

/* Initialize pointers: performs memory mapping, exits if mapping fails */
void gpio_init_ptrs(void)
{
  int fd = -1;

  /* Loading /dev/mem into a file */
  if ((fd = open("/dev/mem", O_RDWR, 0)) == -1)
  {
    err(1, "Error Opening /dev/mem\n");
  }

  /* Mapping GPIO base physical address */
  gpfsel0 = (unsigned int *)mmap(0, getpagesize(), PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);

  if (gpfsel0 == MAP_FAILED)
  {
    errx(1, "Error during mapping GPIO\n");
  }

  /* Set register pointers */
  /* offset 0x1C / 4 = 0x7 */
  gpset0 = gpfsel0 + 0x7;

  /* offset 0x28 / 4 = 0xA */
  gpclr0 = gpfsel0 + 0xA;

  /* offset 0x34 / 4 = 0xD */
  gplev0 = gpfsel0 + 0xD;
}

void gpio_set_mode_all(int mode)
{
  char cmode[3];
  char bits[32];
  memset(bits, '0', 32);

  for (int i = 0; i < 3; ++i)
  {
    cmode[i] = (mode % 2) + '0';
    mode /= 2;
  }

  int index = 6;
  while (index <= 27)
  {
    bits[index] = cmode[0];
    bits[index + 1] = cmode[1];
    bits[index + 2] = cmode[2];
    index += 3;
  }

  int result = 0;

  for (int i = 0; i < 32; ++i)
  {
    result += (bits[i] - '0') * pow(2, i);
  }

  *gpfsel0 = *gpfsel0 | result;
}

void gpio_set_mode(int pin, int mode)
{
  char bits[32];
  memset(bits, '0', 32);

  int BASE = pin * 3;

  for (int i = 0; i < 3; ++i)
  {
    bits[BASE + i] = (mode % 2) + '0';
    mode /= 2;
  }

  int result = 0;

  for (int i = 0; i < 32; ++i)
  {
    result += (bits[i] - '0') * pow(2, i);
  }

  *gpfsel0 = *gpfsel0 | result;
}

void gpio_write_all(unsigned char bit)
{
  if (bit)
  {
    printf("All bits set to 1\n", 0x2FC);
    *gpset0 = *gpset0 | 0x2FC;
  }
  else
  {
    printf("All bits set to 0\n", 0x2FC);
    *gpclr0 = *gpclr0 | 0x2FC;
  }
}

void gpio_write(int pin, unsigned char bit)
{
  if (bit)
  {
    printf("Pin %d set to 1\n", pin);
    *gpset0 = (1 << pin);
  }
  else
  {
    printf("Pin %d set to 0\n", pin);
    *gpclr0 = (1 << pin);
  }
}

void gpio_read_all(void)
{
  unsigned int bits = *gplev0;

  for (int i = 2; i < 10; ++i)
  {
    printf("Pin %d is set to %d\n", i, (bits >> i) & 0x1);
  }
}

void gpio_read(int pin)
{
  unsigned int bits = *gplev0;
  bits >>= pin;
  bits &= 0x1;

  printf("Pin %d set to %d\n", pin, bits);
}

void gpio_get_mode_all(void)
{
  unsigned int bits = *gpfsel0;

  for (int i = 2; i < 10; ++i)
  {
    printf("Pin %d is in mode %d\n", i, (bits >> (i * 3)) & 0x7);
  }
}

void gpio_get_mode(int pin)
{
  unsigned int bits = *gpfsel0;

  bits >>= (pin * 3);
  bits &= 0x7;

  printf("Pin %d is in mode %d\n", pin, bits);
}