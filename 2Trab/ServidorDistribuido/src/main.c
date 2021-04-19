
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include "../inc/bme280.h"
#include "../inc/main.h"
#include "../inc/gpio.h"
#include "../inc/servidor.h"
#include "../inc/cliente.h"

// Define some device parameters
#define I2C_ADDR 0x76 // I2C device address
#define I2C_CH 1      // I2C device channel

int keepThreading = 1;
float temp;
float humidity;
struct servidorDistribuido *update;
pthread_t t0, t1, t2, t3, t4, t5;

struct servidorDistribuido values;

void trata_interrupcao(int sinal)
{
    // bcm2835_close();
    endI2C();
    printf("\nEncerrando\n");
    exit(0);
}

int main()
{
    // init_bcm();
    // gpio_init();
    signal(SIGINT, trata_interrupcao);
    // Servidor(&values);
    Cliente();
    i2c_TemperaturaUmidade();
    gpioSensores();
    // menu();
    sendUpdate();

    // regulateTemperature();
    // pthread_create(&t1, NULL, gpioSensores, NULL);
    // pthread_join(t1, NULL);
    // pthread_create(&t2, NULL, i2c_TemperaturaUmidade, NULL);
    // pthread_join(t2, NULL);
    // pthread_create(&t3, NULL, sendUpdate, NULL);
    // pthread_join(t3, NULL);

    // pthread_create(&t4, NULL, connectClient, NULL);
    // pthread_create(&t5, NULL, regulateTemperature, NULL);
}

void *gpioSensores()
{
    gpio_init();
}

void *i2c_TemperaturaUmidade()
{
    int i = bme280Init(1, 0x76);
    if (i != 0)
    {
        printf("Error bmeInit\n");
        return 0; // problem - quit
    }
    int T, P, H;
    // bme280Start(I2C_CH, I2C_ADDR, &T, &P, &H);
    bme280ReadValues(&T, &P, &H);
    // printf("Temp: %lf\n", T / 100.0);
    temp = T / 100.0;
    humidity = H / 1000.0;
    // printf("Umidade: %lf\n", H / 1000.0);
}

void *sendUpdate()
{
    struct servidorDistribuido *values = malloc(sizeof(struct servidorDistribuido));
    values = setInitialValues();
    printf("temp = %f\n", values->temperatura);
    values->temperatura = temp;
    values->umidade = humidity;
    // sleep(1);
    send_TCP_message(values);
}