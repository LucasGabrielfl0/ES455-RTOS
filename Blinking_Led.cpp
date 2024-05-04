
/* Necessário para funções e macros básicas */
#include <avr/io.h>

/* Os próximos dois includes são necessários quando se usa interrupçoes */
#include <avr/cpufunc.h>
#include <avr/interrupt.h>

#include <stdint.h>

/* CODE LOGIC:
1. sets D2 pin as an input
2. activates D2 pull up resistor
3. activate the interrupt INT0
4. free interrupts (sei)
5. crate function to toogle energy in
the interrupt

test:
when D2 turns 0 again
(falling edge) activates the interrupt
INT0 and toggles the led

*/

ISR(INT0_vect) {
  //toogle led
  PINB ^= (1 << PB5);
}

int main(void) {

// 1. sets D2 pin as an input (DDR =0)
    DDRD &= ~(1 << PD2);
    
// 2. activates D2 pull up resistor
    PORTD |= (1 << PD2);
    
    // Sets PB5 (LED) as output (DDR=1)
    DDRB = 1 << PB5;

    // EICRA 10 = falling edge
    EICRA |= (1 << ISC01);
    
    // Resets flags 
    EIFR |= (1 << INTF0) | (1 << INTF1);
    
    // Enables only INT0
    EIMSK |= (1 << INT0) | (0 << INT1);
    
    // enable interrupts
    sei();
  
  
    /* Aguarda mudar algo nos estados do botão. */
    while (1) {
        while (!g_pressed)
            ;
        g_pressed = 0;
    }

    return 0;
}