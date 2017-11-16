#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define N 0x100
#define M 0x16 //como mucho que me metan 16 parametros
#define PROMPT “MA-TEOS $>”

void
spawn(char buffer[N]) //creamos una funcion que no devuelve nada
{
    char *argv[M];
    int i = 0;
    pid_t mijo = 0; //es un entero

    while( argv[i++] = strtok(buffer, " ") ) // LO QUE ME DEVUELVA DE buffer separando por  espacios para eso es el strtok =  //aqui es donde guardamos en argv el buffer
    buffer = NULL; //cuando no hay mas palabras mete un null y el while muere


    mijo = fork(); //en mijo guardo el pid del fork             el padre da verdadero por lo que hace otro programa y el hijo como lo tiene NULL da falso y sigue
    // getpid te da el id propio y getppid te da el id del padre

    if (mijo) //el padre da verdadero por lo que hace otro programa y el hijo como lo tiene NULL da falso y sigue
        return;
    //execv("/usr/bin/firefox", ["firefox", "index.html", NULL]) //con el v serviria para para una array
    execv(argv[0], argv); //buffer ya es una array de palabras y con el argv lo estamos cogiendo y al hacer el execv estamos pillando esa array which firefox para saber cual es la direccion de firefox
    fprintf(stderr, "No he podido ejecutar: %s\n", argv[0]); // argv[0]es la direccion de firefox
    exit(1); //termino el programa hij; //termino el programa hijoo
}

int
main(int argc, char *argv[])
{
    char buffer[N];

    while (1)
    {
        printf (PROMPT);
        fgets(buffer, N, stdin);
        spawn (buffer);
    }

    return EXIT_SUCCESS;
}
