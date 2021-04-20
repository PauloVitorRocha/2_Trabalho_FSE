
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

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock4 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock5 = PTHREAD_MUTEX_INITIALIZER;

int keepThreading = 1;
volatile int restartClient = 1;
volatile int statusServer = 1;
volatile int restartServer = 1;
float temp;
float humidity;
struct servidorDistribuido *update;
pthread_t t0, t1, t2, t3, t4, t5;

struct servidorDistribuido values;

void trata_interrupcao(int sinal)
{
    // bcm2835_close();
    keepThreading = 0;
    endI2C();
    closeSocket();
    printf("\nEncerrando\n");
    exit(0);
}

int main()
{
    // init_bcm();
    // gpio_init();
    signal(SIGINT, trata_interrupcao);
    signal(SIGPIPE, trataErroSocket);

    // Servidor(&values);
    // Cliente();
    int i = bme280Init(1, 0x76);
    if (i != 0)
    {
        printf("Error bmeInit\n");
        // return 0; // problem - quit
    }
    gpioSensores();
    // Cliente();

    // menu();

    // regulateTemperature();
    // pthread_create(&t1, NULL, gpioSensores, NULL);
    // pthread_join(t1, NULL);
    // pthread_create(&t2, NULL, i2c_TemperaturaUmidade, NULL);
    pthread_create(&t3, NULL, connectClient, NULL);
    pthread_create(&t2, NULL, connectServer, NULL);
    // pthread_join(t2, NULL);
    // pthread_join(t3, NULL);
    // pthread_create(&t4, NULL, sendUpdate, NULL);
    // pthread_join(t4, NULL);

    // pthread_create(&t5, NULL, regulateTemperature, NULL);

    while (1)
    {
        if(!restartClient){
            sendUpdate();
        }
        usleep(1000000);
    }
}

void trataErroSocket(int signal)
{
    printf("Sigpipe error\n");
    restartClient = 1;
}

void *connectClient()
{

    while (keepThreading)
    {
        if (restartClient)
        {
            restartClient = Cliente();
        }
        usleep(1000000);
    }
    return NULL;
}
void *connectServer()
{

    while (keepThreading)
    {
        Servidor();
        usleep(2000000);
    }
}

void *gpioSensores()
{
    gpio_init();
}

void *sendUpdate()
{
    struct servidorDistribuido *values = malloc(sizeof(struct servidorDistribuido));
    values = setInitialValues();
    send_TCP_message(values);
}