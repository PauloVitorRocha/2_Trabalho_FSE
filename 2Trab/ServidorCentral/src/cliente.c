#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include "../inc/cliente.h"

//Create a Socket for server communication
FILE *ptr1;
char x[64];
void time_gen()
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(x, sizeof(x), "%c", tm);
}

int clienteSocket;

int send_TCP_message(int nLampada)
{
    int tamanhoMensagem = 1;
    if(nLampada>7 || nLampada<0){
        return 1;
    }
    char comando[2];
    comando[0] = nLampada + 48;

    if (send(clienteSocket, comando, 1, 0) != tamanhoMensagem)
    {
        // printf("Erro no envio: numero de bytes enviados diferente do esperado\n");
        return 1;
    }
    else{
        ptr1 = fopen("../csv/comandosUsuario.csv", "a");
        if (ptr1 == NULL)
        {
            printf("Error ao abrir arquivo!");
            exit(1);
        }
        time_gen();
        if (nLampada <= 3 && nLampada>=0)
            fprintf(ptr1, "%s, Enviado comando para trocar o estado da lampada %d\n", x, nLampada + 1);
        else
            fprintf(ptr1, "%s, Enviado comando para trocar o estado do ar-condicionado %d\n", x, nLampada-3);
        fclose(ptr1);
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
        // printf("Erro no socket()\n");
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
        // printf("Cliente Central não conseguiu conectar com o Servidor Distribuido\n");
        return 1;
    }
    else
    {
        // printf("Sucessfully conected with server\n");
    }

    return 0;
}

void trata_interrupcao_Cliente()
{
    close(clienteSocket);
}