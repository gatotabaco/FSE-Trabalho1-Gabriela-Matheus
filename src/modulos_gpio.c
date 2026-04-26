#include <pigpio.h>
#include <stdio.h>
#include "modulos.h"
#include "semaforo.h"

void inicializa_pins(){

    // configurando os pinos dos LEDs do Modelo 1 como saída
    gpioSetMode(M1_VERDE, PI_OUTPUT);
    gpioSetMode(M1_AMARELO, PI_OUTPUT);
    gpioSetMode(M1_VERMELHO, PI_OUTPUT);

    // configurando os pinos dos LEDs do Modelo 2 como saída
    gpioSetMode(M2_BIT0, PI_OUTPUT);
    gpioSetMode(M2_BIT1, PI_OUTPUT);
    gpioSetMode(M2_BIT2, PI_OUTPUT);

    
    // configurando os pinos dos botões como entrada com pull-down
    int botoes[] = {BOTAO_M1_P, BOTAO_M1_C, BOTAO_M2_P, BOTAO_M2_C};
    for (int i = 0; i < 4; i++) {
        gpioSetMode(botoes[i], PI_INPUT);
        gpioSetPullUpDown(botoes[i], PI_PUD_DOWN); // ativa o pull-down interno
    }

    
    // configurando as interrupções para os botões, para detectar quando eles forem pressionados
    gpioSetISRFunc(BOTAO_M1_P, RISING_EDGE, 0, callback_botao_m1_p);
    gpioSetISRFunc(BOTAO_M1_C, RISING_EDGE, 0, callback_botao_m1_c);
    gpioSetISRFunc(BOTAO_M2_P, RISING_EDGE, 0, callback_botao_m2_p);
    gpioSetISRFunc(BOTAO_M2_C, RISING_EDGE, 0, callback_botao_m2_c);
}

// funções para atualizar os LEDs dos semáforos, chamadas pelas threads de cada modelo
void atualiza_modelo_1(int verde, int amarelo, int vermelho){
    gpioWrite(M1_VERDE, verde);
    gpioWrite(M1_AMARELO, amarelo);
    gpioWrite(M1_VERMELHO, vermelho);
}

void atualiza_modelo_2(int codigo){
    // o código é um número de 0 a 7 que representa os estados dos LEDs do modelo 2, onde cada bit do número representa um LED (bit 0 = o bit menos significativo)
    gpioWrite(M2_BIT0, (codigo >> 0) & 1); // pega o primeiro bit empurrando o código 0 posições para a direita e fazendo um AND com 1 para pegar apenas o bit desejado
    gpioWrite(M2_BIT1, (codigo >> 1) & 1); // pega o segundo bit empurrando o código 1 posição para a direita e fazendo um AND com 1 para pegar apenas o bit desejado
    gpioWrite(M2_BIT2, (codigo >> 2) & 1); // pega o terceiro bit empurrando o código 2 posições para a direita e fazendo um AND com 1 para pegar apenas o bit desejado
}