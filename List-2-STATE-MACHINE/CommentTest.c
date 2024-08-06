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
    char* ptr;

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
    int alo=0;
    char space[1] =" ";
    int j=0;
    for(int i=0; i < MAX_MESSAGE; i++){
        if(i==Comment_Start[j]){
            OUT_Message[alo]=IN_Message[i];
            OUT_Message[alo+1]=IN_Message[i+1];
            OUT_Message[alo+2]=space[0];
            i=Comment_End[j];
            OUT_Message[alo+3]=IN_Message[i];
            OUT_Message[alo+4]=IN_Message[i+1];
            i+=1;
            alo+=4;
            j++;
            // printf("\n here 1 \n");
            if (j> Comment_counter_1){
                j=0;
            }
        }
        else{
            OUT_Message[alo]=IN_Message[i];
        }

        alo++;
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