#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include "libreria.h"

#define N 0x100

//getPid del padre
//crear una variable para la cantidad de hijos

//hacer el fget
//fgets(command, sizeof(command), stdin)
//fgets(buffer[N], sizeof(buffer), stdin);
//poner el getc sino no va
const char *coge = (const char*) getc(stdin); //va raro

int total_childs = 0;

//señal handler
sig_atomic_t sigusr1_count = 0;

void handler(int signal_number)
{
    ++sigusr1_count;
}

//leer
char *leerArchivo(const char* nombre, size_t length)
{
    char* buffer;
    int archivo;
    ssize_t bytes_leidos;

    buffer = (char*) malloc(length);

    if(buffer == NULL)
        return NULL;

    //para abrir el fichero

    archivo = open(nombre, O_RDONLY);
    if(archivo == -1){
        free(buffer);
        return NULL;
    }
    //datos que leer
    bytes_leidos = read(archivo, buffer, length);
    if(bytes_leidos != length) {
        //lecura fallida
        free(buffer);
        close(archivo);
        return NULL;
    }

    //si todo esta correcto
    close(archivo);
    return buffer;
}

//crear una funcion que vaya poniendo hijos
void spawn(int child){
    //char argv[];
    total_childs++; //añadimos el sguiente hijo
    pid_t child_pid;
    child_pid = fork();

        if(child)
            return;
        else
           leerArchivo(coge, N); //llamo a la funcion que hemos creado antes
           // execv(argv[0], argv);
           // -Se tiene que guardar en buffer para luego sacarlo

}
//matar hijos
void undertaker(int señal){
    int estado_hijos;
    wait(&estado_hijos);
    total_childs--; //acabamos con un hijo
}


int main(int argc, char *argv[]){

     struct sigaction sa;
     memset (&sa, 0, sizeof(sa));
     sa.sa_handler = &handler;
     sigaction(SIGUSR1, &sa, NULL);

     //char argv[M];

     char buffer[N];
//ponemos 0 de tamaño de sa
    // fgets(buffer[N], buffer);

   /*  printf("Que quieres:");
     scanf("%i", &buffer);
*/
     spawn(buffer[N]);


    return EXIT_SUCCESS;
    }
