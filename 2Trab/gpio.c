#include "gpio.h"

void gpio_init()
{
    wiringPiSetup();
}

void toggle(int componente, int status)
{
    digitalWrite(componente, status);
}
void readComponent(int componente)
{
    while(1){
        if (digitalRead(componente) == LOW){
            printf("TA NO LOW\n");
        }
        else{
            printf("TA NO HIGH\n");
        }
        delay(500);
    }
}
