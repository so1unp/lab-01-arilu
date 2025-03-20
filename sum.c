#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int sum = 0;
    int c;

    if(argc == 1){
        //Mientras no se ingrese ctrl + D 
        while ((c = getchar()) != EOF) {
            //En la tabla ASCII los car 0 a 9 son consecutivos
            //0 = 48 
            //9 = 57
            if (c >= '0' && c <= '9') {
                //Se calcula que numero es restando el ascii de 0
                sum += c - '0';
            }
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

