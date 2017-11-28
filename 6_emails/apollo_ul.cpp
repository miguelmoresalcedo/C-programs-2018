#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

#define M 0x100
#define N 0x10

sig_atomic_t hijos = 0;

char const * const comando[] = { //lo que hay aqui no puede cambiarse eso es por el const, es un puntero fijo a una constante, estoy apuntando a un sitio que apunte donde apunte no voy a poder cambiar
        "./mail -vdsharklasers.com email.addr", //es una array de comandos, apunto a esto yy no lo puedo modificar
            NULL
};

void
spawn(char const * lp)
{
     int i = 0;
     char *argv[N];
     char str[M];
     char *p_str = str;

     pid_t tengo_hijo = fork();

     if (tengo_hijo){
         hijos++;

         return;

     }

        bzero(argv, sizeof(argv));
        strncpy(str, lp, M);

        //     . / j m \0 p d t \0
        while ( (argv[i++] = strtok(p_str, " "))  ) //cojo la primera posicion de memoria, y cortame la cadena p_str desde donde empieza el espacio y me guarda en el argv la direccion del ., e i ya vale 1
               p_str = NULL; //lo pone a null para que siga, sigue leyendo una vez ha guardado en argv[0] esa direccion del . y lee hasta el siguiente espacio, y guarda esa palabra siguiente en argv[1] una vez termina devuelve un null

               execvp(argv[0], argv); //aqui es donde se va metiendo la primera direccion argv[0] y la segunda direccion argv[1]
               fprintf(stderr, "We couldn't run %s.\n", argv[0]);
}

void
undertaker(int ruisignal) //aqui quiero recibir una señal
{
    hijos--;
    wait(&estado_de_salida); //se corresponde con el return del main, hay que hacerle un wait para que termine, espera a que termine 1 cualquiera de los programas hijos, recoge su valor de retorno lim        pia la memoria,pilla el return

    //no puedo hacer un wait sin saber que un hijo a muerto por ello hay que recoger una señal sig_child
    if(WIFEXITED(estado_de_salida)) //si entra en el if es que la muerte ha sido normal sino no ha sido natural, la macro ve si hemos terminado bien o no, lo hace solo
        printf("Muerte natural: %i", WIXITSTATUS(estado_de_salida));//quiero sacar lo que hay en estado_de_salida y se hace asi
      else
        printf("Muerte desnatada")


}

int
main(int argc, char *argv[])
{
    int estado_de_salida;
    //si hay una señal sig_child que llame a la funcion undertaker

    struct sigaction como_gestionar; //creamos estrucutra
    bzero(&como_gestionar, sizeof(como_gestionar)); //metemos en la direccion de omo_gestionar tantos ceros como sea el tamaño de como_gestionar
    como_gestionar.sa_hander = &undertaker;
    sigaction(SIG_CHILD,&como_gestionar, NULL);

    for (int i = 0;comando[1] !=NULL; i++){ //solo en caso de tener mas comandos en la array comandos
        comando[i];
    }

    sleep(3);

    while (hijos) usleep(10000); //miestras tenga hijos duerme, u es micro segundos
    printf("The world is a vampire"); //mensaje para cuando he terminado

    spawn(comando[0]); //lanzame comando, lanzo lo de la linea 14



    return EXIT_SUCCESS;
}

