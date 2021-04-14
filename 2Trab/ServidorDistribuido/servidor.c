#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
struct sockaddr_in servidorAddr;
struct sockaddr_in clienteAddr;
unsigned short servidorPorta;
unsigned int clienteLength;

void Servidor()
{
    int servidorSocket;
    int socketCliente;
    char client_message[200] = {0};
    char message[100] = {0};
    const char *pMessage = "hello aticleworld.com";

    // Porta Servidor Distribuido
    servidorPorta = 10124;
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
        }

        // setClientConection(inet_ntoa(clienteAddr.sin_addr));
        close(socketCliente);
    }
    close(servidorSocket);
}

int main()
{
    Servidor();
    return 0;
}