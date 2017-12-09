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

if( argc != 2 ){
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


struct stat atributos;

//Leemos las entradas del directorio.

long long int sum=0;
int n=0;
printf("Los i-nodos son: \n");
while( (direntp=readdir(dirp)) != NULL){
	//Cargamos el stat de cada archivo del directorio.
	if(stat(direntp->d_name,&atributos) < 0) {
		printf("\nError al intentar acceder a los atributos de %s", direntp->d_name);
		perror("\nError en stat");
		exit(-1);
	}

	if( atributos.st_mode & S_IXOTH ){
		if( atributos.st_mode & S_IXGRP ){
			printf("%s : %lld\n",direntp->d_name,direntp->d_ino);
			sum+=atributos.st_size;
			n+=1;	
		}	
	}
}
printf("Existen %d archivos regulares con permiso x para grupo y otros\n",n);
printf("El tamaño total ocupado por dichos archivos es %lld bytes\n", sum);


closedir(dirp);
}
