#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
//Create a Socket for server communication

int clienteSocket;
int Cliente(){
    struct sockaddr_in servidorAddr;
    unsigned short servidorPorta;
    char *IP_Servidor;

    // Ip servidor distribuido, porta servidor distribuido
    IP_Servidor = "127.0.0.1";
    servidorPorta = 10024;

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
    else{
        printf("Sucessfully conected with server\n");
    }
    close(clienteSocket);
    
    return 0;
}
// int send_TCP_message(int msgNumber)
// {
//     int t1;
//     if (t1 = send(clienteSocket, msgNumber, sizeof(int), 0), t1 != sizeof(int))
//     {
//         printf("Erro no envio: numero de bytes enviados diferente do esperado\n");
//         return 1;
//     }

//     return 0;
//     //close(clienteSocket);
// }

int main(){
    Cliente();
    // send_TCP_message(999);
    return 0;
}