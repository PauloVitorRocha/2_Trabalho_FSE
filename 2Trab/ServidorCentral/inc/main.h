#ifndef _MAIN_H_
#define _MAIN_H_

#include <pthread.h>
#include <signal.h>

// #include "cliente.h"
#include "servidor.h"
#include <ncurses.h>

void *ligaServidor();
void chamaMenu();
void loopMenu();
void *pegaInput();
void atualizaValor(struct servidorCentral intermediario);
void trataSinalAlarme();
void abre_inputs();
void trataInterrupcao(int sig);
void trataErroSocket(int signal);

#endif