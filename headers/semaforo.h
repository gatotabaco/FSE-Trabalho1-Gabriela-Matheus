#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <stdbool.h>


// estados do modelo 1
typedef enum {
    M1_VERDE,
    M1_AMARELO,
    M1_VERMELHO
} EstadoM1;

// Estados do modelo 2
// checar a ordem dos estados conforme o enunciado definiu
// para garantir que a logica do semaforo funcione corretamente

typedef enum{
    M2_ESTADO_0 = 0 // amarelo amarelo, modo noturno (nao usado)
    M2_ESTADO_1 = 1, //verde prin, vermelho cruz
    M2_ESTADO_2 = 2, //amarelo prin, vermelhor cruz
    M2_ESTADO_3 = 3, //amarelo prin, vermelho cruz
    M2_ESTADO_4 = 4, //vermelho prin, vermelho cruz
    M2_ESTADO_5 = 5, //vermelho prin, verde cruz
    M2_ESTADO_6 = 6, //vermelho prin, amarelo cruz
    M2_ESTADO_7 = 7, //vermelho prin, amarelo prin, 1 botao desligado (nao usado)
}

// funcoes que serão executadas pelas threads e são colocadas aqui devido ao requisito
// de modularização do projeto.
// essas funções vão ter os loops que fazem o semáforo rodar infinitamente

void* logica_modelo_1(void* arg);
void* logica_modelo_2(void* arg);

// funções de callback dos botoes, que serão chamadas quando um evento de botão for detectado
// gpio = numero da porta GPIO que disparou oe vento
// level = estado atual no momento do disparo
// tick = tempo em microssegundos no momento do disparo, essencial para o
// controle de debounce dos botoes

void callback_botao_m1_p(int gpio, int level, __uint32_t tick);
void callback_botao_m1_c(int gpio, int level, __uint32_t tick);
void callback_botao_m2_p(int gpio, int level, __uint32_t tick);
void callback_botao_m2_c(int gpio, int level, __uint32_t tick);

#endif