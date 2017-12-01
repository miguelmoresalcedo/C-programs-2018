#include <stdio.h>
#include <stdlib.h>

#ifdef __libreria_h__
#define __libreria_h__
#ifdef __cplusplus
extern "C"
{

#endif

//hay que hacer una funcion escribir en la que le pase al buffer lo que quiero;

//enviar(char);

    void salida(char *buffer){
        //lo del buffer

        //printf("Que quiere introducir:");
        scanf("%c", &buffer);


    }



#ifdef __cplusplus

}

#endif
#endif

