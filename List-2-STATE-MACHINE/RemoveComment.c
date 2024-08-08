/*===================================== RTOS: COMMENT REMOVER USING A STATE MACHINE =====================================*/
/* Sumary:
 * This Program takes text as input, and returns the same text without the comments 
 * comment is defined as the message between /'* and *'/
 * EX: |Input: Hello/'*People*'/ of earth |   Output:Hello /'* *'/ of earth 
 
 */

#include <stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAX_MESSAGE     1024        // Max number or char
#define MAX_COMMENTS    100         // Number of possible comments x2

typedef enum{
    // STATE1,STATE2,STATE3
    S0_START,S1_REMOVE,S2_PRINT, S3_FINISH

} states;

typedef enum{
    Input1,Input2,Input3,Input4,Input5,Input6

} inputs;

int main(){

    char MsgBuffer[MAX_MESSAGE];    // Output Message
    int Response=0;
    states STATE =S0_START;
    inputs INPUT =Input1;

    char IN_Message[MAX_MESSAGE]={""};
    char OUT_Message[MAX_MESSAGE]={""};    // Output Message
    int Comment_Start[MAX_COMMENTS]={-1};
    int Comment_End[MAX_COMMENTS]={-1};


    int Buffer_Index=0;
    int Comment_Index=0;
    char space[1]={" "};
    int IndexArray[MAX_COMMENTS]={-1};
    unsigned int Comment_counter_1=0;
    int flag=0;
    int Output_Index=0;


    while (1){
        switch (STATE) {
        /* STATE 0: ASK FOR NEW MESSAGE */
            case S0_START:
                Output_Index=0;
                flag =0;

                //Asks for new message: and waits
                printf("[COMMENT REMOVER]: Give me a code as input and i will remove the comments that use /* */: \n");
                printf("[INPUT]: ");
                fgets(IN_Message, MAX_MESSAGE, stdin);
                        // INPUT = Input2;
                for(int Input_Index=0; Input_Index < MAX_MESSAGE-1; Input_Index++){
                    // Start of comment
                    if(IN_Message[Input_Index]=='/' && IN_Message[Input_Index+1]=='*' ){
                        flag=1;
                        Comment_counter_1++;

                    }

                    // End of comment
                    if(IN_Message[Input_Index]=='*' && IN_Message[Input_Index+1]=='/' ){
                        Input_Index+=2; // Jumps the */
                        flag=0;
                    }

                    if (flag==0){
                        OUT_Message[Output_Index] = IN_Message[Input_Index];
                        Output_Index++;
                    }
                }
                STATE= S2_PRINT;
                break;

        /* STATE 1: ASK FOR NEW MESSAGE */
            case S1_REMOVE:
                break;
            
        /* ASKS FOR MESSAGE */
            case S2_PRINT:
                switch (Comment_counter_1){
                    case 0:
                        // printf("%s \n",IN_Message);
                        printf("lets go: %s", OUT_Message);    
                        STATE=S3_FINISH;
                        break;
                
                    default:
                        printf("lets go: %s", OUT_Message);    
                        STATE=S3_FINISH;
                        break;
                }
                break;

        /* ṔRINTS CUT MESSAGE */
            case S3_FINISH:
                printf("\nPress 1 to Restart, 0 to Close: \n");
                scanf("%d",&Response);
                getchar();
                switch (Response) {
                    case 1:
                        STATE= S0_START;
                        memset(IN_Message, 0, sizeof(IN_Message));
                        memset(OUT_Message, 0, sizeof(OUT_Message));

                        break;                

                    default:
                        return 0;
                }       
        }
    }


    return 0;
}