#ifndef _MAIN_H_
#define _MAIN_H_

#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "gpio.h"
#include "bme280.h"
// #include "servidor.h"
#include "cliente.h"

void trata_interrupcao(int sinal);
void *sendUpdate();
void trataErroSocket(int signal);
void *connectClient();
void *connectServer();

#endif