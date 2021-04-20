#ifndef _SERVIDOR_H_
#define _SERVIDOR_H_

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include "gpio.h"

struct device
{
    int port;
    int state;
};

struct servidorDistribuido
{
    float temperatura, umidade;
    struct device machines[10];
    struct device sensors[10];
};

extern volatile int restartServer;
extern volatile int restartClient;

void trata_interrupcao_Servidor();
void TrataClienteTCP();
void Servidor();

#endif