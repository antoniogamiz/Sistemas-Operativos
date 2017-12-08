#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>

/*
* Lee un archivo por bloques y lo escribe en un fichero (salida.txt) contando el número de bloques.
*/

char bufn[80];


int main(int argc, char *argv[]){
    int fd;
    int fd_o;
    if(argc != 2)	// Si no se le pasa un nombre de archivo, se usará la estándar (fd=0).
        fd=0;
    else{
        if( (fd=open(argv[1],O_CREAT|O_RDONLY,S_IRUSR|S_IWUSR))<0) {	// Si se le pasa un nombre de archivo, se leerá ese archivo.
            printf("\nError %d en open",errno);
            perror("\nError en open");
            exit(-1);
            }
    }


    if( (fd_o=open("salida.txt",O_CREAT|O_WRONLY,S_IRUSR|S_IWUSR))<0) {	// Abrimos el fichero de salida.
        printf("\nError %d en open",errno);
        perror("\nError en open");
        exit(-1);
        }

    struct stat atributos;	// Cargamos los atributos del archivo.
    if(lstat(argv[1],&atributos)<0)
        printf("lstat error\n");
    
    long long int n = atributos.st_size/80;

    char buf[]="El número de bloques es";
    dprintf(fd_o,"%s : %lld", buf,n );	// Escribimos un número en el archivo mediante 'dprintf'.	

    int i=0;	
    char buff[]="\nBloque";
    while(read(fd, bufn,80) != 0) {
        dprintf(fd_o,"%s : %d %s", buff,i++, "\n");
        if(write(fd_o,bufn,80) != 80) {
            perror("\nError en write");
            exit(-1);
            }

        }
    close(fd);
    close(fd_o);
    return 0;


}
