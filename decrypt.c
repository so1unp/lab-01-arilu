#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LONGITUD_PALABRA 100
// El número de bytes random antes de un carácter
#define NUM_BYTES_RAND 7

// Función para desencriptar un mensaje
void desencriptarMensaje(const char *mensaje) {

    // Contador: permite saber cuandos caracteres se leyeron
    int contador = 1;
    
    for (int i = 0; mensaje[i] != '\0'; i++) {

        if (mensaje[i] != ' ' && mensaje[i] != '\n' && mensaje[i] != '\t') {
            // Imprime el caracter si ya se leyeron los caracteres aleatorios
            if ((contador % (NUM_BYTES_RAND +1)) == 0) {
                printf("%c", mensaje[i]);
            }
            contador++;
        } else {
            //reinicia el contador y hace la separacion correspondiente (las más comunes)
            contador = 1; 

            switch(mensaje[i]){
                case ' ':
                    printf(" ");
                    break;
                case '\n':
                    printf("\n");
                    break;
                case '\t':
                    printf("\t");
                    break;
                default:
                    break;
            }
        }
    }
}

// Función para leer desde la entrada estándar y desencriptar
void leerDesdeEntradaEstandar() {
    
    // Lee un byte
    int car = getchar();
    //En el buffer se almacena la palabra temporalmente
    char buffer[MAX_LONGITUD_PALABRA]={0};
    //index del buffer
    int index;

    while(car != EOF){
        //Reinicia el indice del buffer despues de cada palabra leida
        index = 0;

        //Lee la palabra mientras no sea un salto de linea o un EOF
        while(car != '\n' && car != EOF && car != '\t'){ 
            buffer[index] = (char) car;
            index++;
            car = getchar();
        }
        
        //Si se leyo una palabra
        if(index > 0){
            buffer[index] = '\0';
            desencriptarMensaje(buffer);
            printf("\n");
        }
                        
        car = getchar();
    }
}

// Función para leer desde un archivo y desencriptar
void leerDesdeArchivo(const char *archivo) {

    //lee el mensaje, lo desencripta y lo guarda en un archivo
    struct stat fileStat;

    // Abrir el archivo en modo solo lectura
    int fd = open(archivo, O_RDONLY);
    if (fd == -1) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    // Obtener información del archivo
    if (fstat(fd, &fileStat) == -1) {
        perror("Error al obtener información del archivo");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // crea un buffer del tamaño del archivo a leer
    /* 
        * Limitacion! 
        * de esta forma solo funciona al leer archivos de tamaño pequeño
        * ya que se guarda en la pila y se ve limitado por esta
    */
    char mensajeArchivo[fileStat.st_size+1];

    // Lee el archivo y almacena el contenido en mensajeArchivo
    ssize_t bytesRead = read(fd, mensajeArchivo, sizeof(mensajeArchivo) - 1);
    if (bytesRead == -1) {
        perror("Error al leer el archivo");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Asegurar que el buffer termine en '\0'
    mensajeArchivo[bytesRead] = '\0'; 

    // Desencriptar el mensaje
    desencriptarMensaje(mensajeArchivo);

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
        leerDesdeEntradaEstandar();
    }else if(argc == 2){
        // Lee desde un archivo
        leerDesdeArchivo(argv[1]);
    }else{
        // Mensaje de uso incorrecto
        printf("Uso incorrecto. Pruebe con un argumento o sin ninguno.");
    }
    printf("\n");       

    exit(EXIT_SUCCESS);
}