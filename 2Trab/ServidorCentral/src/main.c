#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include "../inc/main.h"
#include "../inc/servidor.h"
// #include "../inc/cliente.h"
// #include "../inc/menu.h"
pthread_t t0, t1;

int contador = 0, keepThreading = 1, restartClient = 0;
struct servidorCentral *values;
void trata_interrupcao(int sinal)
{
    // bcm2835_close();
    closeSocket();
    exit(0);
}
int main()
{
    signal(SIGINT, trata_interrupcao);
    Servidor();

    return 0;
}
