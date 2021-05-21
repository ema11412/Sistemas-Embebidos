#ifndef INCLUDE_ALARMA_PINES_H_
#define INCLUDE_ALARMA_PINES_H_

#include "system.h"

#include <stdint.h>

volatile uint8_t* push0;
volatile uint8_t* timer;
volatile uint32_t* led0;

volatile uint8_t* secs0_pio;
volatile uint8_t* secs1_pio;

volatile uint8_t* mins0_pio;
volatile uint8_t* mins1_pio;

volatile uint8_t* horas0_pio;
volatile uint8_t* horas1_pio;

volatile uint32_t* switches;

void
separate(uint8_t num, volatile  uint8_t *a, volatile  uint8_t *b);

uint8_t
int2hex(uint8_t in);

volatile uint8_t** hexs[] = { &secs0_pio, &secs1_pio, &mins0_pio, &mins1_pio, &horas0_pio, &horas1_pio };

int mask_secs_sw0 = 0x00000001;
int mask_mins_sw1 = 0x00000002;
int mask_horas_sw2 = 0x00000004;
int mask_setAlarm_sw3 = 0x00000008;
int mask_setTime_sw4 = 0x00000010;
int mask_alarm_on_sw5 = 0x00000020;
int mask_sw6 = 0x00000040;
int mask_sw7 = 0x00000080;
int mask_sw8 = 0x00000100;
int mask_sw9 = 0x00000200;

void
init_pointers( void )
{
  push0 = (uint8_t*)PUSH_0_BASE;
  timer = (uint8_t*)TIMER_0_BASE;
  led0 = (uint32_t *)LED_BASE;
  secs0_pio = (uint8_t*)PIO_SECS0_BASE;
  secs1_pio = (uint8_t*)PIO_SECS_1_BASE;
  mins0_pio = (uint8_t*)PIO_MINS_0_BASE;
  mins1_pio = (uint8_t*)PIO_MINS_1_BASE;
  horas0_pio = (uint8_t*)PIO_HORAS_0_BASE;
  horas1_pio = (uint8_t*)PIO_HORAS_1_BASE;
  switches = (uint32_t*)SWITCHES_BASE;
}

void
draw(uint8_t horas, uint8_t mins, uint8_t secs)
{
  separate(horas, horas1_pio, horas0_pio);
  separate(mins, mins1_pio, mins0_pio);
  separate(secs, secs1_pio, secs0_pio);

  for (uint8_t i = 0; i < 6; ++i)
  {
    **hexs[i] |= (1 << 4); //habilitar todos los 7 segs
    if(i == 2 || i == 4)
    {/* esto es para simular HH:MM:SS */
      **hexs[i] |= (1 << 5);
    }
  }
}

uint8_t
int2hex(uint8_t in)
{
  switch (in)
  {
    case 0:
      return 0x0;
    case 1:
      return 0x1;
    case 2:
      return 0x2;
    case 3:
      return 0x3;
    case 4:
      return 0x4;
    case 5:
      return 0x5;
    case 6:
      return 0x6;
    case 7:
      return 0x7;
    case 8:
      return 0x8;
    case 9:
      return 0x9;
    default:
      return 0xF;
  }
}

void
separate(uint8_t num, volatile uint8_t *a, volatile uint8_t *b)
{
  uint8_t tmp_a = num / 10;
  uint8_t tmp_b = num % 10;
  *a = int2hex(tmp_a);
  *b = int2hex(tmp_b);
}

#endif /* INCLUDE_ALARMA_PINES_H_ */
