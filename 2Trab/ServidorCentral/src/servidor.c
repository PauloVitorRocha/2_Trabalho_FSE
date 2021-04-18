#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../inc/servidor.h"
struct sockaddr_in servidorAddr;
struct sockaddr_in clienteAddr;
unsigned short servidorPorta;
unsigned int clienteLength;

int servidorSocket;
int socketCliente;

void TrataClienteTCP()
{
    printf("Tratando Cliente TCP\n");
    int tamanhoRecebido;
    int alarmPlaying = 0;
    int cont = 0;
    struct servidorCentral *intermediario = malloc(sizeof(struct servidorCentral));

    do
    {
        if ((tamanhoRecebido = recv(socketCliente, (void *)intermediario, sizeof(struct servidorCentral), 0)) < 0)
        {
            printf("Erro no recv()");
        }

        printf("%f %f\n", intermediario->temperatura, intermediario->umidade);
        for(int i=0;i<6;i++){
        	printf("machines %d %d\n",intermediario->machines[i].port,intermediario->machines[i].state);
        }
        for(int i=0;i<8;i++){
        	printf("sensors %d %d\n",intermediario->sensors[i].port,intermediario->sensors[i].state);
        }

    } while (tamanhoRecebido > 0);
    close(socketCliente);
}

void Servidor()
{
    struct sockaddr_in servidorAddr;
    struct sockaddr_in clienteAddr;
    unsigned short servidorPorta;
    unsigned int clienteLength;

    // Porta Servidor Distribuido
    servidorPorta = 10024;
    // Abrir Socket
    if ((servidorSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("falha no socket do Servidor");
        close(servidorSocket);
        return;
    }

    // Montar a estrutura sockaddr_in
    memset(&servidorAddr, 0, sizeof(servidorAddr)); // Zerando a estrutura de dados
    servidorAddr.sin_family = AF_INET;
    servidorAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servidorAddr.sin_port = htons(servidorPorta);

    // Bind
    if (bind(servidorSocket, (struct sockaddr *)&servidorAddr, sizeof(servidorAddr)) < 0)
    {
        printf("Falha no Bind do Servidor Central");
        close(servidorSocket);
        return;
    }

    // Listen
    if (listen(servidorSocket, 10) < 0)
    {
        printf("Falha no Listen\n");
        close(servidorSocket);
        return;
    }

    while (1)
    {
        clienteLength = sizeof(clienteAddr);
        printf("Aguardando conexão\n");
        if ((socketCliente = accept(servidorSocket, (struct sockaddr *)&clienteAddr, &clienteLength)) < 0)
        {
            printf("Falha no Accept\n");
            continue;
        }
        else{
            printf("aqui estou\n");
            TrataClienteTCP();
        }
        close(socketCliente);
    }
    close(servidorSocket);
}