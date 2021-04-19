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
    int tamanhoRecebido;
    char buffer[16];
        if ((tamanhoRecebido = recv(socketCliente, buffer, 16, 0)) < 0)
        {
            printf("Erro no recv()\n");
        }
        else{
            printf("Comando= %c\n", buffer[0]);
        }

		// for(int i=0;i<6;i++){
		// 	printf("machines %d %d\n",intermediario->machines[i].port,intermediario->machines[i].state);
		// }
}

void Servidor()
{


    // Porta Servidor Distribuido
    servidorPorta = 10024;
    // Abrir Socket
    if ((servidorSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("falha no socket do Servidor\n");
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
        printf("Falha no Bind do Servidor Distribuido");
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
        printf("Waiting for incoming connections...\n");
        clienteLength = sizeof(clienteAddr);
        if ((socketCliente = accept(servidorSocket, (struct sockaddr *)&clienteAddr, &clienteLength)) < 0)
        {

            printf("Falha no Accept\n");
            continue;
        }
        else
        {
            printf("Connection accepted\n");
            TrataClienteTCP();
        }
        // setClientConection(inet_ntoa(clienteAddr.sin_addr));
        close(socketCliente);
    }
    close(servidorSocket);
}