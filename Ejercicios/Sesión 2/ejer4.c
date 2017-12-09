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
#include <ftw.h>

long long int sum=0;
int n=0;


int visitar(const char* path, const struct stat* stat, int flags, struct FTW* ftw) 
{
	if( stat->st_mode & S_IXOTH ){
		if( stat->st_mode & S_IXGRP ){
			printf("Path: %s : %lld\n",path, stat->st_ino);
			sum+=stat->st_size;
			n+=1;
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{

if (nftw(argc >= 2 ? argv[1] : ".", visitar, 10, 0) != 0) {
	perror("nftw");
}

printf("Existen %d archivos regulares con permiso x para grupo y otros\n",n);
printf("El tamaño total ocupado por dichos archivos es %lld bytes\n", sum);



}
