#include <unistd.h> /* usleep */
#include <gpio.h>
#include <stdio.h>

int main()
{
  gpio_init_ptrs();
  /* gpio_set_mode(2, 1);
  gpio_set_mode(3, 1);
  gpio_set_mode(4, 0); */
  gpio_set_mode_all(1);

  gpio_get_mode_all();

  /* gpio_write(2, 1);
  gpio_write(3, 1); */
  gpio_write_all(1);
  gpio_read(4);
  /* gpio_read_all(); */

  usleep(1000000);

  /* gpio_write(2, 0);
  gpio_write(3, 0); */
  gpio_write_all(0);
  gpio_read(4);
  /* gpio_read_all(); */

  return 0;
}