# Sistemas Operativos (II)
#### Descriptores de archivo
```
fd=0 => entrada estándar de un proceso.
fd=1 => salida estándar de un proceso.
fd=2 => salida de error estándar de un proceso.
```
#### Funcion 'open'
```
int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);

fd=open("archivo", O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR);
close(fd);
```
* Return: a file descriptor. If 'open' fails, it returns -1.
* Flags:
	* O_RDONLY : read only.
	* O_WRONLY: write only.
	* ORDWR: read and write.
	* O_CREAT: if the file does not exist, it will be created.
	* S_IRUSR: 00400 user has read permission.
	* S_IWUSR: 00200 user has write permission.
#### Función 'close'
```
int close(int fd);
```
* Description: *close()* closes a file descriptor, so that it no longer refers to any file and may be reused.
* Return: *close()* returns a zero on success. On error, -1 is returned and *errno* is set appropriately.
#### Función 'read'
```
ssize_t read(int fd, void *buf, size_t count);
```
* Description: read() attempts to read up to *count* bytes from file descriptor *fd* into the buffer starting at *buf*.
* Return: on success. the number of bytes read is returned (zero indicates end of file), and the file position is advanced by this number. On error, -1 is returned, and *errno* is set appropriately. 
#### Función 'write'
```
ssize_t write(int fd, const void *buf, size_t count);
```
* Description: write() writes up to *count* bytes from the buffer pointed *buf* to the file referred to by the file descriptor *fd*.
* Return: On succes, the number of bytes written is returned (zero indicates nothing was written). If -1 is returned, and *errno* is set appropriately.
#### Función 'lseek'
```
off_t lseek(int fd, off_t offset, int whence);
```
* Description: the *lseek* function repositions the offset of the open file associated with the file descriptor *fd* to the argument *offset* according to the directive *whence* as follows:
	* SEEK_SET: the offset is set to *offset* bytes.
	* SEEK_CUR: the offset is set to its current location plus *offset* bytes.
	* SEEK_END: the offset is set to the size of the file plus *offset* bytes.

#### Función 'dprintf'
`dprintf(int fd, const char * formato, varibales);`

#### structure stat

~~~C
struct stat {
dev_t st_dev; /* no de dispositivo (filesystem) */
dev_t st_rdev; /* no de dispositivo para archivos especiales */
ino_t st_ino; /* no de inodo */
mode_t st_mode; /* tipo de archivo y mode (permisos) */
nlink_t st_nlink; /* número de enlaces duros (hard) */
uid_t st_uid; /* UID del usuario propietario (owner) */
gid_t st_gid; /* GID del usuario propietario (owner) */
off_t st_size; /* tamaño total en bytes para archivos regulares */
unsigned long st_blksize; /* tamaño bloque E/S para el sistema de archivos*/
unsigned long st_blocks; /* número de bloques asignados */
time_t st_atime; /* hora último acceso */
time_t st_mtime; /* hora última modificación */
time_t st_ctime; /* hora último cambio */
};
~~~

#### Macros POSIX para comprobar el tipo del fichero.

~~~
S_ISLNK(st_mode) Verdadero si es un enlace simbólico (soft)
S_ISREG(st_mode) Verdadero si es un archivo regular
S_ISDIR(st_mode) Verdadero si es un directorio
S_ISCHR(st_mode) Verdadero si es un dispositivo de caracteres
S_ISBLK(st_mode) Verdadero si es un dispositivo de bloques
S_ISFIFO(st_mode) Verdadero si es una cauce con nombre (FIFO)
S_ISSOCK(st_mode) Verdadero si es un socket
~~~

#### Definición de macros en C

~~~
#define identifier token-stringopc
#define identifier( identifieropc, ... , identifieropc ) ( token-stringopc )
~~~
#### Función 'umask'
`mode_t umask(mode_t mask)`

* Description: `umask()` sets the calling process's file mode creation mask (umask) to `mask & 077`.
* Returns: this system call always succeeds and the previous value of the mask is returned.
* Nota: El argumento de la llamada puede formarse mediante una combinación OR de las nueve constantes de permisos (rwx para ugo).

#### Funciones 'chmod' y 'fchmod'

`int chmod(const char *path, mode_t mode); #Para un archivo cuyo pathname sea path.`
`int fchmod(int fildes, mode_t mode); #Para archivos abiertos con open.`
* Return: En caso de éxito, devuelve 0. En caso de error, -1 y se asigna a la variable errno un valor adecuado.

| mode_t mode| mask | Descripción|
|:-----:|:----:|:----------------------|
|S_ISUID| 04000 |activar la asignación del UID del propietario al UID efectivo del proceso que ejecute el archivo.|
|S_ISGID |02000| activar la asignación del GID del propietario al GID efectivo del proceso que ejecute el archivo.|
|S_ISVTX |01000| activar sticky bit. En directorios significa un borrado restringido, es decir, un proceso no privilegiado no puede borrar o renombrar archivos del directorio salvo que tenga permiso de escritura y sea propietario. Por ejemplo se utiliza en el directorio /tmp.
|S_IRWXU |00700| user (propietario del archivo) tiene permisos de lectura, escritura y ejecución|
|S_IRUSR |00400 |lectura para el propietario (= S_IREAD no POSIX)|
|S_IWUSR| 00200| escritura para el propietario (= S_IWRITE no POSIX)|
|S_IXUSR |00100| ejecución/búsqueda para el propietario (=S_IEXEC no POSIX)|
|S_IRWXG |00070| group tiene permisos de lectura, escritura y ejecución|
|S_IRGRP |00040 |lectura para el grupo|
|S_IWGRP |00020| escritura para el grupo|
|S_IXGRP |00010 |ejecución/búsqueda para el grupo|
|S_IRWXO |00007| other tienen permisos de lectura, escritura y ejecución|
|S_IROTH |00004 |lectura para otros|
|S_IWOTH |00002| escritura para otros|
|S_IXOTH |00001 |ejecución/búsqueda para otros|



