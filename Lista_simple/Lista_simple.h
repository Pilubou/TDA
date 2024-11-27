#ifndef LISTA_SIMPLE_H_INCLUDED
#define LISTA_SIMPLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Nodo.h"

#define DUPLICADO -1;


typedef Nodo * Lista;

typedef int (*Accion) (const void *d);

typedef int (*Cmp) (const void * e1, const void * e2);

typedef int (*Condicion)(const void * elem);

typedef void (*Actualizar) (void * actualizado, const void * actualizador,void * params);

void CrearLista (Lista * pl);

int listaVacia(const Lista *pl);

int listaLlena (const Lista *pl, size_t tamElem);

int insertarEnListaOrd(Lista * pl, const void * dato, size_t tamElem, Cmp cmp);

int insertarEnListaOrdOActualizar(Lista * pl, const void * dato, size_t tamElem, Cmp cmp,Actualizar actualiza, void * params);

int insertarPrimeroEnLista(Lista *pl, void * dato, size_t tamDato);

int insertarUltimoEnLista(Lista *pl, void * dato, size_t tamDato);

int insertarUltimoEnListaOActualizar(Lista *pl, void * dato, size_t tamDato,Cmp cmp,Actualizar actualizar, void * params);

int buscarEnListaDesord(Lista *pl, void * dato,unsigned tamDato, Cmp cmp);

int eliminarListaDesordPorValor (Lista *pl, void *dato, size_t tamDato, Cmp cmp);

int eliminarListaOrdPorValor (Lista *pl, void *dato, size_t tamDato, Cmp cmp);

int MapLista(Lista *pl, Accion accion);

void VaciarLista(Lista *pl);

int eliminarDeListaOrdDuplicados(Lista * pl, Cmp cmp, Actualizar actualizar, void * params);

int eliminarDeListaDesordDuplicados(Lista * pl, Cmp cmp, Actualizar actualizar, void * params);

int OrdenarLista(Lista * pl, Cmp cmp);

int MostrarListaAlReves(Lista *pl, Accion show);

#endif // LISTA_SIMPLE_H_INCLUDED
