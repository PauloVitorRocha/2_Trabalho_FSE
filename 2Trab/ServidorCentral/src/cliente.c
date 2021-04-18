// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include <unistd.h>
// #define SENSOR_PRESENCA_SALA 1             //GPIO 25
// #define SENSOR_PRESENCA_COZINHA 2          //GPIO 26
// #define SENSOR_ABERTURA_PORTA_COZINHA 3    //GPIO 05
// #define SENSOR_ABERTURA_JANELA_COZINHA 4   //GPIO 06
// #define SENSOR_ABERTURA_PORTA_SALA 5       //GPIO 12
// #define SENSOR_ABERTURA_JANELA_SALA 6      //GPIO 16
// #define SENSOR_ABERTURA_JANELA_QUARTO_01 7 //GPIO 20
// #define SENSOR_ABERTURA_JANELA_QUARTO_02 8 //GPIO 21
// #define LOW 0
// #define HIGH 1

// struct device
// {
//     int port;
//     int state;
// };

// struct device sensors[] = {
//     {SENSOR_PRESENCA_COZINHA, LOW},
//     {SENSOR_PRESENCA_SALA, LOW},
//     {SENSOR_ABERTURA_PORTA_COZINHA, LOW},
//     {SENSOR_ABERTURA_JANELA_COZINHA, LOW},
//     {SENSOR_ABERTURA_PORTA_SALA, LOW},
//     {SENSOR_ABERTURA_JANELA_SALA, LOW},
//     {SENSOR_ABERTURA_JANELA_QUARTO_01, LOW},
//     {SENSOR_ABERTURA_JANELA_QUARTO_02, LOW}};

// //Create a Socket for server communication

// // Send the data to the server and set the timeout of 20 seconds
// int SocketSend(int hSocket, struct servidorCentral *Rqst, short lenRqst)
// {
//     int shortRetval = -1;
//     struct timeval tv;
//     tv.tv_sec = 20; /* 20 Secs Timeout */
//     tv.tv_usec = 0;
//     if (setsockopt(hSocket, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(tv)) < 0)
//     {
//         printf("Time Out\n");
//         return -1;
//     }
//     shortRetval = send(hSocket, Rqst, lenRqst, 0);
//     return shortRetval;
// }

// int Cliente(){
//     int clienteSocket;
//     struct sockaddr_in servidorAddr;
//     unsigned short servidorPorta;
//     char *IP_Servidor;

//     // Ip servidor distribuido, porta servidor distribuido
//     IP_Servidor = "192.168.0.4";
//     servidorPorta = 10124;

//     // Criar Socket
//     if ((clienteSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
//     {
//         printf("Erro no socket()");
//         return 1;
//     }

//     // Construir struct sockaddr_in
//     memset(&servidorAddr, 0, sizeof(servidorAddr)); // Zerando a estrutura de dados
//     servidorAddr.sin_family = AF_INET;
//     servidorAddr.sin_addr.s_addr = inet_addr(IP_Servidor);
//     servidorAddr.sin_port = htons(servidorPorta);

//     // Connect
//     if (connect(clienteSocket, (struct sockaddr *)&servidorAddr, sizeof(servidorAddr)) < 0)
//     {
//         printf("Cliente Central não conseguiu conectar com o Servidor Distribuido");
//         //printf("Erro. Cliente Central não conseguiu conectar com o Servidor Distribuido\n");
//         return 1;
//     }
//     SocketSend(clienteSocket, sensors, sizeof(sensors));

//     return 0;
// }