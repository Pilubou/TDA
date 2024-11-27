#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX(x,y) ((x)>(y) ? (x) : (y))

#define MIN(x,y) ((x)<(y) ? (x) : (y))

#define OK 1

#define DUPLICADO 2
#define SIN_MEM -1
#define reservarMemoriaNodo(X,Y,Z,W) ( \
                                      ( ( X ) = (typeof( X )) mallox(Y) ) == NULL || ( ( Z ) = malloc(W) ) == NULL ? \ free( X ),0 : 1 )

typedef int (*Cmp)(const void * e1, const void * e2);
typedef void (*Actualizar)(void * datoArbol, const void * datoParam);
typedef void (*Accion)(void * dato, void * datoAccion);

typedef struct sNodoArbol
{
    void * dato;
    unsigned tamDato;
    struct sNodoArbol *izq,
                  *der;
}NodoA;

typedef NodoA *tArbol;

void CrearArbol(tArbol * pa);

int buscarEnArbol(const tArbol * pa, void * dato, size_t tamDato, Cmp cmp);

int insertarEnArbol(tArbol * pa, void * dato, size_t tamDato, Cmp cmp);

int insertarEnArbolRec(tArbol * pa, void * dato, size_t tamDato, Cmp cmp);

int insertarOActualizarEnArbol(tArbol * pa, void * dato, size_t tamDato, Cmp cmp, Actualizar actualiza);

int cantNodosArbol (const tArbol *pa);

int alturaArbol(const tArbol *pa);

void recorrerEnPreOrden(tArbol *pa, void * params, void (*accion) (void *, unsigned, void *) );

void recorrerEnPosOrden(tArbol *pa, void * params, void (*accion) (void *, unsigned, void *) );

void recorrerEnOrden(tArbol *pa, void * params, void (*accion) (void *, unsigned, void *) );

void vaciarArbol(tArbol *pa);

int EsHoja(tArbol *pa);

NodoA ** mayorNodoArbol (const tArbol * pa);
NodoA ** menorNodoArbol (const tArbol *pa);

#endif // ARBOL_H_INCLUDED
