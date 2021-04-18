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

int main()
{

    Servidor();

    return 0;
}
