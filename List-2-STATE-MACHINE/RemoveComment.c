/*===================================== RTOS: COMMENT REMOVER USING A STATE MACHINE =====================================*/
/* Sumary:
 * This Program takes text as input, and returns the same text without the comments 
 * comment is defined as the message between /'* and *'/
 * EX: |Input: Hello/'*People*'/ of earth |   Output:Hello /'* *'/ of earth 
 
 */

#include <stdio.h>
#include <string.h>

#define MAX_MESSAGE     1024        // Max number or char
#define MAX_COMMENTS    100         // Number of possible comments x2

typedef enum{
    // STATE1,STATE2,STATE3
    S0_START,S1_READ,S2_CUT, S3_PRINT

} states;

typedef enum{
    Input1,Input2

} inputs;

int main(){
    char INMessage[MAX_MESSAGE];    // Input Message
    char MsgBuffer[MAX_MESSAGE];    // Output Message
    int IndexArray[MAX_COMMENTS]={-1};
    char* ptr;
    states STATE;
    inputs INPUT;

    while (1){
        switch (STATE) {
        /* STATE 0: ASK FOR NEW MESSAGE */
            case S0_START:
                switch (INPUT){
                    /* ASKS FOR NEW MESSAGE */
                    case Input1:
                        printf("[COMMENT REMOVER]: \n");
                        printf("Message to be removed: \n");
                        printf("[INPUT]: ");
                        fgets(INMessage, MAX_MESSAGE, stdin);
                        STATE = S1_READ;
                        break;
                    
                    /* ERROR MESSAGE */                        
                    case Input2:
                        INPUT= Input1;
                    
                        break;

                    // case Input3:
                    //     break;
                    
                    /* ASKS FOR NEW MESSAGE */
                    default:
                        break;
                }


                break;

        /* STATE 1: ASK FOR NEW MESSAGE */
            case S1_READ:

                break;
            
            /* ASKS FOR MESSAGE */
            case S2_CUT:
                break;

            /* ṔRINTS CUT MESSAGE */
            case S3_PRINT:
                printf(MsgBuffer);
                break;
    
            default:
                break;
        }
    }

    // while (1){
    //     printf("hm");


    // }

 
 
    printf("\n[OUTPUT]: %s",INMessage);
    printf("\n=============================================================== \n");


    return 0;
}