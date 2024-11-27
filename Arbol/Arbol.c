#include "Arbol.h"

void CrearArbol(tArbol * pa)
{
    *pa = NULL;
}

int buscarEnArbol(const tArbol * pa, void * dato, size_t tamDato, Cmp cmp)
{
    int comp;
    while(*pa && (comp = cmp(dato,(*pa)->dato)) != 0)
       pa = comp < 0 ? &(*pa)->izq : &(*pa)->der;
    if(!*pa)
        return 0;
    memcpy(dato,(*pa)->dato,MIN(tamDato,(*pa)->tamDato));

    return OK;
}
int insertarEnArbol(tArbol * pa, void * dato, size_t tamDato, Cmp cmp)
{
    int comp;
    while(*pa)
    {
        comp = cmp((*pa)->dato,dato);
        if(comp == 0)
            return DUPLICADO;
        pa = comp > 0 ? &(*pa)->izq : &(*pa)->der;
    }
    NodoA * nue = (NodoA * )malloc(sizeof(NodoA));
    void * datoN = malloc(tamDato);
    if(!nue || !datoN)
    {
        free(nue);
        free(datoN);
        return SIN_MEM;
    }

    memcpy(datoN,dato,tamDato);
    nue->dato = datoN;

    nue->tamDato = tamDato;

    nue->der = nue->izq = NULL;

    *pa = nue; ///Engancho el nuevo nodo.

    return OK;
}
int insertarEnArbolRec(tArbol * pa, void * dato, size_t tamDato, Cmp cmp)
{
    int comp;
    if(*pa)
    {
        if((comp = cmp((*pa)->dato,dato)) > 0)
            return insertarEnArbolRec(&(*pa)->izq,dato,tamDato,cmp);
        if(comp < 0)
            return insertarEnArbolRec(&(*pa)->der,dato,tamDato,cmp);
        return DUPLICADO;
    }
    NodoA * nue = (NodoA *)malloc(sizeof(NodoA));
    void * datoN = malloc(tamDato);
    if(!nue || !datoN)
    {
        free(nue);
        free(datoN);
        return SIN_MEM;
    }

    memcpy(datoN,dato,tamDato);
    nue->dato = datoN;
    nue->tamDato = tamDato;
    nue->izq = nue->der = NULL;
    *pa = nue;

    return OK;

}
int insertarOActualizarEnArbol(tArbol * pa, void * dato, size_t tamDato, Cmp cmp, Actualizar actualiza)
{
    int comp;
    while(*pa)
    {
        comp = cmp((*pa)->dato,dato);
        if(comp == 0)
        {
            actualiza((*pa)->dato,dato);
            return DUPLICADO;
        }
        pa = comp > 0 ? &(*pa)->izq : &(*pa)->der;
    }
    NodoA * nue = (NodoA * )malloc(sizeof(NodoA));
    void * datoN = malloc(tamDato);
    if(!nue || !datoN)
    {
        free(nue);
        free(datoN);
        return SIN_MEM;
    }

    memcpy(datoN,dato,tamDato);
    nue->dato = datoN;

    nue->tamDato = tamDato;

    nue->der = nue->izq = NULL;

    *pa = nue; ///Engancho el nuevo nodo.

    return OK;
}
int cantNodosArbol (const tArbol *pa)
{
    if(!*pa)
        return 0;
    return cantNodosArbol(&(*pa)->izq) + cantNodosArbol(&(*pa)->der) + 1;
}
int alturaArbol(const tArbol *pa)
{
    if(!*pa)
        return 0;
    int hi, hd;
    hi = alturaArbol(&(*pa)->izq);
    hd = alturaArbol(&(*pa)->der);
    return MAX(hi,hd) + 1;
}
void recorrerEnPreOrden(tArbol *pa, void * params, void (*accion) (void *, unsigned, void *) )
{
    if(!*pa)
        return;
    accion((*pa)->dato,(*pa)->tamDato,params);
    recorrerEnPreOrden(&(*pa)->izq,params,accion);
    recorrerEnPreOrden(&(*pa)->der,params,accion);
}
void recorrerEnPosOrden(tArbol *pa, void * params, void (*accion) (void *, unsigned, void *) )
{
    if(!*pa)
        return;
    recorrerEnPosOrden(&(*pa)->izq,params,accion);
    recorrerEnPosOrden(&(*pa)->der,params,accion);
    accion((*pa)->dato,(*pa)->tamDato,params);
}
void recorrerEnOrden(tArbol *pa, void * params, void (*accion) (void *, unsigned, void *) )
{
   if(!*pa)
        return;
    recorrerEnOrden(&(*pa)->izq, params, accion);
    accion((*pa)->dato, (*pa)->tamDato, params);
    recorrerEnOrden(&(*pa)->der, params, accion);
}

void vaciarArbol(tArbol *pa)
{
    if(!*pa)
        return;

    vaciarArbol(&(*pa)->izq);
    vaciarArbol(&(*pa)->der);

    free((*pa)->dato);
    free(*pa);

    *pa = NULL;
}

int EsHoja(tArbol *pa)
{
    return !(*pa)->izq && !(*pa)->der;
}
NodoA ** mayorNodoArbol (const tArbol * pa)
{
    if(!*pa)
        return NULL;
    while(*pa)
        pa = &(*pa)->der;
    return (NodoA **)pa;
}
NodoA ** menorNodoArbol (const tArbol * pa)
{
    if(!*pa)
        return NULL;
    while(*pa)
        pa = &(*pa)->izq;
    return (NodoA **)pa;
}

int eliminarRaizDeArbol (tArbol *pa, void * dato,size_t tamDato, Cmp cmp)
{
    NodoA ** remp;
    NodoA * elim;
    int hi, hd;
    if(!*pa)
        return 0; ///Si el árbol esta vacío, no hay nada que hacer.
    free((*pa)->dato); ///Libero el espacio asignado al dato de la raíz.
    if(EsHoja(pa)) ///Si es hoja, libero el espacio para el nodo de la raíz directamente y le asigno NULL al puntero del árbol.
    {
        free(*pa);
        *pa = NULL;
        return OK;
    }
    hi = alturaArbol(&(*pa)->izq);
    hd = alturaArbol(&(*pa)->der);
    remp = hi > hd ? mayorNodoArbol(&(*pa)->izq) : menorNodoArbol(&(*pa)->der);
    ///Encuentro el reemplazante según que rama tiene mayor altura.
    elim = *remp; ///El nodo que reemplazará a la raíz será eliminado, por lo que se lo asigno a un puntero nodo aparte.
    (*pa)->dato = elim->dato; ///La raíz toma el valor del nodo a eliminar.
    (*pa)->tamDato = elim->tamDato; ///La raíz toma el tamaño del nodo a eliminar.

    *remp = elim->izq ? elim->izq : elim->der; ///Conecto el puntero desde el nodo anterior al que elimine con su hijo izquierdo o derecho.
    free(elim); ///Libero la memoria del nodo.

    return OK;

}
