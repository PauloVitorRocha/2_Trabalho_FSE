#include "../inc/gpio.h"
#include <bcm2835.h>

struct device sensors[] = {
    {SENSOR_PRESENCA_SALA, LOW},
    {SENSOR_PRESENCA_COZINHA, LOW},
    {SENSOR_ABERTURA_PORTA_COZINHA, LOW},
    {SENSOR_ABERTURA_JANELA_COZINHA, LOW},
    {SENSOR_ABERTURA_PORTA_SALA, LOW},
    {SENSOR_ABERTURA_JANELA_SALA, LOW},
    {SENSOR_ABERTURA_JANELA_QUARTO_01, LOW},
    {SENSOR_ABERTURA_JANELA_QUARTO_02, LOW}};

struct device machines[] = {
    {LAMPADA_01, LOW},
    {LAMPADA_02, LOW},
    {LAMPADA_03, LOW},
    {LAMPADA_04, LOW},
    {ARCONDICIONADO_01, LOW},
    {ARCONDICIONADO_02, LOW}};

struct timeval last_change;

int sensorsSize = 8, machinesSize = 6;

void gpio_init()
{
    wiringPiSetup();
    toggle();
}

void handleSALA(void)
{
    struct timeval now;
    unsigned long diff;

    gettimeofday(&now, NULL);

    // Time difference in usec
    diff = (now.tv_sec * 1000000 + now.tv_usec) - (last_change.tv_sec * 1000000 + last_change.tv_usec);

    // Filter jitter
    if (diff > IGNORE_CHANGE_BELOW_USEC)
    {
        if (sensors[0].state)
        {
            printf("Falling\n");
        }
        else
        {
            printf("Rising\n");
        }

        sensors[0].state = !sensors[0].state;
    }

    last_change = now;
}
void handleCOZINHA(void)
{
    struct timeval now;
    unsigned long diff;

    gettimeofday(&now, NULL);

    // Time difference in usec
    diff = (now.tv_sec * 1000000 + now.tv_usec) - (last_change.tv_sec * 1000000 + last_change.tv_usec);

    // Filter jitter
    if (diff > IGNORE_CHANGE_BELOW_USEC)
    {
        if (sensors[1].state)
        {
            printf("Falling\n");
        }
        else
        {
            printf("Rising\n");
        }

        sensors[1].state = !sensors[1].state;
    }

    last_change = now;
}
void handlePORTA_COZINHA(void)
{
    struct timeval now;
    unsigned long diff;

    gettimeofday(&now, NULL);

    // Time difference in usec
    diff = (now.tv_sec * 1000000 + now.tv_usec) - (last_change.tv_sec * 1000000 + last_change.tv_usec);

    // Filter jitter
    if (diff > IGNORE_CHANGE_BELOW_USEC)
    {
        if (sensors[2].state)
        {
            printf("Falling\n");
        }
        else
        {
            printf("Rising\n");
        }

        sensors[2].state = !sensors[2].state;
    }

    last_change = now;
}
void handleJANELA_COZINHA(void)
{
    struct timeval now;
    unsigned long diff;

    gettimeofday(&now, NULL);

    // Time difference in usec
    diff = (now.tv_sec * 1000000 + now.tv_usec) - (last_change.tv_sec * 1000000 + last_change.tv_usec);

    // Filter jitter
    if (diff > IGNORE_CHANGE_BELOW_USEC)
    {
        if (sensors[3].state)
        {
            printf("Falling\n");
        }
        else
        {
            printf("Rising\n");
        }

        sensors[3].state = !sensors[3].state;
    }

    last_change = now;
}
void handlePORTA_SALA(void)
{
    struct timeval now;
    unsigned long diff;

    gettimeofday(&now, NULL);

    // Time difference in usec
    diff = (now.tv_sec * 1000000 + now.tv_usec) - (last_change.tv_sec * 1000000 + last_change.tv_usec);

    // Filter jitter
    if (diff > IGNORE_CHANGE_BELOW_USEC)
    {
        if (sensors[4].state)
        {
            printf("Falling\n");
        }
        else
        {
            printf("Rising\n");
        }

        sensors[4].state = !sensors[4].state;
    }

    last_change = now;
}
void handleJANELA_SALA(void)
{
    struct timeval now;
    unsigned long diff;

    gettimeofday(&now, NULL);

    // Time difference in usec
    diff = (now.tv_sec * 1000000 + now.tv_usec) - (last_change.tv_sec * 1000000 + last_change.tv_usec);

    // Filter jitter
    if (diff > IGNORE_CHANGE_BELOW_USEC)
    {
        if (sensors[5].state)
        {
            printf("Falling\n");
        }
        else
        {
            printf("Rising\n");
        }

        sensors[5].state = !sensors[5].state;
    }

    last_change = now;
}
void handleJANELA_QUARTO_01(void)
{
    struct timeval now;
    unsigned long diff;

    gettimeofday(&now, NULL);

    // Time difference in usec
    diff = (now.tv_sec * 1000000 + now.tv_usec) - (last_change.tv_sec * 1000000 + last_change.tv_usec);

    // Filter jitter
    if (diff > IGNORE_CHANGE_BELOW_USEC)
    {
        if (sensors[6].state)
        {
            printf("Falling\n");
        }
        else
        {
            printf("Rising\n");
        }

        sensors[6].state = !sensors[6].state;
    }

    last_change = now;
}
void handleJANELA_QUARTO_02(void)
{
    struct timeval now;
    unsigned long diff;

    gettimeofday(&now, NULL);

    // Time difference in usec
    diff = (now.tv_sec * 1000000 + now.tv_usec) - (last_change.tv_sec * 1000000 + last_change.tv_usec);

    // Filter jitter
    if (diff > IGNORE_CHANGE_BELOW_USEC)
    {
        if (sensors[7].state)
        {
            printf("Falling\n");
        }
        else
        {
            printf("Rising\n");
        }

        sensors[7].state = !sensors[7].state;
    }

    last_change = now;
}

