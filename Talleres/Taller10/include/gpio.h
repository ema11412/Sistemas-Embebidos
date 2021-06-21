#ifndef _GPIO_H
#define _GPIO_H




void gpio_init_ptrs(void);
void gpio_set_mode_all(int mode);
void gpio_set_mode(int pin, int mode);
void gpio_write_all(unsigned char bit);
void gpio_write(int pin, unsigned char bit);
void gpio_read_all(void);
void gpio_read(int pin);
void gpio_get_mode_all(void);
void gpio_get_mode(int pin);



#endif