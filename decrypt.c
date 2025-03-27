#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// El número de bytes random antes de un carácter
#define NUM_BYTES_RAND 7

// Función para desencriptar un mensaje
void desencriptarMensaje(const int fd) {
    ssize_t bytesRead;
    char buffer[NUM_BYTES_RAND + 1] = {0};

    while ((bytesRead = read(fd, buffer, NUM_BYTES_RAND + 1)) > 0) {
        // Verifica si se leyeron exactamente NUM_BYTES_RAND + 1 bytes
        if (bytesRead == NUM_BYTES_RAND + 1) {
            write(STDOUT_FILENO, &buffer[NUM_BYTES_RAND], 1);
        }
    }

    if (bytesRead < 0) {
        perror("Error al leer");
        exit(EXIT_FAILURE);
    }
}

// Función para leer desde un archivo y desencriptar
void leerDesdeArchivo(const char *archivo) {

    // Abrir el archivo en modo solo lectura
    int fd = open(archivo, O_RDONLY);
    if (fd == -1) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    // Desencriptar el mensaje
    desencriptarMensaje(fd);

    //cierra el archivo
    close(fd);
}

int main(int argc, char *argv[])
{
    //Bucle mientras no se lea EOF
    //Leer un byte
    //Ignorar los siguientes 7 bytes

    if(argc ==1){
        // Lee desde la entrada estandar
        desencriptarMensaje(STDIN_FILENO);
        
    }else if(argc == 2){
        // Lee desde un archivo
        leerDesdeArchivo(argv[1]);
    }else{
        char mensajeError[] = "Uso incorrecto. Pruebe con un argumento o sin ninguno."; 
        // Mensaje de uso incorrecto
        write(STDOUT_FILENO, mensajeError, sizeof(mensajeError)-1);
    }
    //write(STDOUT_FILENO,'\n', 1);       

    printf("\n");
    exit(EXIT_SUCCESS);
}