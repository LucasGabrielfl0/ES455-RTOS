/* Necessário para funções e macros básicas */
#include <avr/io.h>

/* Os próximos dois includes são necessários quando se usa interrupçoes */
#include <avr/cpufunc.h>
#include <avr/interrupt.h>

#include <stdint.h>

/*
* A atividade consistem em 3 partes diferentes:

* 1. Gerar um Pulso Periodico com valor Hex de 0xAA55 que dure entre 3 e 4 μs, a cada 20 μs, 

* 2. Usar o Temporizador 0 para ter um período de 160 μs
*    2.1 fazer o led (pino PB5) piscar com um período de 640 ms
*    2.2 Adicione um atraso de 20 pulsos de clock (use a instrução NOP, que consome exatamente 1 pulso de clock) após modificar o led

* 3. Monitore o recebimento de dados na interface serial
*    3.1 Ao receber um dado verifique se houve erro na recepção
*    3.2 Caso afirmativo, envie de volta o valor 0x7E | Se não houve erro, ecoe de volta o valor recebido.
*    3.3 Configure a comunicação serial para o formato 8N1 a 480 kHz

*/








// 3. Monitoramento da Serial
ISR(USART_RX) {
    /* Verifique se houve erro. Se houve transmita o byte 0xDE. Se não
       houve, ecoe o byte recebido */

}


ISR(TIMER0_OVF_vect) {
    /* Pisque o LED a cada 320 ms */

    /* Introduza um delay de 20 instruções NOP */
    delay(5);
    // Nops(20);

}

/*
 * Função para criar um pequeno delay variável de aproximadamente n
 * us. Máximo de 255 us
 */
void delay(uint8_t n) {
    uint8_t i;

    while (n--)
        for (i=0; i<4; i++)
            asm("nop");
}


/*
 * Função para criar delay de n nops (cada nop = 1 ciclo de clock)
 */
void Nops(uint8_t n) {
    uint8_t i;
    for (i=0; i<n; i++)
        asm("nop");
}

int main(void) {
    /*
     * Configure aqui a porta que controla o LED, iniciando-o apagado
     */
    DDRB = 0;
    PORTB = 0;

    /* Configura o timer 0 para dar timeout a cada 160 us (dica: use
       modo CTC) */
    TCCR0B = 0;
    TIMSK0 = 0;


    /* Configura a interface serial para receber dados no formato 8N1
       a 480 kHz */
    UCSR0A = 0;
    UCSR0B = 0;
    UCSR0C = 0;



    /* Habilita as interrupções */
    sei();


    /* Gera o sinal digital correspondente a 0xAA55. Se usar loop,
       coloque um delay de 2 instruções NOP antes de mudar o sinal */
    while (1) {
        /* O seu código aqui */

        /* Pequeno delay para separar os sinais individuais */
        delay(20);
    }

    return 0;
}
