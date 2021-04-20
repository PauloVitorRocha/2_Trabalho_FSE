#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../inc/cliente.h"

//Create a Socket for server communication

int clienteSocket;

int send_TCP_message(int nLampada)
{
    // printf("IN TCP MSG: %f %f\n", updates->temperatura, updates->umidade);

    int tamanhoMensagem = 1;
    char comando[2];
    comando[0] = nLampada + 48;

    if (send(clienteSocket, comando, 1, 0) != tamanhoMensagem)
    {
        printf("Erro no envio: numero de bytes enviados diferente do esperado\n");
        return 1;
    }
    else
    {
        printf("Mensagem enviada com sucesso\n");
        // close(clienteSocket);
    }
    return 0;
}

int Cliente()
{
    struct sockaddr_in servidorAddr;
    unsigned short servidorPorta;
    char *IP_Servidor;

    // Ip servidor distribuido, porta servidor distribuido
    IP_Servidor = "192.168.0.52";
    servidorPorta = 10124;

    // Criar Socket
    if ((clienteSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("Erro no socket()");
        return 1;
    }

    // Construir struct sockaddr_in
    memset(&servidorAddr, 0, sizeof(servidorAddr)); // Zerando a estrutura de dados
    servidorAddr.sin_family = AF_INET;
    servidorAddr.sin_addr.s_addr = inet_addr(IP_Servidor);
    servidorAddr.sin_port = htons(servidorPorta);

    // Connect
    if (connect(clienteSocket, (struct sockaddr *)&servidorAddr, sizeof(servidorAddr)) < 0)
    {
        printf("Cliente Central não conseguiu conectar com o Servidor Distribuido");
        return 1;
    }
    else
    {
        printf("Sucessfully conected with server\n");
    }
    // close(clienteSocket);

    return 0;
}

void closeClienteSocket()
{
    close(clienteSocket);
}