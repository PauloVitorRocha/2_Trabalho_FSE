#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include "../inc/main.h"
#include "../inc/servidor.h"
#include "../inc/cliente.h"
// #include "../inc/cliente.h"
// #include "../inc/menu.h"
pthread_t t0, t1, t2;

int keepThreading = 1;
struct servidorCentral *values;
struct servidorCentral globalValues;
volatile int statusServer = 0;
volatile int restartServer = 1;
volatile int restartClient = 1;
volatile int menuAberto = 0;
pthread_mutex_t lockInput = PTHREAD_MUTEX_INITIALIZER;

int main()
{
    signal(SIGINT, trata_interrupcao);
    signal(SIGTSTP, abre_inputs);
    pthread_create(&t0, NULL, *ligaServidor, NULL);
    pthread_create(&t2, NULL, *ligaCliente, NULL);
    pthread_create(&t1, NULL, *pegaInput, NULL);
    loopMenu();
    return 0;
}

void trata_interrupcao(int sinal)
{

    closeSocket();
    exit(0);
}

void abre_inputs()
{
    menuAberto = 1;
    chamaMenu();
}

void loopMenu()
{
    while (1)
    {
        chamaMenu();
        usleep(1000000);
    }
}

void *pegaInput()
{
    int opcao;
    do
    {
        scanf("%d", &opcao);
        if (opcao != 6)
        {
            send_TCP_message(opcao);
            menuAberto = 0;
        }
        if (opcao == 6)
        {
            menuAberto = 0;
            loopMenu();
        }
    } while (keepThreading);
}

void chamaMenu()
{

    system("clear");
    printf("------- Bem vindo ao trabalho 2 -------\n");

    printf("Status do Distribuido: %d\n", statusServer);
    printf("Temperatura: %f\n", globalValues.temperatura);
    printf("Umidade: %f\n", globalValues.umidade);
    printf("LAMPADA_01: %d\n", globalValues.machines[0].state);
    printf("LAMPADA_02: %d\n", globalValues.machines[1].state);
    printf("LAMPADA_03: %d\n", globalValues.machines[2].state);
    printf("LAMPADA_04: %d\n", globalValues.machines[3].state);
    printf("ARCONDICIONADO_01: %d\n", globalValues.machines[4].state);
    printf("ARCONDICIONADO_02: %d\n", globalValues.machines[5].state);
    printf("SENSOR_PRESENCA_SALA: %d\n", globalValues.sensors[0].state);
    printf("SENSOR_PRESENCA_COZINHA: %d\n", globalValues.sensors[1].state);
    printf("SENSOR_ABERTURA_PORTA_COZINHA: %d\n", globalValues.sensors[2].state);
    printf("SENSOR_ABERTURA_JANELA_COZINHA: %d\n", globalValues.sensors[3].state);
    printf("SENSOR_ABERTURA_PORTA_SALA: %d\n", globalValues.sensors[4].state);
    printf("SENSOR_ABERTURA_JANELA_SALA: %d\n", globalValues.sensors[5].state);
    printf("SENSOR_ABERTURA_JANELA_QUARTO_01: %d\n", globalValues.sensors[6].state);
    printf("SENSOR_ABERTURA_JANELA_QUARTO_02: %d\n", globalValues.sensors[7].state);
    printf("\nPressione CTRL+Z para menu \n");
    if (menuAberto)
    {
        printf("Qual opção deseja mudar?\n");
        printf("0- LAMPADA_01\n");
        printf("1- LAMPADA_02\n");
        printf("2- LAMPADA_03\n");
        printf("3- LAMPADA_04\n");
        printf("4- ARCONDICIONADO_01\n");
        printf("5- ARCONDICIONADO_02\n");
        printf("6- Voltar a info\n");
    }
}

void atualizaValor(struct servidorCentral intermediario)
{
    globalValues.temperatura = intermediario.temperatura;
    globalValues.umidade = intermediario.umidade;
    for (int i = 0; i < 6; i++)
    {
        globalValues.machines[i].state = intermediario.machines[i].state;
        globalValues.machines[i].port = intermediario.machines[i].port;
    }

    for (int i = 0; i < 8; i++)
    {
        globalValues.sensors[i].state = intermediario.sensors[i].state;
        globalValues.sensors[i].port = intermediario.sensors[i].port;
    }
}

void *ligaServidor()
{
    while (keepThreading)
    {
        Servidor();
        usleep(2000000);
    }
}

void *ligaCliente()
{
    while (keepThreading)
    {
        if (restartClient)
        {
            restartClient = Cliente();
        }
        usleep(1000000);
    }
    return NULL;
}