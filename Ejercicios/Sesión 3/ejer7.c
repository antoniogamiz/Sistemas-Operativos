
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/wait.h>

#include <string.h> //strcmp

int main(int args, char *argv[]){

  if (args < 2){
    printf("Error en el número de argumentos\n");
    exit(-1);
  }

  int bg = 0; //false
  char cadena[]  = "bg";
  pid_t PID, pido;
  int estado;

  char **argumentos = argv;
  argumentos++;


  if(strcmp(cadena, argv[args-1]) == 0)
    bg = 1;

  printf("El valor de bg es %d\n", bg);
  
    if (bg){
        if((PID = fork()) < 0){
            perror("Error al hacer fork\n");
        }
        else{ 
            if(PID==0){
            //Proceso hijo
            printf("Ejecutando en background\n");
            argumentos[args-2] = '\0';
            if(execvp(argv[1], argumentos) < 0)
                perror("Error en la ejececución de la instrucción");
            } 
            else exit(0);
            }
    } else{
        printf("Se ejecutara en foreground\n");;
        if(execvp(argv[1], argumentos) < 0)
            perror("Error en la ejecución");
    }
  
}
