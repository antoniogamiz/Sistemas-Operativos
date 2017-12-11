//tarea4.c
//Trabajo con llamadas al sistema del Subsistema de Procesos "POSIX 2.10 compliant"
//Prueba el programa tal y como está. Después, elimina los comentarios (1) y pruebalo de nuevo.

#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

char buf[]=" Ejercicio 1\n";	// Mensaje que aparecerá en pantalla.

int main(int argc, char *argv[])
{
	if(argc != 2){
		printf("Número de paŕametros incorrecto: ./programa <número>\n");
		exit(-1);
	}

	int n = strtol(argv[1], 0, 10);

	pid_t pid;

	if(write(STDOUT_FILENO,buf,sizeof(buf)+1) != sizeof(buf)+1) {	// Escribe un mensaje en la salida estándar.
		perror("\nError en write");
		exit(EXIT_FAILURE);
	}

	if( (pid=fork())<0) {
		perror("\nError en el fork");
		exit(EXIT_FAILURE);
	}
	else if(pid==0) {  
		//proceso hijo ejecutando el programa
		if( n % 2 ){
			printf("El número %d es impar\n", n);		
		} else{
			printf("El número %d es par\n", n);
		}
	} else{  //proceso padre ejecutando el programa
		sleep(1);		
		if( n % 4 ){
			printf("El número %d no es múltiplo de 4\n", n);		
		} else{
			printf("El número %d es múltiplo de 4\n", n);
		}
	}
	exit(EXIT_SUCCESS);

}
