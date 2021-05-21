#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#define TIME_IN_MILLIS(ns) (ns * 1000000L)

#include <gpio.h>

int64_t
get_nanos( void )
{
  struct timespec ts;
  timespec_get(&ts, TIME_UTC);
  return (int64_t)(ts.tv_sec * 1000000000L + ts.tv_nsec);
}

void
wait_in_ms(int64_t ms)
{
  int64_t period = ms;
  int64_t nanos = get_nanos();
  int64_t last_nanos = nanos;
  do
  {
    nanos = get_nanos();
  } while ( nanos - last_nanos < period );
}

int total_time = 5000;

#if !defined(NDEBUG)
const char device[] = "gpiochip0";
#else
const char device[] = "/dev/gpiochip0";
#endif /* DEBUG */

typedef enum
{
  OFF = 0,
  ON = 1
} value_t;

int on_pin = 9; /* pin 21 */
int blink_pin = 25; /* pin 22 */
int read_pin = 24; /* pin 18 */

int
main( void )
{
  gpio_write(device, on_pin, ON);

  uint8_t blink_value = ON;
  gpio_result_t read_result;
  int millis_passed = 0;
  int iteration_time = 250; /* once per second */

  while (total_time - millis_passed > 0)
  {
    gpio_write(device, blink_pin, blink_value);
    read_result = gpio_read(device, read_pin);

    wait_in_ms( TIME_IN_MILLIS(iteration_time) );
    if ( read_result.result == FAILURE )
    {
      printf("could not read from pin %d\n", read_pin);
    }
    else
    {
      printf("value in pin %d: %d\n", read_pin, read_result.value);
    }

    if (blink_value == ON)
    {
      blink_value = OFF;
    }
    else
    {
      blink_value = ON;
    }
    millis_passed += iteration_time;
  }

  blink_value = OFF;
  gpio_write(device, on_pin, blink_value);
  wait_in_ms( TIME_IN_MILLIS(250) );
  gpio_write(device, blink_pin, blink_value);
  wait_in_ms( TIME_IN_MILLIS(250) );

  return 0;
}
