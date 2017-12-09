#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
int main(int argc, char *argv[])
{
    int fd1,fd2;
    struct stat atributos;
    //CREACION DE ARCHIVOS
    if( (fd1=open("archivo1",O_CREAT|O_TRUNC|O_WRONLY,S_IRGRP|S_IWGRP|S_IXGRP))<0)
        {
        printf("\nError %d en open(archivo1,...)",errno);
        perror("\nError en open");
        exit(-1);
        }
    
    umask(0);

    if( (fd2=open("archivo2",O_CREAT|O_TRUNC|O_WRONLY,S_IRGRP|S_IWGRP|S_IXGRP))<0)
    {
        printf("\nError %d en open(archivo2,...)",errno);
        perror("\nError en open");
        exit(-1);
    }
    //CAMBIO DE PERMISOS
    if(stat("archivo1",&atributos) < 0) {
        printf("\nError al intentar acceder a los atributos de archivo1");
        perror("\nError en lstat");
        exit(-1);
    }
    if(chmod("archivo1", (atributos.st_mode & ~S_IXGRP) | S_ISGID) < 0) {
        perror("\nError en chmod para archivo1");
        exit(-1);
    }
    if(chmod("archivo2",S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH) < 0) {
        perror("\nError en chmod para archivo2");
        exit(-1);
    }
    
    close(fd1);
    close(fd2);
    return 0;
}