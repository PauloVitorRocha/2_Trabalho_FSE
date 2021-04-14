
#include <wiringPi.h>
#include <stdio.h>
#ifndef GPIO_H_
#define GPIO_H_

void gpio_init();
void toggle(int componente, int status);
void readComponent(int componente);

#endif /* GPIO_H_ */