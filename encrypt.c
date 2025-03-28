#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h> // Para usar write() y read()
#include <string.h>

#define MAX_LONGITUD 100
#define NUM_BYTES_ALEATORIOS 7

// Función genérica para encriptar desde cualquier entrada
void encriptar(int fd, const char *mensaje, size_t longitud) {
    for (size_t i = 0; i < longitud; i++) {
        // Generar y escribir bytes aleatorios
        for (int j = 0; j < NUM_BYTES_ALEATORIOS; j++) {
            char charAleatorio = (char)((rand() % 95) + 32); // ASCII imprimible
            write(fd, &charAleatorio, 1); // Escribir un byte aleatorio
        }
        // Escribir el carácter original
        write(fd, &mensaje[i], 1); // Escribir el carácter actual
    }
}

int main(int argc, char *argv[]) {
    // Inicializar semilla para números aleatorios
    srand((unsigned int)time(NULL));

    switch (argc) {
        case 1: { // Leer desde la entrada estándar usando read
            char buffer[MAX_LONGITUD];
            ssize_t bytesLeidos;

            bytesLeidos = read(STDIN_FILENO, buffer, MAX_LONGITUD);
            if (bytesLeidos == -1) {
                perror("Error al leer la entrada estándar");
                exit(EXIT_FAILURE);
            }

            encriptar(STDOUT_FILENO, buffer, (size_t)bytesLeidos);
            char saltoDeLinea = '\n'; 
            write(STDOUT_FILENO, &saltoDeLinea, 1);

            break;
        }
        case 2: { // Leer mensaje desde argumentos
            char *mensaje = argv[1];
            encriptar(STDOUT_FILENO, mensaje, strlen(mensaje));
            char saltoDeLinea = '\n'; 
            write(STDOUT_FILENO, &saltoDeLinea, 1);
            break;
        }
        case 3: { // Leer mensaje y guardar en archivo
            int archivoSalida = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (archivoSalida == -1) {
                perror("Error al abrir el archivo");
                exit(EXIT_FAILURE);
            }

            char *mensajeEntrada = argv[2];
            
            encriptar(archivoSalida, mensajeEntrada, strlen(mensajeEntrada));
            char saltoDeLinea = '\n'; 
            write(archivoSalida, &saltoDeLinea, 1);

            close(archivoSalida); // Cerrar el archivo
            break;
        }
        default: {
            char mensajeError[] = "Uso incorrecto. Intenta con 2 o 3 argumentos.\n";
            write(STDERR_FILENO, mensajeError, sizeof(mensajeError) - 1);
            break;
        }
    }

    return 0;
}