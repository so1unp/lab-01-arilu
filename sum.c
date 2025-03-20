#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int sum = 0;
    int c;
    int aux;

    if(argc == 1){
        char buffer[100];
        c = getchar();
        while(c != EOF){
            aux = 0;
            while(c != ' ' && c != '\n' && c != EOF){
                buffer[aux] = (char) c;
                aux++;
                c = getchar();
            }
            if(aux > 0){
                buffer[aux] = '\0';
                sum += atoi(buffer);
            }
            c = getchar();
        }
        printf("Sumatoria: %d \n", sum);
        
    }else{
        //Recorre todos los argumentos
        for (int i = 0; i < argc; i++){
            sum += atoi(argv[i]);
        }
        printf("Sumatoria: %d \n", sum);
    }
    
    exit(EXIT_SUCCESS);
}

