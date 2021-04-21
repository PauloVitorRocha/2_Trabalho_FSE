#ifndef _MAIN_H_
#define _MAIN_H_

#include <pthread.h>
#include <signal.h>
#include "servidor.h"

void *ligaServidor();
void *ligaCliente();
void chamaMenu();
void loopMenu();
void *pegaInput();
void *verificaSensores();
void atualizaValor(struct servidorCentral intermediario);
void setAlarme();
void tocaAlarme(int nSensor);
void trata_interrupcao(int sig);
void trataErroSocket(int signal);

#endif