/*
 * "Small Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It requires a STDOUT  device in your system's hardware.
 *
 * The purpose of this example is to demonstrate the smallest possible Hello
 * World application, using the Nios II HAL library.  The memory footprint
 * of this hosted application is ~332 bytes by default using the standard
 * reference design.  For a more fully featured Hello World application
 * example, see the example titled "Hello World".
 *
 * The memory footprint of this example has been reduced by making the
 * following changes to the normal "Hello World" example.
 * Check in the Nios II Software Developers Manual for a more complete
 * description.
 *
 * In the SW Application project (small_hello_world):
 *
 *  - In the C/C++ Build page
 *
 *    - Set the Optimization Level to -Os
 *
 * In System Library project (small_hello_world_syslib):
 *  - In the C/C++ Build page
 *
 *    - Set the Optimization Level to -Os
 *
 *    - Define the preprocessor option ALT_NO_INSTRUCTION_EMULATION
 *      This removes software exception handling, which means that you cannot
 *      run code compiled for Nios II cpu with a hardware multiplier on a core
 *      without a the multiply unit. Check the Nios II Software Developers
 *      Manual for more details.
 *
 *  - In the System Library page:
 *    - Set Periodic system timer and Timestamp timer to none
 *      This prevents the automatic inclusion of the timer driver.
 *
 *    - Set Max file descriptors to 4
 *      This reduces the size of the file handle pool.
 *
 *    - Check Main function does not exit
 *    - Uncheck Clean exit (flush buffers)
 *      This removes the unneeded call to exit when main returns, since it
 *      won't.
 *
 *    - Check Don't use C++
 *      This builds without the C++ support code.
 *
 *    - Check Small C library
 *      This uses a reduced functionality C library, which lacks
 *      support for buffering, file IO, floating point and getch(), etc.
 *      Check the Nios II Software Developers Manual for a complete list.
 *
 *    - Check Reduced device drivers
 *      This uses reduced functionality drivers if they're available. For the
 *      standard design this means you get polled UART and JTAG UART drivers,
 *      no support for the LCD driver and you lose the ability to program
 *      CFI compliant flash devices.
 *
 *    - Check Access device drivers directly
 *      This bypasses the device file system to access device drivers directly.
 *      This eliminates the space required for the device file system services.
 *      It also provides a HAL version of libc services that access the drivers
 *      directly, further reducing space. Only a limited number of libc
 *      functions are available in this configuration.
 *
 *    - Use ALT versions of stdio routines:
 *
 *           Function                  Description
 *        ===============  =====================================
 *        alt_printf       Only supports %s, %x, and %c ( < 1 Kbyte)
 *        alt_putstr       Smaller overhead than puts with direct drivers
 *                         Note this function doesn't add a newline.
 *        alt_putchar      Smaller overhead than putchar with direct drivers
 *        alt_getchar      Smaller overhead than getchar with direct drivers
 *
 */

#include <stdbool.h>

#include "system.h"
#include "sys/alt_irq.h"
#include "alarma.h"
#include "alarma_pines.h"

void
io_push_0_isr(void* context);

void
timer_0_isr(void* context);

void
irq_setup(void);

volatile int edge_val;

int counter = 0;
bool sonar_alarma =  false;

int
main( void )
{
  init_pointers();
  *led0 = 0b0;
  irq_setup();
  init_hour_type(&hour);
  init_hour_type(&alarm);

  /* Event loop never exits. */
  while (1)
  {
    if((*switches & mask_setAlarm_sw3) == mask_setAlarm_sw3)
    {
      /* muestra la hora de la alarma */
      draw(alarm.hours, alarm.minutes, alarm.seconds);
    }
    else
    {
      /* muestra la hora normal */
      draw(hour.hours, hour.minutes, hour.seconds);
    }
    if((*switches & mask_alarm_on_sw5) == mask_alarm_on_sw5)
    {
      *led0 |=(1 << 5);
      if(hora_equals(&hour, &alarm))
      {
        sonar_alarma = true;
      }
    }
    else
    {
      *led0 &= ~(1UL << 5);
    }
    if(sonar_alarma)
    {
      *led0 |= 1;
    }
    else
    {
      *led0 &= ~(1UL << 0);
    }
  }
  return 0;
}


void
irq_setup( void )
{
  *(push0 + 0x08) = 0x0F;
  *(push0 + 0x0C) = 0x00;
  /* Register the interrupt */
  alt_ic_isr_register(PUSH_0_IRQ_INTERRUPT_CONTROLLER_ID, PUSH_0_IRQ, io_push_0_isr, NULL, 0x00);

  *(timer + 0x04) = 0x03;
  *(timer) = 0x00; /* clear the interrupt */
  alt_ic_isr_register(TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID, TIMER_0_IRQ, timer_0_isr, NULL, 0x00);
  *(timer + 0x04) = 0x07; /* start */
}

void
io_push_0_isr( void* context )
{
  *(push0 + 0x0C) = 0x00;
  bool time_set = (*switches&mask_setTime_sw4) == mask_setTime_sw4;
  bool alarm_set  = (*switches&mask_setAlarm_sw3) == mask_setAlarm_sw3;

  if ((*switches & mask_secs_sw0) == mask_secs_sw0)
  {
    /* set seconds */
    if(alarm_set)
    {
      tick(&alarm);
    }
    else if (time_set)
    {
      tick(&hour);
    }
  }
  else if((*switches & mask_mins_sw1) == mask_mins_sw1)
  {
    /* set minutes */
    if(alarm_set)
    {
      tick_min(&alarm);
    }
    else if (time_set)
    {
      tick_min(&hour);
    }
  }
  else if((*switches & mask_horas_sw2) == mask_horas_sw2)
  {
    /* set hours */
    if(alarm_set)
    {
      tick_hour(&alarm);
    }
    else if (time_set)
    {
      tick_hour(&hour);
    }
  }
  else
  {
    sonar_alarma = false;
  }
}

void
timer_0_isr( void* context )
{
  *(timer) = 0x00;
  tick(&hour);
}
