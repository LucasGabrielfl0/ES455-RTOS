#include <stdio.h>

#define MAX_MESSAGE 100

int main(){
    char INMessage[MAX_MESSAGE];
    printf("=============================================================== \n");
    printf("Message to be removed: \n");
    fgets(INMessage, MAX_MESSAGE, stdin);
    printf("\n[OUTPUT]: %s",INMessage);
    printf("\n=============================================================== \n");


    return 0;
}