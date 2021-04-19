#include <stdio.h>
#include <unistd.h>
#include "bme280.h"
#include "menu.h"
#include "gpio.h"
#include <bcm2835.h>
#include <signal.h>

struct device
{
    int port;
    int state;
};

#define SENSOR_PRESENCA_SALA RPI_V2_GPIO_P1_22 //GPIO 25

// Define some device parameters
#define I2C_ADDR 0x76 // I2C device address
#define I2C_CH 1 // I2C device channel

    void configura_pinos(){

    // Define botão como entrada
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

        bcm2835_gpio_set_eds(SENSOR_PRESENCA_SALA);
        sleep(10);

        if (bcm2835_gpio_eds(SENSOR_PRESENCA_SALA))
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