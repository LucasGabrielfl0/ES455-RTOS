#include <stdio.h>
#include <string.h>

#define MAX_MESSAGE     1024        // Max number or char
#define MAX_COMMENTS    100         // Number of possible comments x2


int main(){
    char IN_Message[MAX_MESSAGE]={""};
    char OUT_Message[MAX_MESSAGE]={""};    // Output Message
    int Comment_Start[MAX_COMMENTS]={-1};
    int Comment_End[MAX_COMMENTS]={-1};

    int IndexArray[MAX_COMMENTS]={-1};
    unsigned int Comment_counter_1=0;
    unsigned int Comment_counter_2=0;

    while(1){


    printf("\n=============================================================== \n\n");
    printf("C code with comments to be removed: \n");
    printf("[INPUT]: ");

    fgets(IN_Message, MAX_MESSAGE, stdin); 

/* Find index of the comment on the original message */
    for(int i=0; i < MAX_MESSAGE-1; i++){
        if(IN_Message[i]=='/' && IN_Message[i+1]=='*' ){
            Comment_Start[Comment_counter_1]= i;
            Comment_counter_1++;
        }        
        if(IN_Message[i]=='*' && IN_Message[i+1]=='/' ){
            Comment_End[Comment_counter_2]= i;
            Comment_counter_2++;
        }     

    }

    /* Rewrites the original message without comment*/
    int Buffer_Index=0;
    // char space[1] =" ";
    int Comment_Index=0;
    for(int Input_Index=0; Input_Index < MAX_MESSAGE; Input_Index++){
        if(Input_Index==Comment_Start[Comment_Index]){
            // OUT_Message[Buffer_Index]=IN_Message[Input_Index];
            // OUT_Message[Buffer_Index+1]=IN_Message[Input_Index+1];
            OUT_Message[Buffer_Index+2]=" ";
            Input_Index=Comment_End[Comment_Index];
            // OUT_Message[Buffer_Index+3]=IN_Message[Input_Index];
            // OUT_Message[Buffer_Index+4]=IN_Message[Input_Index+1];
            Input_Index+=1;
            
            Buffer_Index+=4;
            Comment_Index++;

            // printf("\n here 1 \n");
            if (Comment_Index > Comment_counter_1){
                Comment_Index=0;
            }
        }
        else{
            OUT_Message[Buffer_Index]=IN_Message[Input_Index];
        }

        Buffer_Index++;
    }

    printf("\n[OUTPUT: ");
    printf("%s \n",OUT_Message);
    printf("\nBegin: %d , End:%d", Comment_Start[1],Comment_End[1]);

    printf("\n\n=============================================================== \n");

    // ptr= strstr(IN_Message,"/*");
    // printf("/*: %s",ptr);
 
    }


    return 0;
}