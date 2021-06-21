#include <unistd.h> /* usleep */
#include <gpio.h>
#include <stdio.h>

int main()
{
  gpio_init_ptrs();
  gpio_set_mode_all(1);

  gpio_get_mode_all();

  gpio_write_all(1);
  gpio_read(4);

  usleep(1000000);

  gpio_write_all(0);
  gpio_read(4);



  return 0;
}