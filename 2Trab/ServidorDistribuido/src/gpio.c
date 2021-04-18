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

struct servidorDistribuido *update;

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
        if (update->sensors[0].state)
        {
            printf("Falling\n");
        }
        else
        {
            printf("Rising\n");
        }

        update->sensors[0].state = !update->sensors[0].state;
    }
    last_change = now;
    send_TCP_message(update);
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
        if (update->sensors[1].state)
        {
            printf("Falling\n");
        }
        else
        {
            printf("Rising\n");
        }

        update->sensors[1].state = !update->sensors[1].state;
    }
    last_change = now;
    send_TCP_message(update);
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
        if (update->sensors[2].state)
        {
            printf("Falling\n");
        }
        else
        {
            printf("Rising\n");
        }

        update->sensors[2].state = !update->sensors[2].state;
    }
    last_change = now;
    send_TCP_message(update);
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
        if (update->sensors[3].state)
        {
            printf("Falling\n");
        }
        else
        {
            printf("Rising\n");
        }

        update->sensors[3].state = !update->sensors[3].state;
    }
    last_change = now;
    send_TCP_message(update);
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
        if (update->sensors[4].state)
        {
            printf("Falling\n");
        }
        else
        {
            printf("Rising\n");
        }

        update->sensors[4].state = !update->sensors[4].state;
    }
    last_change = now;
    send_TCP_message(update);
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
        if (update->sensors[5].state)
        {
            printf("Falling\n");
        }
        else
        {
            printf("Rising\n");
        }

        update->sensors[5].state = !update->sensors[5].state;
    }
    last_change = now;
    send_TCP_message(update);
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
        if (update->sensors[6].state)
        {
            printf("Falling\n");
        }
        else
        {
            printf("Rising\n");
        }

        update->sensors[6].state = !update->sensors[6].state;
    }
    last_change = now;
    send_TCP_message(update);
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
        if (update->sensors[7].state)
        {
            printf("Falling\n");
        }
        else
        {
            printf("Rising\n");
        }

        update->sensors[7].state = !update->sensors[7].state;
    }
    last_change = now;
    send_TCP_message(update);
}

void toggle()
{
    *update = *updateValues();
    for (int i = 0; i < sensorsSize; i++)
    {
        pinMode(update->sensors[i].port, OUTPUT);
        update->sensors[i].state = digitalRead(sensors[i].port);
    }
    for (int i = 0; i < machinesSize; i++)
    {
        pinMode(update->machines[i].port, OUTPUT);
        update->machines[i].state = digitalRead(machines[i].port);
    }
    send_TCP_message(update);
    gettimeofday(&last_change, NULL);
    wiringPiISR(update->sensors[0].port, INT_EDGE_BOTH, &handleSALA);
    wiringPiISR(update->sensors[1].port, INT_EDGE_BOTH, &handleCOZINHA);
    wiringPiISR(update->sensors[2].port, INT_EDGE_BOTH, &handlePORTA_COZINHA);
    wiringPiISR(update->sensors[3].port, INT_EDGE_BOTH, &handleJANELA_COZINHA);
    wiringPiISR(update->sensors[4].port, INT_EDGE_BOTH, &handlePORTA_SALA);
    wiringPiISR(update->sensors[5].port, INT_EDGE_BOTH, &handleJANELA_SALA);
    wiringPiISR(update->sensors[6].port, INT_EDGE_BOTH, &handleJANELA_QUARTO_01);
    wiringPiISR(update->sensors[7].port, INT_EDGE_BOTH, &handleJANELA_QUARTO_02);

    // while (1)
    // {
    //     sleep(1);
    // }
}

int gpioLigaEquipamentos(int option)
{
    digitalWrite(update->machines[option].port, !update->machines[option].state);
    update->machines[option].state = !update->machines[option].state;
    // updateValues
}

// int init_bcm()
// {
//     if (!bcm2835_init())
//     {
//         return 1;
//     }
//     return 0;
// }

void checaSensoresGPIO()
{
    printf("Here\n");
    // struct servidorDistribuido *newValues = malloc(sizeof(struct servidorDistribuido));
    // newValues->temperatura = 1000.0;
    // newValues->umidade = 50.0;
    // printf("%f\n", newValues->temperatura);
    // printf("%f\n", newValues->umidade);

    // send_TCP_message(newValues);
}

struct servidorDistribuido *updateValues()
{
    struct servidorDistribuido *newValues = malloc(sizeof(struct servidorDistribuido));

    int T, P, H;
    // bme280Start(I2C_CH, I2C_ADDR, &T, &P, &H);
    bme280ReadValues(&T, &P, &H);
    newValues->temperatura = T/100.0;
    newValues->umidade = H/1000.0;

    for (int i = 0; i < 6; i++)
    {
        newValues->machines[i].state = machines[i].state;
        newValues->machines[i].port = machines[i].port;
    }

    for (int i = 0; i < 8; i++)
    {
        newValues->sensors[i].state = sensors[i].state;
        newValues->sensors[i].port = sensors[i].port;
    }

    return newValues;
}