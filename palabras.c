#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LONGITUD_PALABRA 100

int main()
{
    //Cada palabra se va a almacenar en buffer
    char buffer[MAX_LONGITUD_PALABRA];
    // El programa termina con ctrl + C
    // Permite palabras de hasta 99 caracteres inclusive(tener en cuenta /0)
    while (scanf("%99s", buffer) != EOF) {
        printf( "%s \n", buffer);
    }
    exit(EXIT_SUCCESS);
}
