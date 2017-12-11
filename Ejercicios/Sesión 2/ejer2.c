/*
Realiza un programa en C utilizando las llamadas al sistema necesarias que acepte
como entrada:
	• Un argumento que representa el 'pathname' de un directorio.
	• Otro argumento que es un número octal de 4 dígitos.
El programa tiene que usar el número octal indicado en el segundo argumento para cambiar los
permisos de todos los archivos que se encuentren en el directorio indicado en el primer
argumento.
El programa debe proporcionar en la salida estándar una línea para cada archivo del directorio
que esté formada por:
<nombre_de_archivo> : <permisos_antiguos> <permisos_nuevos>
Si no se pueden cambiar los permisos de un determinado archivo se debe especificar la siguiente
información en la línea de salida:
<nombre_de_archivo> : <errno> <permisos_antiguos>
*/

#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<dirent.h>

int main(int argc, char *argv[])
{

if( argc != 3 ){
	printf("\nSintaxis incorrecta\n\n");
	exit(-1);
}


//Declaramos las variables necesarias.
DIR * dirp;
struct dirent * direntp;
//Abrimos el directorio.
dirp=opendir(argv[1]);
if( dirp==NULL ){
	printf("Error: no se pudo abrir el directorio.\n");
	exit(-1);
}

char * endptr;

mode_t mask=strtol(argv[2], &endptr, 8);
mode_t old_mask;

struct stat atributos;

//Leemos las entradas del directorio.

while( (direntp=readdir(dirp)) != NULL){

    if(stat(direntp->d_name,&atributos) < 0) {
        printf("\nError al intentar acceder a los atributos de %s\n", direntp->d_name);
        perror("\nError en stat\n");
        exit(-1);
    }
	old_mask=atributos.st_mode;

	//printf("%s\n", direntp->d_name);
	if( (chmod(direntp->d_name, atributos.st_mode, mask)) < 0 )
		printf("\n%s: %d %d %s", direntp->d_name, errno, old_mask, "error");
	else
		printf("\n%s: %d %d", direntp->d_name, old_mask, atributos.st_mode); 
}
closedir(dirp);
}
