#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

#define S_ISREG2(mode) ( S_ISREG(mode) )

int main(int argc, char *argv[])
{
    struct stat atributos;
    char tipoArchivo[30];
    if(argc!=2) {
    printf("\nSintaxis incorrecta\n\n");
    exit(-1);
    }

    if(lstat(argv[1],&atributos) < 0) {
        printf("\nError al intentar acceder a los atributos de %s",argv[1]);
        perror("\nError en lstat");
        }

    if( S_ISREG2(atributos.st_mode)) printf("El archivo %s es un archivo regular.\n",argv[1]);

}