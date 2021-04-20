#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include "../inc/main.h"
#include "../inc/menu.h"
#include "../inc/servidor.h"
#include "../inc/cliente.h"
// #include "../inc/cliente.h"
// #include "../inc/menu.h"
pthread_t t0, t1;

int keepThreading = 1;
int menuAberto =0;
struct servidorCentral *values;
struct servidorCentral globalValues;
volatile int statusServer = 0;
volatile int restartServer = 1;
pthread_mutex_t lockInput = PTHREAD_MUTEX_INITIALIZER;
void trata_interrupcao(int sinal)
{
    // bcm2835_close();
    // pthread_cl(t0, NULL);
    closeSocket();
    exit(0);
}

int main()
{
    signal(SIGINT, trata_interrupcao);
    signal(SIGTSTP, abre_inputs);
    // Servidor();
    // pthread_create(&t1, NULL, *pegaInput, NULL);
    pthread_create(&t0, NULL, *ligaServidor, NULL);
    pthread_mutex_lock(&lockInput);
    pthread_create(&t1, NULL, *pegaInput, NULL);
    // pthread_join(t0, NULL);
    loopMenu();
    return 0;
}

void loopMenu()
{
    while (1)
    {
        chamaMenu();
        sleep(1);
    }
}
void abre_inputs()
{
    menuAberto=1;
    chamaMenu();
    pthread_mutex_unlock(&lockInput);
}

void *pegaInput()
{
    while (keepThreading)
    {
        pthread_mutex_lock(&lockInput);
        int opcao;
        
        scanf("%d", &opcao);
        if (opcao != 6)
        {
            send_TCP_message(opcao);
        }
        if (opcao == 6)
        {
            menuAberto=0;
            loopMenu();
        }
    }
}

void chamaMenu()
{

    printf("\033[2J\033[H");
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
    if(menuAberto){
        printf("Qual opção deseja mudar?\n");
        printf("0- LAMPADA_01: %d\n", globalValues.machines[0].state);
        printf("1- LAMPADA_02: %d\n", globalValues.machines[1].state);
        printf("2- LAMPADA_03: %d\n", globalValues.machines[2].state);
        printf("3- LAMPADA_04: %d\n", globalValues.machines[3].state);
        printf("4- ARCONDICIONADO_01: %d\n", globalValues.machines[4].state);
        printf("5- ARCONDICIONADO_02: %d\n", globalValues.machines[5].state);
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