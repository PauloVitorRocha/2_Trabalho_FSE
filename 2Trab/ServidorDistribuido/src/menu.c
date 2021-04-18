#include <stdio.h>
#include "../inc/gpio.h"

void menu()
{
    struct servidorDistribuido *newValues = malloc(sizeof(struct servidorDistribuido));
    int opcao = 0;
    // printf("L01: %d\n", newValues->machines[0].state);
    printf("------- Bem vindo ao trabalho 2 -------\n");
    while (opcao != 9)
    {
        newValues = updateValues();
        printf("Escolha um comando de 0 a 5.\n 0 a 3 sendo as lâmpadas,\n 4 e 5 ar - condicionados\n 9 - Sair\n");
        // printf("Estado atual:");
        printf("Temperatura: %f\n", newValues->temperatura);
        printf("Umiddade: %f\n", newValues->umidade);
        printf("L01: %d\n", newValues->machines[0].state);
        printf("L02: %d\n", newValues->machines[1].state);
        printf("L03: %d\n", newValues->machines[2].state);
        printf("L04: %d\n", newValues->machines[3].state);
        printf("AC01: %d\n", newValues->machines[4].state);
        printf("AC02: %d\n", newValues->machines[5].state);
        printf("S01: %d\n", newValues->sensors[0].state);
        printf("SENSOR_PRESENCA_SALA: %d\n", newValues->sensors[0].state);
        printf("SENSOR_PRESENCA_COZINHA: %d\n", newValues->sensors[1].state);
        printf("SENSOR_ABERTURA_PORTA_COZINHA: %d\n", newValues->sensors[2].state);
        printf("SENSOR_ABERTURA_JANELA_COZINHA: %d\n", newValues->sensors[3].state);
        printf("SENSOR_ABERTURA_PORTA_SALA: %d\n", newValues->sensors[4].state);
        printf("SENSOR_ABERTURA_JANELA_SALA: %d\n", newValues->sensors[5].state);
        printf("SENSOR_ABERTURA_JANELA_QUARTO_01: %d\n", newValues->sensors[6].state);
        printf("SENSOR_ABERTURA_JANELA_QUARTO_02: %d\n", newValues->sensors[7].state);
        scanf("%d", &opcao);
        if (opcao == 8)
        {
            send_TCP_message(newValues);
        }
        else
        {
            gpioLigaEquipamentos(opcao);
        }
    }
}
