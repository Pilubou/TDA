#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

#define SIN_MEM -1
#define TODO_OK 1

#define MIN(x,y) ((x)<(y) ? (x) : (y))

typedef struct sNodo
{
    void * dato;
    unsigned tamElem;
    struct sNodo *sig;
}Nodo;


#endif // NODO_H_INCLUDED
