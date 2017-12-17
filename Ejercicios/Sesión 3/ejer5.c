#include <sys/types.h>
#include <unistd.h>		
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	
	const int NUM_HIJOS = 5;
	pid_t pid[NUM_HIJOS];

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

	//Esperamos a que se cierren primero los impares
	for (int i = 0;i<NUM_HIJOS;i = i + 2) {
		if (waitpid(pid[i],0,0) > 0) {                  
	    	printf("Acaba de finalizar mi hijo con PID:%d\n",pid[i]);
	    	printf("Solo me quedan %d hijos vivos\n",NUM_HIJOS - i);
    	}
	}
	//Esperamos a que se cierren despues los pares
	for (int i = 1;i<NUM_HIJOS;i = i + 2) {
		if (waitpid(pid[i],0,0) > 0) {                  
	    	printf("Acaba de finalizar mi hijo con PID:%d\n",pid[i]);
	    	printf("Solo me quedan %d hijos vivos\n",NUM_HIJOS - i);
    	}
	}
		
	exit(0);

}