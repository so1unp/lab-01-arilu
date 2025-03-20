#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LONGITUD_PALABRA 100

int main()
{
    int c;
    // El programa termina con ctrl + C
    c = getchar();
    //En el buffer se almacena la palabra temporalmente
    char buffer[MAX_LONGITUD_PALABRA];
    while(c != EOF){
        int k = 0;
        while(c != ' ' && c != '\n'){  
            buffer[k] = (char) c; 
            k++;
            c = getchar();
        }
        buffer[k] = '\0';

        if(k > 0){
            printf("%s \n", buffer);
        }
        
        c = getchar();
    }
    
    exit(EXIT_SUCCESS);
}
