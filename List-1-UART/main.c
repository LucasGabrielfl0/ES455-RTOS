/* Necessário para funções e macros básicas */
#include <avr/io.h>

/* Os próximos dois includes são necessários quando se usa interrupçoes */
#include <avr/cpufunc.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#define SCAPE       0x7d        // Prefix Character
#define SYNC        0x7e        // Sync Character (Limit between packages)
#define XON         0x11        // Flux Character
#define XOFF        0x13        // Flux Character
#define F_OSC       16000000    // CPU Frequency (16MHz)
#define BAUD_RATE   9600        // USART baud rate


/*====================================== GLOBAL VARIABLES ======================================*/
uint8_t FlowControl = 0;      // 1: Flow on | 2: Flow Off
bool ReadyToSend  = 0;        // 1: USART is Ready to send another message | 2: USART is not ready
bool ByteReceived  = 0;       // 1: USART received a msg | 2: no message received


/*====================================== FUNCTIONS USED ======================================*/
// Mandatory
uint8_t write(uint8_t* buf, uint8_t n, int8_t close_packet);	    // Writes buff in usart
uint8_t read(uint8_t* buf, uint8_t n);                       	    // Reads data from USART
void flow_off();                                              	    // Sends XOFF
void flow_on();													    // Sends XON
uint8_t is_flow_on();											    // Returns if flow is or or off

// Custom
void CompareMsg(uint8_t* msg_1, uint8_t* msg_2, uint8_t n);		    // Compares 2 messages and turns LED accordingly
uint8_t read_2(uint8_t* buf, uint16_t n)                            //
void SendByte(uint8_t buff);		                                // Blocks system until sends Byte
uint8_t ReadByte();		                                            // Blocks system until receives Byte
void Set_LED(uint8_t State);

// Mandatory Tests (1 and 5 are in the main)
void task_2();
void task_3();
void task_4();
void task_6();
void task_7_A();
void task_7_B();


/*====================================== INTERRUPTS ======================================*/
// Called when USART regiter receives a byte
ISR(USART_RX_vect) {
    ByteReceived = true;
    if(UDR0== XON){
        flow_on();
    }
    if(UDR0== XOFF){
        flow_off();
    }
}

// Called when USART register can send another byte
ISR(USART_UDRE_vect) {
    ReadyToSend = true;
}



int main(void) {
	/* Task 1 */
    // 1: Turn off Led, setup USART
    /*======= LED SETUP =======*/
	DDRB = 1 << PB5;			// Sets PB5 (LED) as output (DDR=1)
    PORTB &= ~(1 << PB5);     	// Turns OFF LED

    /*======= USART SETUP =======*/
    UCSR0A = 0;                                                 //
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);                      // Enable Interrupts
    UCSR0B |= (1 << RXCIE0) | (1 << UDRIE0) | (1 << TXCIE0);    // Enable Transmission and Reception
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);                     // Sets that: 1 Byte = 8 bits

    // Transmission Speed
    // UBRR =Fosc/(16* BaudRate) -1 => [16M/(16*9600)] - 1 = 103.166
	UBRR0H = 0;
    UBRR0L = 103;

    // Enable Interrupts Globally
    sei();

    /*------------------------------------------ REQUIRED TESTS ----------------------------------------*/    
    /*======= 2.  =======*/
    task_2();

    /*======= 3.  =======*/
    task_3();
    
    /*======= 4.  =======*/
    task_4();

    /*======= 5.  =======*/
    PORTB &= ~(1 << PB5);     // Turns OFF LED
    task_4();                 // Repeat test 4
    
    /*======= 6.  =======*/
    PORTB &= ~(1 << PB5);     // Turns OFF LED    
    task_6();                 // Test 6
    
    
    /* Loop infinito necessário em qualquer programa para embarcados */
    while (1) {
        /*======= 7.  =======*/
        task_7_A();
        task_7_B();

    }

    return 0;
}



/*========================================== Functions ==========================================*/
// sends n bytes from the buffer (buf)
uint8_t write(uint8_t* buf, uint8_t n, int8_t close_packet){
    uint8_t msg_counter=0;

    // If flow is off, returns 0
    if(is_flow_on()==0){
        return 0;
    }

   // if flow is on, sends the 'n' bytes of data
    for(int i=0; i<n; i++){
        // If receives XOFF, Stops transmission
        if(!is_flow_on){
            break;
        }

        SendByte( *(buf+i) );       // Sends the byte via USART
        msg_counter++;              // Updates Counter

    }

    // if close_packet is not zero, sends sync character at the end
    if(close_packet !=0){
        SendByte(SCAPE);    // Scape as prefix
        SendByte(SYNC);     // sync        
    }

    return msg_counter;
}


// Receives n bytes from serial and saves them on the buffer (buf)
uint8_t read(uint8_t* buf, uint8_t n){
	uint8_t msg_counter=0;
    uint8_t ByteBuffer =0;

  	// The maximum value of n must be 254
  	if (n==255){
    	n=254;
  	}

	// If flow is off, returns 0
  	if(is_flow_on()==0){
    	return 0;
  	}

  	// if flow is on, reads the 'n' bytes of data
  	for(int i=0; i<n; i++){
        ByteBuffer= ReadByte();        

        // If it reads the sync character, stops reading
        if(ByteBuffer == SYNC){
            break;
        }

        *(buf+i) = ByteBuffer;    // Saves data in the buffer 
        msg_counter=i;              // Updates counter

        // If it reads n messages before receiving the sync character, returns n+1
        if( (i+1) == n ){
            return n+1;
        }
    }

	return msg_counter;
}


