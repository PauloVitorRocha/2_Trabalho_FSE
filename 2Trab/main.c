#include <stdio.h>
#include <unistd.h>
#include "bme280.h"
#include "menu.h"
#include "gpio.h"
#include <bcm2835.h>
#include <signal.h>

// Define some device parameters
#define I2C_ADDR 0x76 // I2C device address
#define I2C_CH 1 // I2C device channel
#define LAMPADA01 0  //GPIO 17
#define LAMPADA02 1  //GPIO 18
#define LAMPADA03 2  //GPIO 27
#define LAMPADA04 3  //GPIO 22
#define SENSORPRESENCA01 RPI_V2_GPIO_P1_22 //GPIO 25
#define SENSORPRESENCA02 RPI_V2_GPIO_P1_37 //GPIO 26
#define SENSORABERTURA01 RPI_V2_GPIO_P1_29 //GPIO 05
#define SENSORABERTURA02 RPI_V2_GPIO_P1_31 //GPIO 06
#define SENSORABERTURA03 RPI_V2_GPIO_P1_32 //GPIO 12
#define SENSORABERTURA04 RPI_V2_GPIO_P1_36 //GPIO 16
#define SENSORABERTURA05 RPI_V2_GPIO_P1_38 //GPIO 20
#define SENSORABERTURA06 RPI_V2_GPIO_P1_40 //GPIO 21
// #define AC01 23  //GPIO 13
// #define AC02 24  //GPIO 19
// #define SP01 6   //GPIO 25
// #define SP02 25  //GPIO 26
// #define SA01 21  //GPIO 05
// #define SA02 22  //GPIO 06
// #define SA03 26  //GPIO 12 //WiringPi 26
// #define SA04 27  //GPIO 16
// #define SA05 28  //GPIO 20
// #define SA06 29  //GPIO 21

void configura_pinos()
{

    // Define botão como entrada
    bcm2835_gpio_fsel(SENSOR1, BCM2835_GPIO_FSEL_INPT);
    // Configura entrada do botão como Pull-up
    bcm2835_gpio_set_pud(SENSOR1, BCM2835_GPIO_PUD_UP);

    // bcm2835_gpio_hen(SENSOR1); // Evento HIGH
    //bcm2835_gpio_len(SENSOR1); // Evento LOW
    bcm2835_gpio_ren(SENSOR1); // Evento Rising Edge
    // bcm2835_gpio_fen(SENSOR1); // Evento Falling Edge
}


void trata_interrupcao(int sinal)
{
    bcm2835_close();
    exit(0);
}

int main()
{
    gpio_init();
    int T, P, H; // calibrated values
    bme280Start(I2C_CH, I2C_ADDR, &T, &P, &H);
    menu();
    printf("Temp: %lf\n", T/100.0);
    printf("Umidade: %lf\n", H/1000.0);
    if (!bcm2835_init())
        exit(1);
        
    configura_pinos();

    signal(SIGINT, trata_interrupcao);

    while (1)
    {

        bcm2835_gpio_set_eds(SENSOR1);
        sleep(5);

        if (bcm2835_gpio_eds(SENSOR1))
        {
            printf("Botão apertado!\n");
            fflush(stdout);
        }
        else
        {
            printf("Botão não apertado!\n");
            fflush(stdout);
        }
    }

    // pinMode(SP01, INPUT);
    // readComp(SP01);


}