#### Funciones de manejo de directorios.

* opendir: se le pasa el pathname del directorio a abrir, y devuelve un puntero a la estructura de
tipo DIR, llamada stream de directorio. El tipo DIR está definido en <dirent.h>.
* readdir: lee la entrada donde esté situado el puntero de lectura de un directorio ya abierto cuyo stream se pasa a la función. Después de la lectura adelanta el puntero una posición. Devuelve la entrada leída a través de un puntero a una estructura (struct dirent), o devuelve NULL si llega al final del directorio o se produce un error.
* closedir: cierra un directorio, devolviendo 0 si tiene éxito, en caso contrario devuelve -1.
* seekdir: permite situar el puntero de lectura de un directorio (se tiene que usar en combinación con telldir).
* telldir: devuelve la posición del puntero de lectura de un directorio.
* rewinddir: posiciona el puntero de lectura al principio del directorio.

Declaraciones: 
~~~~~
DIR *opendir(char *dirname)
DIR *opendir(int fd)
struct dirent *readdir(DIR *dirp)
int closedir(DIR *dirp)
void seekdir(DIR *dirp, log loc)
long telldir(DIR *dirp)
void rewinddir(DIR *dirp)

typedef struct _dirdesc {
	int dd_fd;
	long dd_loc;
	long dd_size;
	long dd_bbase;
	long dd_entno;
	long dd_bsize;
	char *dd_buf;
} DIR;
//La estructura struct dirent conforme a POSIX 2.1 es la siguiente:
#include <sys/types.h>
#include <dirent.h>
struct dirent {
	long d_ino; /* número i-nodo */
	char d_name[256]; /* nombre del archivo */
	off_t          d_off;       /* offset to the next dirent */
	unsigned short d_reclen;    /* length of this record */
	unsigned char  d_type;      /* type of file; not supported
};
~~~~~

###### Orden nftw

`int nftw (const char *dirpath, int (*func) (const char *pathname, const struct stat *statbuf, int typeflag, struct FTW *ftwbuf), int nopenfd, int flags);`

|flag|Descripción|
|:--------:|:----------------------|
|FTW_DIR |Realiza un chdir (cambia de directorio) en cada directorio antes de procesar sucontenido. Se utiliza cuando func debe realizar algún trabajo en el directorio en el que el archivo especificado por su argumento pathname reside.|
|FTW_DEPTH |Realiza un recorrido postorden del árbol. Esto significa que nftw llama a func sobre todos los archivos (y subdirectorios) dentro del directorio antes de ejecutar func sobre el propio directorio.|
|FTW_MOUNT| No cruza un punto de montaje.|
|FTW_PHYS|Indica a nftw que nos desreferencie los enlaces simbólicos. En su lugar, un enlace simbólico se pasa a func como un valor typedflag de FTW_SL.|

|typeflag|Descripción|
|:--------:|:----------------------|
|FTW_D |Es un directorio|
|FTW_DNR |Es un directorio que no puede leerse (no se lee sus descendientes).|
|FTW_DP |Estamos haciendo un recorrido posorden de un directorio, y el ítem actual es un directorio cuyos archivos y subdirectorios han sido recorridos.|
|FTW_F |Es un archivo de cualquier tipo diferente de un directorio o enlace simbólico.|
|FTW_NS |stat ha fallado sobre este archivo, probablemente debido a restricciones de permisos. El valor statbuf es indefinido.|
|FTW_SL |Es un enlace simbólico. Este valor se retorno solo si nftw se invoca con FTW_PHYS|
|FTW_SLN |El ítem es un enlace simbólico perdido. Este se da cuando no se especifica FTW_PHYS.|

~~~
struct FTW {
	int base; /* Desplazamiento de la parte base del pathname */
	int level; /*Profundidad del archivo dentro recorrido del arbol */
};
~~~

### Sesión III (Control de procesos)

##### LLamadas que devuelven identificadores

~~~
#include <unistd.h>
#include <sys/types.h>
pid_t getpid(void); // devuelve el PID del proceso que la invoca.
pid_t getppid(void); // devuelve el PID del proceso padre del proceso que la invoca.
uid_t getuid(void); // devuelve el identificador de usuario real del proceso que la invoca.
uid_t geteuid(void); // devuelve el identificador de usuario efectivo del proceso que la invoca.
gid_t getgid(void); // devuelve el identificador de grupo real del proceso que la invoca.
gid_t getegid(void); // devuelve el identificador de grupo efectivo delproceso que la invoca.
~~~
##### fork()

`pid_t fork(void);`

* Return: 0 si es el hijo quien ejecuta, pid si es el padre.


##### Unbuffered stdout

~~~
if(setvbuf(stdout,NULL,_IONBF,0)) {
	perror("\nError en setvbuf");
}
~~~



















