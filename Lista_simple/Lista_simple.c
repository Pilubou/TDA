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

    if(*pl && cmp(dato, (*pl)->dato) == 0)
        return DUPLICADO;

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
int insertarEnListaOrdOActualizar(Lista * pl, const void * dato, size_t tamElem, Cmp cmp,Actualizar actualiza, void * params)
{
    int comp;
    while(*pl && (comp = cmp(dato, (*pl)->dato)) > 0)
        pl = &(*pl)->sig;

    if(*pl && comp == 0)
    {
        actualiza((*pl)->dato,dato,params);
        return DUPLICADO;
    }

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
int insertarUltimoEnLista(Lista *pl, void * dato, size_t tamDato)
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
    while(*pl)
        pl = &(*pl)->sig;
    nodo->sig = *pl;
    *pl = nodo;
    return TODO_OK;
}

int insertarUltimoEnListaOActualizar(Lista *pl, void * dato, size_t tamDato,Cmp cmp,Actualizar actualizar, void * params)
{
    int comp;
    while(*pl && (comp = cmp((*pl)->dato,dato)) != 0)
        pl = &(*pl)->sig;

    if(*pl && comp == 0) ///encontré el nodo.
    {
       actualizar((*pl)->dato,dato,params);
       return TODO_OK;
    }
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
int buscarEnListaDesord(Lista *pl, void * dato,unsigned tamDato, Cmp cmp)
{

    while(*pl && cmp(dato,(*pl)->dato)!= 0)
        pl = &(*pl)->sig;

    if(*pl == NULL)
        return 0;

    memcpy(dato,(*pl)->dato,MIN(tamDato,(*pl)->tamElem));
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
int eliminarDeListaOrdDuplicados(Lista * pl, Cmp cmp, Actualizar actualizar, void * params)
{
   Lista * pl2;
   Nodo * nae;
   int cantElim = 0;
   while(*pl)
   {
       pl2 = &(*pl)->sig;

       while(*pl2 && cmp((*pl)->dato,(*pl2)->dato) == 0 ) ///Corte de control, mientras pl2 no sea null y el anterior (*pl) y (*pl2) sean iguales.
       {
           actualizar((*pl)->dato,(*pl2)->dato, params);
           nae = *pl2; ///Apunto con nae al nodo duplicado.
           *pl2 = nae->sig; ///Engancho *pl2 con el siguiente al que voy a eliminar.
           free(nae->dato); ///Elimino el duplicado.
           free(nae);
           cantElim++;
       }
       pl = &(*pl)->sig;
   }
   return cantElim;
}
int eliminarDeListaDesordDuplicados(Lista * pl, Cmp cmp, Actualizar actualizar, void * params)
{
   Lista * pl2;
   Nodo * nae;
   int cantElim = 0;
   while(*pl)
   {
       pl2 = &(*pl)->sig;

       while(*pl2)
       {
           if(cmp((*pl2)->dato,(*pl)->dato) == 0)
           {
            actualizar((*pl)->dato,(*pl2)->dato, params);
            nae = *pl2;
            *pl2 = nae->sig;
            free(nae->dato);
            free(nae);
            cantElim++;
           }
           else
                pl2 = &(*pl2)->sig;
       }
       pl = &(*pl)->sig;
   }
   return cantElim;

}
int OrdenarLista(Lista *pl, Cmp cmp)
{
    Lista *pri = pl;

    if(*pl == NULL)
        return 0;

    while((*pl)->sig)
    {
        if(cmp((*pl)->dato,(*pl)->sig->dato) > 0) ///si el actual es mayor que el siguiente.
        {
            Lista *q = pri;
            Nodo * aux = (*pl)->sig; ///Tomo la dirección del nodo que es menor al actual.
            (*pl)->sig = aux->sig; ///Uno el actual con el siguiente (salteo el nodo a insertar)
            while(cmp((*q)->dato,aux->dato) < 0)
                q = &(*q)->sig;
            aux->sig = *q; ///Vincula el nodo en la lista.
            *q = aux;
        }
        else
            pl = &(*pl)->sig; ///Avanza.
    }
    return TODO_OK;
}

int MostrarListaAlReves(Lista *pl, Accion show)
{
    if (*pl == NULL) {
        return TODO_OK;  // Si está vacía, simplemente retornamos.
    }
    MostrarListaAlReves(&(*pl)->sig,show);
    show((*pl)->dato);
    return TODO_OK;
}