void toggle()
{
    for (int i = 0; i < machinesSize; i++)
    {
        pinMode(machines[i].port, OUTPUT);
        machines[i].state = digitalRead(machines[i].port);
    }
    for (int i = 0; i < sensorsSize; i++)
    {
        pinMode(sensors[i].port, OUTPUT);
        sensors[i].state = digitalRead(sensors[i].port);
    }
    
    gettimeofday(&last_change, NULL);
    wiringPiISR(sensors[0].port, INT_EDGE_BOTH, &handleSALA);
    wiringPiISR(sensors[1].port, INT_EDGE_BOTH, &handleCOZINHA);
    wiringPiISR(sensors[2].port, INT_EDGE_BOTH, &handlePORTA_COZINHA);
    wiringPiISR(sensors[3].port, INT_EDGE_BOTH, &handleJANELA_COZINHA);
    wiringPiISR(sensors[4].port, INT_EDGE_BOTH, &handlePORTA_SALA);
    wiringPiISR(sensors[5].port, INT_EDGE_BOTH, &handleJANELA_SALA);
    wiringPiISR(sensors[6].port, INT_EDGE_BOTH, &handleJANELA_QUARTO_01);
    wiringPiISR(sensors[7].port, INT_EDGE_BOTH, &handleJANELA_QUARTO_02);

int gpioLigaEquipamentos(int option)
{
    digitalWrite(machines[option].port, !machines[option].state);
    machines[option].state = !machines[option].state;
}

struct servidorDistribuido *setInitialValues()
{
    struct servidorDistribuido *newValues = malloc(sizeof(struct servidorDistribuido));

    int T=0, P, H=0;
    // bme280Start(I2C_CH, I2C_ADDR, &T, &P, &H);
    bme280ReadValues(&T, &P, &H);
    newValues->temperatura = T/100.0;
    newValues->umidade = H/1000.0;

    for (int i = 0; i < machinesSize; i++)
    {
        machines[i].state = digitalRead(machines[i].port);
    }

    for (int i = 0; i < machinesSize; i++)
    {
        newValues->machines[i].state = machines[i].state;
        newValues->machines[i].port = machines[i].port;
    }

    for (int i = 0; i < sensorsSize; i++)
    {
        newValues->sensors[i].state = sensors[i].state;
        newValues->sensors[i].port = sensors[i].port;
    }

    return newValues;
}