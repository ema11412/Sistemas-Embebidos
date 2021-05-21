#include <gpio.h>

#include <linux/gpio.h> /* gpiohandle_* structs, GPIO.* macros */
#include <fcntl.h> /* O_RDONLY, O_WRONLY */
#include <string.h> /* strerror() */
#include <errno.h> /* errno */
#include <sys/ioctl.h> /* ioctl() */
#include <stdio.h> /* printf() */
#include <stdlib.h> /* NULL */
#include <unistd.h> /* close(fd) */

/* the actual numbers are the "offsets"
 * the comments explains the pinout on the board */
int const valid_offsets[] = {
  /* PIN 01 -        - 3.3V   */
  /* PIN 02 -        - 5V     */
  /* PIN 03 - BCM 02 - SDA    */ 2,
  /* PIN 04 -        - 5V     */
  /* PIN 05 - BCM 03 - SCL    */ 3,
  /* PIN 06 -        - GND    */
  /* PIN 07 - BCM 04 - GPCLK0 */ 4,
  /* PIN 08 - BCM 14 - TXD    */ 14,
  /* PIN 09 -        - GND    */
  /* PIN 10 - BCM 15 - RXD    */ 15,
  /* PIN 11 - BCM 17 -        */ 17,
  /* PIN 12 - BCM 18 -        */ 18,
  /* PIN 13 - BCM 27 -        */ 27,
  /* PIN 14 -        - GND    */
  /* PIN 15 - BCM 22 -        */ 22,
  /* PIN 16 - BCM 23 -        */ 23,
  /* PIN 17 -        - 3.3V   */
  /* PIN 18 - BCM 24 -        */ 24,
  /* PIN 19 - BCM 10 - MOSI   */ 10,
  /* PIN 20 -        - GND    */
  /* PIN 21 - BCM 09 -        */ 9,
  /* PIN 22 - BCM 25 -        */ 25,
  /* PIN 23 - BCM 11 - SCLK   */ 11,
  /* PIN 24 - BCM 08 - CE0    */ 8,
  /* PIN 25 -        - GND    */
  /* PIN 26 - BCM 07 - CE1    */ 7,
  /* PIN 27 - BCM 00 - ID_SD  */ 0,
  /* PIN 28 - BCM 01 - ID_SC  */ 1,
  /* PIN 29 - BCM 05 -        */ 5,
  /* PIN 30 -        - GND    */
  /* PIN 31 - BCM 06 -        */ 6,
  /* PIN 32 - BCM 12 - PWM0   */ 12,
  /* PIN 33 - BCM 13 - PWM1   */ 13,
  /* PIN 34 -        - GND    */
  /* PIN 35 - BCM 19 - MISO   */ 19,
  /* PIN 36 - BCM 16 -        */ 16,
  /* PIN 37 - BCM 26 -        */ 26,
  /* PIN 38 - BCM 20 - MOSI   */ 20,
  /* PIN 39 -        - GND    */
  /* PIN 40 - BCM 21 - SCLK   */ 21,
};

typedef struct gpiohandle_request gpiohandle_request;
typedef struct gpiohandle_data gpiohandle_data;

gpio_result_t
gpio_write(const char *dev_name, int offset, uint8_t value)
{
  gpio_result_t result;
  gpiohandle_request rq;
  gpiohandle_data data;
  int fd;
  int ret;
  init_gpio_result(&result);
  #if !defined(NDEBUG)
  printf("Write value %d to GPIO at offset %d (OUTPUT mode) on chip %s\n", value, offset, dev_name);
  #endif /* DEBUG PRINT */
  fd = open(dev_name, O_RDONLY);
  if (fd < 0)
  {
    fprintf(stderr, "Unable to open %s: %s", dev_name, strerror(errno));
    return result;
  }
  #if !defined(NDEBUG)
  return result;
  #endif /* DEBUG PRINT */
  rq.lineoffsets[0] = offset;
  rq.flags = GPIOHANDLE_REQUEST_OUTPUT;
  rq.lines = 1;
  ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &rq);
  close(fd);
  if (ret == -1)
  {
    fprintf(stderr, "Unable to line handle from ioctl : %s", strerror(errno));
    return result;
  }
  data.values[0] = value;
  ret = ioctl(rq.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
  if (ret == -1)
  {
    fprintf(stderr, "Unable to set line value using ioctl : %s", strerror(errno));
  }
  close(rq.fd);
  result.result = SUCCESS;
  return result;
}

gpio_result_t
gpio_read(const char *dev_name, int offset)
{
  gpio_result_t result;
  gpiohandle_request rq;
  gpiohandle_data data;
  int fd;
  int ret;
  init_gpio_result(&result);
  fd = open(dev_name, O_RDONLY);
  if (fd < 0)
  {
    fprintf(stderr,"Unabled to open %s: %s", dev_name, strerror(errno));
    return result;
  }
  #if !defined(NDEBUG)
  result.result = SUCCESS;
  return result;
  #endif /* DEBUG PRINT */
  rq.lineoffsets[0] = offset;
  rq.flags = GPIOHANDLE_REQUEST_INPUT;
  rq.lines = 1;
  ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &rq);
  close(fd);
  if (ret == -1)
  {
    fprintf(stderr, "Unable to get line handle from ioctl : %s", strerror(errno));
    return result;
  }
  ret = ioctl(rq.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
  if (ret == -1)
  {
    fprintf(stderr, "Unable to get line value using ioctl : %s", strerror(errno));
  }
  else
  {
    result.result = SUCCESS;
    result.value = data.values[0];
    #if !defined(NDEBUG)
    fprintf(stderr, "Value of GPIO at offset %d (INPUT mode) on chip %s: %d\n", offset, dev_name, data.values[0]);
    #endif /* DEBUG PRINT */
  }
  close(rq.fd);
  return result;
}

void
init_gpio_op(gpio_op_t* const o)
{
  o->value = 0;
  o->device = NULL;
}

void
init_gpio_result(gpio_result_t* const r)
{
  r->result = FAILURE;
  r->value = 0;
}
