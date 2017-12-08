#Sistemas Operativos (II)
####Descriptores de archivo
```
fd=0 => entrada estándar de un proceso.
fd=1 => salida estándar de un proceso.
fd=2 => salida de error estándar de un proceso.
```
####Funcion 'open'
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
####Función 'close'
```
int close(int fd);
```
* Description: *close()* closes a file descriptor, so that it no longer refers to any file and may be reused.
* Return: *close()* returns a zero on success. On error, -1 is returned and *errno* is set appropriately.
####Función 'read'
```
ssize_t read(int fd, void *buf, size_t count);
```
* Description: read() attempts to read up to *count* bytes from file descriptor *fd* into the buffer starting at *buf*.
* Return: on success. the number of bytes read is returned (zero indicates end of file), and the file position is advanced by this number. On error, -1 is returned, and *errno* is set appropriately. 
####Función 'write'
```
ssize_t write(int fd, const void *buf, size_t count);
```
* Description: write() writes up to *count* bytes from the buffer pointed *buf* to the file referred to by the file descriptor *fd*.
* Return: On succes, the number of bytes written is returned (zero indicates nothing was written). If -1 is returned, and *errno* is set appropriately.
####Función 'lseek'
```
off_t lseek(int fd, off_t offset, int whence);
```
* Description: the *lseek* function repositions the offset of the open file associated with the file descriptor *fd* to the argument *offset* according to the directive *whence* as follows:
	* SEEK_SET: the offset is set to *offset* bytes.
	* SEEK_CUR: the offset is set to its current location plus *offset* bytes.
	* SEEK_END: the offset is set to the size of the file plus *offset* bytes.

####Función 'dprintf'
`dprintf(int fd, const char * formato, varibales);`

####structure stat

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

####Macros POSIX para comprobar el tipo del fichero.

~~~
S_ISLNK(st_mode) Verdadero si es un enlace simbólico (soft)
S_ISREG(st_mode) Verdadero si es un archivo regular
S_ISDIR(st_mode) Verdadero si es un directorio
S_ISCHR(st_mode) Verdadero si es un dispositivo de caracteres
S_ISBLK(st_mode) Verdadero si es un dispositivo de bloques
S_ISFIFO(st_mode) Verdadero si es una cauce con nombre (FIFO)
S_ISSOCK(st_mode) Verdadero si es un socket
~~~

####Definición de macros en C

~~~
#define identifier token-stringopc
#define identifier( identifieropc, ... , identifieropc ) ( token-stringopc )
~~~
####Función 'umask'
`mode_t umask(mode_t mask)`

* Description: `umask()` sets the calling process's file mode creation mask (umask) to `mask & 077`.
* Returns: this system call always succeeds and the previous value of the mask is returned.
* Nota: El argumento de la llamada puede formarse mediante una combinación OR de las nueve constantes de permisos (rwx para ugo).

####Funciones 'chmod' y 'fchmod'

`int chmod(const char *path, mode_t mode); #Para un archivo cuyo pathname sea path.`
`int fchmod(int fildes, mode_t mode); #Para archivos abiertos con open.`
* Return: En caso de éxito, devuelve 0. En caso de error, -1 y se asigna a la variable errno un valor adecuado.



