// Sends XOFF
void flow_off(){
  FlowControl = 0;  // Sets flow control as off
  UDR0 = SCAPE;     // SCAPE prefix before XON or XOFF
  UDR0 = XOFF;

}

// Sends XON
void flow_on(){
  FlowControl = 0;  // Sets flow control as OON
  UDR0 = SCAPE;     // CAPE prefix before XON or XOFF
  UDR0 = XON;
}

// Detects if communication (flow) is on or off
// 1 = flow is on | 0 = flow is off
uint8_t is_flow_on(){
  return FlowControl;
}


/*========================================== MANDATORY TEST FUNCTIONS ==========================================*/
/* Task 2 */
void task_2(){
    uint8_t UFPE_DES[]= "Universidade Federal de Pernambuco\nDepartamento de Eletrônica e Sistemas";
    uint8_t n_sent= write(UFPE_DES,sizeof(UFPE_DES), 1);
}

/* Task 3 */
void task_3(){
    uint8_t UFPE_DES[]= "Universidade Federal de Pernambuco\nDepartamento de Eletrônica e Sistemas";
    uint8_t n_sent= write(UFPE_DES,10, 1);
}

/* Task 4 */
void task_4(){
    int MsgCounter = 0;
    uint8_t ByteBuffer=0;
    uint8_t Msg_buffer[303];

    // Reads 300 packages
  	for(int i=0; i<300; i++){
        ByteBuffer= ReadByte();    
        // If it reads the sync character, stops reading
        if(ByteBuffer == SYNC){
            break;
        }
        Msg_buffer[i] = ByteBuffer;
        MsgCounter++;
    }

    //After 300 reads, sends XOFF
    if(MsgCounter==300){
        flow_off();
        _delay_ms(10); // blocks 10 ms
    }

    //if it stops receiving messages, blinks LED at 1Hz for 5s (1 time per sec)
    if(!ByteReceived){
        for(int i=0;i<5;i++){
            PINB ^= (1 << PB5);   //toogle led
            _delay_ms(1000);      // wait 1s
        }
    }
    // if the messages continue LED is turned on for 5s 
    else{
    Set_LED(1)              // Turns ON LED
    _delay_ms(5000);        // Wait 5s
    }

    Set_LED(0);     // Turns off LED
}

/* Task 6 */
void task_6(){
    uint8_t Binary_String[]={0x00, 0x01, 0x11, 0x02, 0x13, 0x04, 0x7e, 0x05, 0x7d, 0x06};
    uint8_t n_Bytes =sizeof(Binary_String)/sizeof(Binary_String[0]);
    //turn off the LED:
    Set_LED(0);


    // Sends the binary string without sync character
    uint8_t n_sent = write(Binary_String, n_Bytes, 0);
    
    // If the data wasnt all sent (received a XOFF in the middle)
    while(n_sent < n_Bytes){
        Set_LED(1);                                                 // Turns on LED
        while(!is_flow_on()){};                                     // Hold the program until receives XON 
        Set_LED(0);                                                 // Sets LED =0;
        n_sent = write(Binary_String+n_sent, n_Bytes-n_sent, 0);    // Resumes transmission (where it left of)
    }
  
}

/* Task 7.A */
void task_7_A(){
    // receive package
    uint8_t msg_DSE[] ="Desenvolvimento de sistemas embarcados";
    uint8_t buffer_1[100]={'',0};
    
    // 7A: Read and compare Msg 1
    read(buffer_1,sizeof(msg_DSE));                   // Read package
    CompareMsg(buffer_1, msg_DSE,sizeof(msg_DSE));    // Compare and Light the led (if the 2 are the same)
    
}

/* Task 7.B */
void task_7_B(){
    // receive package
    uint8_t msg_DSE[] ="Desenvolvimento de sistemas embarcados";
    uint8_t buffer_2[10]={'',0};

    // 7B: Read and compare Msg, but n=10
    read(buffer_2,10);                      // Read package
    CompareMsg(buffer_2, msg_DSE,10);       // Compare and Light the led (if the 2 are the same)
    
}

/*====================================== OTHER FUNCTIONS USED ======================================*/
void CompareMsg(uint8_t* msg_1, uint8_t* msg_2, uint8_t n){
    bool Is_equal = true;

    // If they have different sizes, they are different
    if(sizeof(msg_1) !=sizeof(msg_2)){
        Is_equal = false;
    }

    // Compare array elementy wise
    for(int i=0; i<n; i++){ 
        // If any byte is different, returns false
        if( (*(msg_1+i) != *(msg_2+i)) ) {
            Is_equal = false;
            break;
        }
    }

    // If the messages are the same, turns on LED, if not, turns off
    if(Is_equal){
        // Turns on LED
        Set_LED(1); 
    }
    else{
        // Turns off LED
        Set_LED(0);
    }
}

void SendByte(uint8_t buff){
    while (!ReadyToSend){};     // blocks until it can send 
    UDR0 = buff;                // Sends byte
    ReadyToSend = false;        // Flag

}

uint8_t ReadByte(){
    while (!ByteReceived){};         // blocks until it receives a byte 
    uint8_t ByteBuff = UDR0;        // Reads Received byte
    ByteReceived = false;           // Flag

    return ByteBuff;
}

void Set_LED(bool State){
    if(State ==1){
        PORTB |= (1 << PB5);    // Turns ON LED
    }
    else{
        PORTB &= ~(1 << PB5);   // Turns off LED
    }
}
