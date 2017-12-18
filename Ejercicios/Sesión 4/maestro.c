#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
  int fd1[2];
  int fd2[2];
  
  int bytes1, bytes2, prim1, prim2;
  pid_t es1 = -1, es2 = -1; //Slaves
  int start, end; //Intervals provided by user
  int te1, be2; //Top and bottom interval points for slavesx

  //execl needs char and not int in the call
  char top[10];
  char bot[10];


  //Check args provided
  if(argc < 3){
    perror("Error en el número de argumentos");
    exit(-1);
  }

  // Set the intervals bounds
  start = atoi(argv[1]);
  end = atoi(argv[2]);
  te1 = (start+end)/2 -1;
  be2 = te1 +1;

  //Create the pipes

  pipe(fd1);
  pipe(fd2);
  
  //Make the fork for the first child
  if((es1 = fork()) < 0){
    perror("Error al hacer fork del primer esclavo");
    exit(-1);
  }


  //Slave number 1
  if(es1 == 0){
    //We close the read channel
    close(fd1[0]);
    dup2(fd1[1], STDOUT_FILENO);

    //This way we convert int to char[]
    //itoa is not a standart
    snprintf( top, sizeof(int), "%d", te1 );
    
    if(execl("./esclavo", "esclavo", argv[1], top, NULL) < 0){
      perror("Error en la llamada a slave 1");
      exit(-1);
    };
  }else{

    //Close the write for the pipe with es1
    close(fd1[1]);
    

    while(bytes1 = read(fd1[0], &prim1, sizeof(int)) > 0){
      printf("%d\n", prim1);
    }
    
    printf("--------------\n");
    
  }


  //Slave number 2
  if((es2 = fork()) < 0){
    perror("Error al hacer fork del segundo esclavo");
    exit(-1);
  }
      
  if (es2 == 0){

    close(fd2[0]);
    dup2(fd2[1], STDOUT_FILENO);
    snprintf( bot, sizeof(int), "%d", be2 );
    
    if(execl("./esclavo", "esclavo", bot, argv[2], NULL) < 0){
      perror("Error en la llamada a slave 1");
      exit(-1);
    };
    
  }else{

    close(fd2[1]);
    while(bytes1 = read(fd2[0], &prim2, sizeof(int)) > 0){
      printf("%d\n", prim2);
    }
    
  }

}