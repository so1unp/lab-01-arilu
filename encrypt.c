#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LONGITUD 100
#define NUM_BYTES_ALEATORIOS 7

int main(int argc, char *argv[]) {
    // Inicializar semilla para números aleatorios
    srand((unsigned int)time(NULL));

    switch (argc) {
        case 1: { // Leer desde la entrada estándar
            int caracter = getchar();
            char palabra[MAX_LONGITUD];
            while (caracter != EOF) {
                int indice = 0;
                while (caracter != ' ' && caracter != '\n' && caracter != EOF) {
                    palabra[indice] = (char)caracter;
                    indice++;
                    caracter = getchar();
                }
                palabra[indice] = '\0';

                // Imprimir bytes aleatorios y la palabra
                for (int i = 0; i < indice; i++) {
                    for (int j = 0; j < NUM_BYTES_ALEATORIOS; j++) {
                        char charAleatorio = (char)(rand() % 256);
                        printf("%c", charAleatorio);
                    }
                    printf("%c", palabra[i]);
                }
                printf("\n");

                caracter = getchar();
            }
            break;
        }
        case 2: { // Leer mensaje desde argumentos
            char *mensaje = argv[1];
            for (int i = 0; mensaje[i] != '\0'; i++) {
                for (int k = 0; k < NUM_BYTES_ALEATORIOS; k++) {
                    char charAleatorio = (char)(rand() % 256);
                    printf("%c", charAleatorio);
                }
                printf("%c", mensaje[i]);
            }
            printf("\n");
            break;
        }
        case 3: { // Leer mensaje y guardar en archivo
            if (argc != 3) {
                printf("Uso: %s <archivo> <mensaje>\n", argv[0]);
                exit(EXIT_FAILURE);
            }

            FILE *archivoSalida = fopen(argv[1], "w");
            if (archivoSalida == NULL) {
                perror("Error al abrir el archivo");
                exit(EXIT_FAILURE);
            }

            char *mensajeEntrada = argv[2];
            for (int i = 0; mensajeEntrada[i] != '\0'; i++) {
                for (int j = 0; j < NUM_BYTES_ALEATORIOS; j++) {
                    char charAleatorio = (char)(rand() % 128);
                    fprintf(archivoSalida, "%c", charAleatorio);
                }
                fprintf(archivoSalida, "%c", mensajeEntrada[i]);
            }
            fprintf(archivoSalida, "\n");

            fclose(archivoSalida);
            break;
        }
        default: {
            printf("Uso incorrecto. Intenta con 2 o 3 argumentos.\n");
            break;
        }
    }

    exit(EXIT_SUCCESS);
}
