#ifndef _TIMER_H
#define _TIMER_H

int startTimer(void);
int stopTimer(void);
unsigned int getTimerValue(void);
unsigned int hex2dec(char *hex);
unsigned int getRandomNumber(unsigned int upper, unsigned int lower);
double getExecutionTime(unsigned int upperTime, unsigned int lowerTime);

#endif