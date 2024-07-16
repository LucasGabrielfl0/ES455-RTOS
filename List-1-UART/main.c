/* Necessário para funções e macros básicas */
#include <avr/io.h>

/* Os próximos dois includes são necessários quando se usa interrupçoes */
#include <avr/cpufunc.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#define SCAPE       0x7d    // Prefix Character
#define SYNC        0x7e    // Sync Character (Limit between packages)
#define XON         0x11    // Flux Character
#define XOFF        0x13    // Flux Character
#define FREQ_CPU    10      // CPU Frequency
#define BAUD_rATE   9600    // USART baud rate



// Functions used
uint8_t write(uint8_t* buf, uint8_t n, int8_t close_packet);
uint8_t read(uint8_t* buf, uint8_t n);
void flow_off();
void flow_on();
uint8_t is_flow_on();



ISR(USART_RX_vect) {
}

ISR(USART_UDRE_vect) {
}

// tests
void task_1();
void task_2();
void task_3();
void task_4();
void task_5();
void task_6();
void task_7();




int main(void) {
    /* Task 1 */
    // 1: Turn of Led, setup USART
    /*======= Turn of LED =======*/


    /*======= USART SETUP =======*/
    UCSR0A = 0;
    UCSR0B = 0;
    UCSR0C = 0;

    // Transmission Speed
    UBRR0 = 1;


    // Messages to be sent
    // Each Msg is a uint8_t is a interger array of the ascii characters that represent each letter (and spaces)
    uint8_t Msg_1[]= "Universidade Federal de Pernambuco\nDepartamento de Eletrônica e Sistemas";

    uint8_t Msg_2[]= "Desenvolvimento de sistemas embarcados";

    // Enable Interrupts Globally
    sei();

    /* Implemente os testes aqui. Veja o texto para os detalhes */    
    /*======= 2. String + Sync =======*/
    task_2();

    /*======= 3. String (n=10) + Sync =======*/
    task_3();
    
    /*======= 4.  =======*/
    task_4();

    /*======= 5.  =======*/
    _delay_ms(5000);    // Wait 5 ms
    task_4();           // Repeat test 4
    
    /*======= 6.  =======*/
    _delay_ms(5000);    // Wait 5 ms
    task_6();           // Test 6
    
    /* Loop infinito necessário em qualquer programa para embarcados */
    while (1) {
        /*======= 7.  =======*/
        task_7();

    }

    return 0;
}



/*========================================== Functions ==========================================*/
// sends n bytes from the buffer (buf)
uint8_t write(uint8_t* buf, uint8_t n, int8_t close_packet){
    int msg_counter=0;

    // If flow is off, returns 0
    if(is_flow_on()==0){
        return 0;
    }
    
    // if flow is on, sends the 'n' bytes of data
    for(int i=0; i<n; i++){
        // If receives XON, Stops transmission
        if(*(buf+i)== XON){
            break;
        }

        // Sends data 
        UDR0 = *(buf+i);
        msg_counter=i;
    }


    // if close_packet is not zero, sends sync character at the end
    if(close_packet !=0){
        UDR0= SYNC;
    }


    return msg_counter;
}


// Receives n bytes from serial and saves them on the buffer (buf)
uint8_t read(uint8_t* buf, uint8_t n){
    // If flow is off, returns 0
    if(is_flow_on()==0){
        return 0;
    }


    // if flow is on, sends the 'n' bytes of data
    for(int i=0; i<n; i++){
        // If it reads the Sync character, stops reading
        if(*(buf+i)== SYNC){
            break;
        }

        // Sends data 
        UDR0 = *(buf+i);
        msg_counter=i;

        // If the buffer reads n messages before receiving the sync character, return n+1
        if( (i+1) == n ){
            return n+1;
        }
    }


}

// Sends XOFF
void flow_off(){
    UDR0 = XOFF;

}

// Sends XON
void flow_on(){
    UDR0 = XON;
}

// Detects if communication (flow) is on or off
// 1 = flow is on | 0 = flow is off
uint8_t is_flow_on(){

}


void task_1(){
}

/* Task 2 */
// send "Universidade Federal de Pernambuco\nDepartamento de Eletrônica e Sistemas" + sync
void task_2(){
    uint8_t UFPE_DES[]= "Universidade Federal de Pernambuco\nDepartamento de Eletrônica e Sistemas";

}

/* Task 3 */
// send "Universidade Federal de Pernambuco\nDepartamento de Eletrônica e Sistemas" + sync, with n=10
void task_3(){
    // string Dev= "Universidade Federal de Pernambuco\nDepartamento de Eletrônica e Sistemas";
}


/* Task 4 */
void task_4(){

}

/* Task 4 */
void task_5(){
    // wait 5s, and repeat task 4
    task_4();
}
void task_6(){

}

void task_7(){
    // receive package

}