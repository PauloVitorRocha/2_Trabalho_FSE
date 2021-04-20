
#ifndef GPIO_H_
#define GPIO_H_

#include <wiringPi.h>
#include "cliente.h"
#include "bme280.h"

#define LAMPADA_01 0                    //GPIO 17
#define LAMPADA_02 1                   //GPIO 18
#define LAMPADA_03 2                   //GPIO 27
#define LAMPADA_04 3                   //GPIO 22
#define ARCONDICIONADO_01 23           //GPIO 13
#define ARCONDICIONADO_02 24           //GPIO 19
#define SENSOR_PRESENCA_SALA 6 //RPI_V2_GPIO_P1_22 //GPIO 25
#define SENSOR_PRESENCA_COZINHA 25 //RPI_V2_GPIO_P1_37    //GPIO 26
#define SENSOR_ABERTURA_PORTA_COZINHA 21 //RPI_V2_GPIO_P1_29    //GPIO 05
#define SENSOR_ABERTURA_JANELA_COZINHA 22 //RPI_V2_GPIO_P1_31   //GPIO 06
#define SENSOR_ABERTURA_PORTA_SALA 26 //RPI_V2_GPIO_P1_32       //GPIO 12
#define SENSOR_ABERTURA_JANELA_SALA 27 //RPI_V2_GPIO_P1_36      //GPIO 16
#define SENSOR_ABERTURA_JANELA_QUARTO_01 28//RPI_V2_GPIO_P1_38 //GPIO 20
#define SENSOR_ABERTURA_JANELA_QUARTO_02 29//RPI_V2_GPIO_P1_40 //GPIO 21
#define HIGH 1
#define OUTPUT 1
#define INPUT 0
#define LOW 0
#define IGNORE_CHANGE_BELOW_USEC 10000

void gpio_init();
// int init_bcm();
void toggle();
int gpioLigaEquipamentos(int option);
int init_bcm();
void checaSensoresGPIO();
void trata_interrupcao_gpio(void);

struct servidorDistribuido *setInitialValues();

#endif /* GPIO_H_ */
