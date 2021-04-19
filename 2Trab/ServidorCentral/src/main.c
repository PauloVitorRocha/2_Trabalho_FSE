#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include "../inc/main.h"
#include "../inc/menu.h"
#include "../inc/servidor.h"
// #include "../inc/cliente.h"
// #include "../inc/menu.h"
pthread_t t0, t1;

int contador = 0, keepThreading = 1;
struct servidorCentral *values;
struct servidorCentral globalValues;
void trata_interrupcao(int sinal)
{
    // bcm2835_close();
    // pthread_cl(t0, NULL);
    closeSocket();
    exit(0);
}

int main()
{
    flag:
    signal(SIGINT, trata_interrupcao);
    signal(SIGTSTP, abre_inputs);
    // Servidor();
    // pthread_create(&t1, NULL, *pegaInput, NULL);
    pthread_create(&t0, NULL, *ligaServidor, NULL);
    // pthread_join(t1, NULL);
    loopMenu();
    return 0;
}

void loopMenu()
{
    while (1)
    {
        chamaMenu();
        sleep(5);
    }
}
void abre_inputs()
{
    int opcao;
    printf("\033[2J\033[H");
    chamaMenu();
    printf("Qual opção deseja mudar?\n");
    printf("0- LAMPADA_01: %d\n", globalValues.machines[0].state);
    printf("1- LAMPADA_02: %d\n", globalValues.machines[1].state);
    printf("2- LAMPADA_03: %d\n", globalValues.machines[2].state);
    printf("3- LAMPADA_04: %d\n", globalValues.machines[3].state);
    printf("4- ARCONDICIONADO_01: %d\n", globalValues.machines[4].state);
    printf("5- ARCONDICIONADO_02: %d\n", globalValues.machines[5].state);
    printf("6- Voltar a info\n");
    scanf("%d", &opcao);
    if (opcao == 6){
        loopMenu();
    }
}

void chamaMenu()
{

    printf("\033[2J\033[H");
    printf("------- Bem vindo ao trabalho 2 -------\n");
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
}

void atualizaValor(struct servidorCentral intermediario)
{
    // struct servidorCentral *values = malloc(sizeof(struct servidorCentral));
    // printf("Atualizando Valores\n");
    globalValues.temperatura = intermediario.temperatura;
    // printf("globalValues temp = %f\n", globalValues.temperatura);
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
    Servidor();
}