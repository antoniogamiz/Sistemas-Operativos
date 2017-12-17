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