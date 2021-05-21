#ifndef GPIO_H
#define GPIO_H

#include <stdint.h> /* uint8_t */

typedef enum
{
  FAILURE,
  SUCCESS
} gpio_op_result_t;

typedef struct
{
  char* device;
  int offset;
  uint8_t value;
} gpio_op_t;

typedef struct
{
  int result;
  int value;
} gpio_result_t;

/*
 * example { .dev = "/dev/gpiochip0", .offset = 17, .mode = GPIO_READ, .val = 0 }
 */

extern int const valid_offsets[];

gpio_result_t
gpio_read(const char *dev_name, int offset);

gpio_result_t
gpio_write(const char *dev_name, int offset, uint8_t value);

void
init_gpio_op(gpio_op_t* const o);

void
init_gpio_result(gpio_result_t* const r);

#endif /* GPIO_H */
