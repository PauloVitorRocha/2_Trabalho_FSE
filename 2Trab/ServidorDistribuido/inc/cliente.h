#ifndef _CLIENTE_H_
#define _CLIENTE_H_

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "servidor.h"


int Cliente();
int send_TCP_message();
void closeSocket();
#endif