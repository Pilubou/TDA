#include "Lista_simple.h"

void CrearLista (Lista * pl)
{
    *pl = NULL;
}

int listaVacia(const Lista *pl)
{
    return !*pl;
}

int listaLlena (const Lista *pl, size_t tamElem)
{
    void * Nodo = malloc(sizeof(Nodo));
    void * Dato = malloc(tamElem);
    free(Nodo);
    free(Dato);
    return !Nodo || !Dato;
}

int insertarEnListaOrd(Lista * pl, const void * dato, size_t tamElem, Cmp cmp)
{
    while(*pl && cmp(dato, (*pl)->dato) > 0)
        pl = &(*pl)->sig;

    Nodo * nue = (Nodo *)malloc(sizeof(Nodo));
    void * datoN = malloc(tamElem);
    if(!nue || !datoN)
    {
        free(nue);
        free(datoN);
        return SIN_MEM;
    }

    memcpy(datoN,dato,tamElem);
    nue->dato = datoN;
    nue->tamElem = tamElem;

    nue->sig = *pl;
    *pl = nue;
    return TODO_OK;
}

int eliminarListaDesordPorValor (Lista *pl, void *dato, size_t tamDato, Cmp cmp)
{
    int comp;
    while(*pl && (comp = cmp(dato,(*pl)->dato) ) != 0)
        pl = &(*pl)->sig;
    if(!*pl)
        return 0;

    Nodo * nae = *pl;
    *pl = nae->sig;
    memcpy(dato,nae->dato,MIN(tamDato,nae->tamElem));
    free(nae->dato);
    free(nae);
    return TODO_OK;

}

int eliminarListaOrdPorValor (Lista *pl, void *dato, size_t tamDato, Cmp cmp)
{
    int comp;
    while(*pl && (comp = cmp(dato,(*pl)->dato)) > 0)
        pl = &(*pl)->sig;
    if(!*pl || comp < 0 )
        return 0;

    Nodo * nae = *pl;
    *pl = nae->sig;
    memcpy(dato,nae->dato,MIN(tamDato,nae->tamElem));
    free(nae->dato);
    free(nae);
    return TODO_OK;
}
int insertarPrimeroEnLista(Lista *pl, void * dato, size_t tamDato)
{
    Nodo * nodo = (Nodo *)malloc(sizeof(Nodo));
    void * datoN = malloc(tamDato);
    if(!nodo || !datoN)
    {
        free(nodo);
        free(datoN);
        return SIN_MEM;
    }
    nodo->tamElem = tamDato;
    memcpy(datoN,dato,tamDato);
    nodo->dato = datoN;
    nodo->sig = *pl;
    *pl = nodo;
    return TODO_OK;
}
int MapLista(Lista *pl, Accion accion)
{
    while(*pl)
    {
        accion((*pl)->dato);
        pl = &(*pl)->sig;
    }
    return TODO_OK;
}
void VaciarLista(Lista *pl)
{
    Nodo * nae;
    while(*pl)
    {
        nae = *pl;
        *pl = nae->sig;
        free(nae->dato);
        free(nae);
    }
    *pl = NULL;
}
int eliminarDeListaOrdDuplicados(Lista * pl, Cmp cmp, Actualizar actualizar)
{
   Lista * pl2;
   Nodo * nae;
   int cantElim = 0;
   while(*pl)
   {
       pl2 = &(*pl)->sig;

       while(*pl2 && cmp((*pl)->dato,(*pl2)->dato) == 0 ) ///Corte de control, mientras pl2 no sea null y el anterior (*pl) y (*pl2) sean iguales.
       {
           actualizar((*pl)->dato,(*pl2)->dato);
           nae = *pl2; ///Borramos el nodo apuntado por *pl2
           *pl2 = nae->sig; ///Lo avanzamos.
           free(nae->dato);
           free(nae);
           cantElim++;
       }

   }
   return cantElim;

}
