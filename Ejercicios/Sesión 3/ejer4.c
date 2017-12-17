#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include <unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>	//Cabeceras para poder usar el tipo booleano
#include <sys/wait.h>


int main(int argc, char *argv[]) {
	
	const int NUM_HIJOS = 5;

	pid_t pid[NUM_HIJOS];

	//En un principio lo había resuelto con una funcion recursiva con un contador como parametro
	//pero creo que el ejercicio no pedía tanta complicación
	switch (pid[0] =fork()){

		case 0: //Hijo
			printf("Soy el hijo %d\n", getpid());
			break;
		default: //Padre
			switch (pid[1] =fork()){

				case 0: //Hijo
					printf("Soy el hijo %d\n", getpid());
					break;
				default: //Padre
					switch (pid[2] =fork()){

						case 0: //Hijo
							printf("Soy el hijo %d\n", getpid());
							break;
						default: //Padre
							switch (pid[3] =fork()){

								case 0: //Hijo
									printf("Soy el hijo %d\n", getpid());
									break;
								default: //Padre
									switch (pid[4] =fork()){

										case 0: //Hijo
											printf("Soy el hijo %d\n", getpid());
											break;
									} 
									break;
							} 
							break;

					}
					break; 
			} 
			break;

	}



	//Esperamos a que se cierren
	for (int i = 0;i<NUM_HIJOS;i++) {

		if (waitpid(pid[i],0,0) > 0) {                  

	    	printf("Acaba de finalizar mi hijo con PID:%d\n",pid[i]);
	    	printf("Solo me quedan %d hijos vivos\n",NUM_HIJOS - i);
      
    	}
	}

		
	exit(0);

}