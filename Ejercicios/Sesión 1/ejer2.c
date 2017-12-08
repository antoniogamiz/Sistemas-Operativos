#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>

char bufn[80];


int main(int argc, char *argv[]){
    int fd;
    int fd_o;
    if(argc != 2)
        fd=0;
    else{
        if( (fd=open(argv[1],O_CREAT|O_RDONLY,S_IRUSR|S_IWUSR))<0) {
            printf("\nError %d en open",errno);
            perror("\nError en open");
            exit(-1);
            }
    }


    if( (fd_o=open("salida.txt",O_CREAT|O_WRONLY,S_IRUSR|S_IWUSR))<0) {
        printf("\nError %d en open",errno);
        perror("\nError en open");
        exit(-1);
        }

    struct stat atributos;
    if(lstat(argv[1],&atributos)<0)
        printf("lstat error\n");
    
    long long int n = atributos.st_size/80;

    char buf[]="El número de bloques es";
    dprintf(fd_o,"%s : %lld", buf,n );

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