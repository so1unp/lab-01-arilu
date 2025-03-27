#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h> // Para usar write()

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
                    if (indice >= MAX_LONGITUD - 1) { // Validación de longitud
                        char mensajeError[] = "Error: palabra demasiado larga.\n";
                        write(STDERR_FILENO, mensajeError, sizeof(mensajeError) - 1); // Escribir en stderr
                        exit(EXIT_FAILURE);
                    }
                    palabra[indice] = (char)caracter;
                    indice++;
                    caracter = getchar();
                }
                palabra[indice] = '\0';

                // Imprimir bytes aleatorios y la palabra
                for (int i = 0; i < indice; i++) {
                    for (int j = 0; j < NUM_BYTES_ALEATORIOS; j++) {
                        char charAleatorio = (char)((rand() % 95) + 32);
                        write(STDOUT_FILENO, &charAleatorio, 1); // Escribir el byte aleatorio
                    }
                    write(STDOUT_FILENO, &palabra[i], 1); // Escribir el carácter original de la palabra
                }
                char saltoDeLinea = '\n';
                write(STDOUT_FILENO, &saltoDeLinea, 1); // Escribir un salto de línea
            }
            break;
        }
        case 2: { // Leer mensaje desde argumentos
            char *mensaje = argv[1];
            for (int i = 0; mensaje[i] != '\0'; i++) {
                // Generar y escribir bytes aleatorios
                for (int k = 0; k < NUM_BYTES_ALEATORIOS; k++) {
                    char charAleatorio = (char)((rand() % 95) + 32); // ASCII imprimible
                    write(STDOUT_FILENO, &charAleatorio, 1); // Escribir un byte aleatorio
                }
                // Escribir el carácter original del mensaje
                write(STDOUT_FILENO, &mensaje[i], 1); // Escribir el carácter actual
            }
            // Escribir un salto de línea al final
            char saltoDeLinea = '\n';
            write(STDOUT_FILENO, &saltoDeLinea, 1); // Escribir un salto de línea
            break;
        }
        
        case 3: { // Leer mensaje y guardar en archivo
            int archivoSalida = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (archivoSalida == -1) {
                perror("Error al abrir el archivo");
                exit(EXIT_FAILURE);
            }

            char *mensajeEntrada = argv[2];
            for (int i = 0; mensajeEntrada[i] != '\0'; i++) {
                for (int j = 0; j < NUM_BYTES_ALEATORIOS; j++) {
                    char charAleatorio = (char)((rand() % 95) + 32);
                    write(archivoSalida, &charAleatorio, 1);
                }
                write(archivoSalida, &mensajeEntrada[i], 1);
            }
            char saltoDeLinea = '\n';
            write(archivoSalida, &saltoDeLinea, 1);

            close(archivoSalida);
            break;
        }
        default: {
            char mensjError[] = "Uso incorrecto. Intenta con 1 o 2 argumentos.\n";
            write(STDIN_FILENO, mensjError, sizeof(mensjError) - 1);
            
            break;
        }
    }

    exit(EXIT_SUCCESS);
}

