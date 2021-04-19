#include <stdio.h>
#include "../inc/servidor.h"

void chamaMenu(struct servidorCentral intermediario)
{
    int opcao = 0;
    // struct servidorCentral *intermediario = malloc(sizeof(struct servidorCentral));

    // printf("L01: %d\n", newValues->machines[0].state);
    printf("------- Bem vindo ao trabalho 2 -------\n");
    // printf("Escolha um comando de 0 a 5.\n 0 a 3 sendo as lâmpadas,\n 4 e 5 ar - condicionados\n 9 - Sair\n");
    // printf("Estado atual:");
    printf("Temperatura: %f\n", intermediario.temperatura);
    printf("Umidade: %f\n", intermediario.umidade);
    printf("LAMPADA_01: %d\n", intermediario.machines[0].state);
    printf("LAMPADA_02: %d\n", intermediario.machines[1].state);
    printf("LAMPADA_03: %d\n", intermediario.machines[2].state);
    printf("LAMPADA_04: %d\n", intermediario.machines[3].state);
    printf("ARCONDICIONADO_01: %d\n", intermediario.machines[4].state);
    printf("ARCONDICIONADO_02: %d\n", intermediario.machines[5].state);
    printf("SENSOR_PRESENCA_SALA: %d\n", intermediario.sensors[0].state);
    printf("SENSOR_PRESENCA_COZINHA: %d\n", intermediario.sensors[1].state);
    printf("SENSOR_ABERTURA_PORTA_COZINHA: %d\n", intermediario.sensors[2].state);
    printf("SENSOR_ABERTURA_JANELA_COZINHA: %d\n", intermediario.sensors[3].state);
    printf("SENSOR_ABERTURA_PORTA_SALA: %d\n", intermediario.sensors[4].state);
    printf("SENSOR_ABERTURA_JANELA_SALA: %d\n", intermediario.sensors[5].state);
    printf("SENSOR_ABERTURA_JANELA_QUARTO_01: %d\n", intermediario.sensors[6].state);
    printf("SENSOR_ABERTURA_JANELA_QUARTO_02: %d\n", intermediario.sensors[7].state);
    // scanf("%d", &opcao);
    // gpioLigaEquipamentos(opcao);
}
