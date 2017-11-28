#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#define NOMASOPC -1
#define INVALOPC '?' //solamente es para que el switch quede mas limpio
#define USAGE //todo lo que podemos meter en la parte del fprintf donde hemos puesto el usage
    "%s -v1.0\n"\
    "Sends an email to a file. \n\n"\
    "USAGE: \n" \
    "%s -d<domain> [-p<port|port name>=smtp] <email file> \n" \
    "EXAMPLE:\n" \
    "%s -d sharklaers.com -p"
#define N 0x100 //veces
#define mailmando "cat %s | telnet %s %s"

const char *program_name; //esto se hace para que el programa quede mas limpio

void
print_usage (FILE *out, int status) //el FILE *out es el tubo por el que quiero que me lo pase
{
    fprintf ( out, USAGE(program_name )); //en este apartado vamos a hacer un "patron" para que la cadena siga un orden y se haga bien
    exit(status);
}


int
main(int argc, char *argv[]){

    char mailmando[N]; //esto es lo que voy a querer mandar, los %s se ponen para que no tengamos que mandar siempre el mismo mensaje y pueda mandarse lo que quieras

    //vamos a usar getopt por eso debemos de declarar las opciones cortas y las opciones largar que es lo que se hace a continuacion
    const char *servidor = NULL;
    int sig_opcion;
    char puerto[N] = "smtp" //esto solo es por si quieres poner el puerto

    int verbose = 0; //para la opcion que hemos metido luego de verbose
    const char *op_cortas = "hd:p:v";

    const struct option *op_largas[] = {
               {"help", 0, NULL, 'h'},
               {"domain", 1, NULL, 'd'},
               {"port", 1, NULL, 'p'},
               {"verbose", 0, NULL, 'v'}, //metemos el verbose en el menu de opciones largas
               {NULL, 0, NULL, '\0'}
    };

    program_name = argv[0];

    //ahora hay que parsear las opciones
    do{
        sig_opcion = getopt_long(op_cortas, op_largas, argc, argv, NULL); //analiza la linea de comandos y devuelve la opcion

        //en caso de sig_opcion se pueden dar diferenctes opciones
        switch (sig_opcion){
            case 'h':
                print usage(stdout, EXIT_SUCCESS);
                break;
             case 'v': //crear la opcion verbose
                 verbose = 1;
                 break;
            case 'd': //es solamente cuando tiene un argumento mas lo guarda aqui
                servidor = optarg;
                break;
            case 'p':
                strncpy(puerto, optarg, N); //copiaria en puerto el puerto que se ha introducido en caso de que haya sido introducido
                break;
            case '?'
                print usage(stderr, EXIT_FAILURE);
                break;
            case NOMASOPC:
                break;
            default:
                abort();

        }

    }while(sig_opcion);

    //en caso de que no s haya introducido el dominio
    if (servidor == NULL){
        fprintf(stderr, "You have to specify a email server \ n");
        print_usage(stderr, EXIT_SUCCESS);

    }
        if (optind >= argc){
            fprintf(stderr, "You have to specify an email file.\n");
            print_usage(stderr, EXIT_FAILURE);
        }


        sprintf(mailmado, mailmando,
                argv[optind], //va analizando todo lo que empieza por - y te dice lo que hay despues
                servidor,
                puerto);

       if (verbose)
           printf("Command: %s\n", mailmando);

    }

   /* sprintf(mailmando, mailmando, "email.addr", "sharklasers.com", "smtp"); //con el primer mailmando cojo la cena y con el segundo mailmando escribo sobre la cadena mailmando lo que he puesto entre      comillas, cada %s es lo que hay entre comillas
   */

    system (mailmando);

    return EXIT_SUCCESS;
}
