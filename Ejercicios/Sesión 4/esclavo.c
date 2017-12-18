#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


#include <math.h> //Necesita gcc -lm

int isPrime(int n){

  int i;
  int prime = 1;
  int bound = sqrt(n);

  if (n <= 1)
    prime = 0;

  if (n > 2 && n%2 == 0)
    prime = 0;
  else if (n == 2)
    prime = 1;

  for (i = 3; i <= bound && prime; i += 2){

    if(n % i == 0){
      prime = 0;
    }
  }

  return prime;

}

int main(int argc, char *argv[]){

  int start, end, i;

  if(argc < 3){
    perror("Error en el número de argumentos");
    exit(-1);
  }
  start = atoi(argv[1]);
  end = atoi(argv[2]);
  
  for (i = start; i < end; i++)
    if (isPrime(i)){
      //printf("%d\n", i);
      write(STDOUT_FILENO, &i, sizeof(int));
    }
  exit(0);
}