#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LONGITUD_PALABRA 100
// El número de bytes random antes de un carácter
#define NUM_BYTES_RAND 7

int main(int argc, char *argv[])
{
    // Bucle mientras no se lea EOF
    //Leer un byte
    //Ignorar los siguientes 7 bytes
    int contador = 1;

    if(argc ==1){
            int car;
            // El programa termina con ctrl + C
            car = getchar();
            //En el buffer se almacena la palabra temporalmente
            char buffer[MAX_LONGITUD_PALABRA]={0};
                        
            while(car != EOF){
                contador = 1; 
                int index = 0;
                while(car != ' ' && car != '\n' && car != EOF){  
                    if(contador%8 == 0){
                        //escribe la letra cada 7 chars
                        buffer[index] = (char) car;
                        index++;
                    }
                    contador++;
                    car = getchar();
                }
                buffer[index] = '\0';
        
                if(contador > 1){
                    printf("%s ", buffer);
                }
                        
                car = getchar();
            }
    }else{
            //lee el mensaje, lo desencripta y lo guarda en un archivo
            struct stat fileStat;

            // Abrir el archivo en modo solo lectura
            int fd = open(argv[1], O_RDONLY);
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
            char mensajeArchivo[fileStat.st_size+1];

            ssize_t bytesRead = read(fd, mensajeArchivo, sizeof(mensajeArchivo) - 1);
            if (bytesRead == -1) {
                perror("Error al leer el archivo");
                close(fd);
                exit(EXIT_FAILURE);
            }

            // desencrita el mensaje y lo imprime
            for (int i = 0; mensajeArchivo[i] != '\0'; i++){
                if(mensajeArchivo[i]!= ' '){
                    if(contador%8 == 0){
                        printf("%c", mensajeArchivo[i]);
                    }
                    contador++; 
                }else{
                    contador = 1;
                    printf(" ");
                }
                
            }
    }
    printf("\n");       

    exit(EXIT_SUCCESS);
}
