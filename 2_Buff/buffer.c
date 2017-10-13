#include<stdio.h>
#include<stdlib.h>

#define N 3

struct TQueue{
    char buffer[];
    int summit;
}

struct TQueue buffer;

bool push (struct TQueue *b, usingned char c)
{
    if (b->summit >= N)
        return false;

    b->buffer[b->summit++] = c;
    return true;
}

bool pop (struct TQueue *b, usigned char c)
{
    if (b->summit >= N)
        return false;
    b->buffer[b->summit++] = c;

}

void imprime(struct TQueue *b){
    for(int i=0; i<7;i++){
        
    }
}



int main(int argc, char *argv[]){


    return EXIT_SUCCESS;
}
