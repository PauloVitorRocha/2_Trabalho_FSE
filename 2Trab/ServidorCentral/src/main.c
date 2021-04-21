#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include "../inc/main.h"
#include "../inc/servidor.h"
#include "../inc/cliente.h"

pthread_t t0, t1, t2, t3;

volatile int keepThreading = 1;
struct servidorCentral *values;
struct servidorCentral globalValues;
volatile int statusServer = 0;
volatile int restartServer = 1;
volatile int restartClient = 1;
volatile int menuAberto = 0;
int alarmeTocando = 0, alarmeLigado = 0, showMsg = 0;

FILE *ptr, *ptr1;
char s[64];
void time_generate()
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(s, sizeof(s), "%c", tm);
}

int main()
{
    ptr = fopen("../csv/logAlarme.csv", "w");
    if (ptr == NULL)
    {
        printf("Error ao abrir arquivo log!");
        exit(1);
    }
    fprintf(ptr, "Data, Acontecimento\n");
    fclose(ptr);
    ptr1 = fopen("../csv/comandosUsuario.csv", "w");
    if (ptr1 == NULL)
    {
        printf("Error ao abrir arquivo comandos!");
        exit(1);
    }
    fprintf(ptr1, "Data, Acontecimento\n");
    fclose(ptr1);
    signal(SIGINT, trata_interrupcao);
    pthread_create(&t0, NULL, *ligaServidor, NULL);
    pthread_create(&t2, NULL, *ligaCliente, NULL);
    pthread_create(&t1, NULL, *pegaInput, NULL);
    pthread_create(&t3, NULL, *verificaSensores, NULL);
    loopMenu();
    return 0;
}

void trata_interrupcao(int sinal)
{
    if (statusServer == 0)
    {
        keepThreading = 0;
        trata_interrupcao_Cliente();
        trata_interrupcao_Servidor();
        printf("\nEncerrando\n");
        exit(0);
    }
    else
    {
        showMsg = 1;
    }
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
        sleep(1);
        if (opcao >= 0 && opcao <= 5)
        {
            send_TCP_message(opcao);
            menuAberto = 0;
        }
        else if (opcao == 7)
        {
            menuAberto = 0;
            loopMenu();
        }
        else if (opcao == 6)
        {
            setAlarme();
        }
    } while (keepThreading);
}

void chamaMenu()
{

    system("clear");
    if (showMsg)
        printf("Feche primeiro o servidor distribuido\n");
    
    printf("\n------- Bem vindo ao trabalho 2 -------\n");

    printf("Status do Distribuido: %d\n", statusServer);
    printf("Status do Alarme: %d\n\n", alarmeLigado);
    if (alarmeTocando)
    {
        printf("######### ALARME TOCANDO #########\n\n");
    }
    printf("Temperatura: %.02f\n", globalValues.temperatura);
    printf("Umidade: %.02f\n", globalValues.umidade);
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
    printf("\nSelecione uma opção para ativar ou desativar os aparelhos\n");
    printf("0- LAMPADA_01\n");
    printf("1- LAMPADA_02\n");
    printf("2- LAMPADA_03\n");
    printf("3- LAMPADA_04\n");
    printf("4- ARCONDICIONADO_01\n");
    printf("5- ARCONDICIONADO_02\n");
    printf("6- Ativar o Alarme: %d\n", alarmeLigado);
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
    return NULL;
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

void *verificaSensores()
{
    while (keepThreading)
    {
        int alarmeTocou = 0;
        for (int i = 0; i < 8; i++)
        {
            if (globalValues.sensors[i].state && alarmeLigado)
            {
                tocaAlarme(i);
                alarmeTocou = 1;
            }
        }
        if (!alarmeTocou)
            alarmeTocando = 0;
        usleep(1000000);
    }
    return NULL;
}

void setAlarme()
{
    alarmeLigado = !alarmeLigado;
}

void tocaAlarme(int nSensor)
{
    alarmeTocando = 1;
    ptr = fopen("../csv/logAlarme.csv", "a");
    if (ptr == NULL)
    {
        printf("Error ao abrir arquivo!");
        exit(1);
    }
    time_generate();
    if (nSensor == 0)
        fprintf(ptr, "%s, Alarme tocou pois presença foi detectada pelo SENSOR_PRESENCA_SALA\n", s);
    if (nSensor == 1)
        fprintf(ptr, "%s, Alarme tocou pois presença foi detectada pelo SENSOR_PRESENCA_COZINHA\n", s);
    if (nSensor == 2)
        fprintf(ptr, "%s, Alarme tocou pois abertura foi detectada pelo SENSOR_ABERTURA_PORTA_COZINHA\n", s);
    if (nSensor == 3)
        fprintf(ptr, "%s, Alarme tocou pois abertura foi detectada pelo SENSOR_ABERTURA_JANELA_COZINHA\n", s);
    if (nSensor == 4)
        fprintf(ptr, "%s, Alarme tocou pois abertura foi detectada pelo SENSOR_ABERTURA_PORTA_SALA\n", s);
    if (nSensor == 5)
        fprintf(ptr, "%s, Alarme tocou pois abertura foi detectada pelo SENSOR_ABERTURA_JANELA_SALA\n", s);
    if (nSensor == 6)
        fprintf(ptr, "%s, Alarme tocou pois abertura foi detectada pelo SENSOR_ABERTURA_JANELA_QUARTO_01\n", s);
    if (nSensor == 7)
        fprintf(ptr, "%s, Alarme tocou pois abertura foi detectada pelo SENSOR_ABERTURA_JANELA_QUARTO_02 \n", s);
    fclose(ptr);
    system("omxplayer --no-keys beep.mp3 > /dev/null 2>&1 &");
}