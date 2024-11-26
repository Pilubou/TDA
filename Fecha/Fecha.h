#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED
#include <stdio.h>
#include <string.h>
#define DOMINGO
#define LUNES
#define MARTES
#define MIERCOLES
#define JUEVES
#define VIERNES
#define SABADO

#define	AN_MIN	1
#define	AN_MAX	5000

#define esBisiesto( X ) ( ( ( X ) % 4 == 0 && ( X ) % 100 != 0 ) || \
( X ) % 400 == 0 )

typedef struct
{
int di,
    me,
    an;
} tFecha;

int ingresarFechaDMA(tFecha *fec, const char *mensajeOpcional);
void mostrarFechaDMA(const tFecha *fec);
int esFechaValida(const tFecha *fec);
int ingresarFechaValidaDMA(tFecha *fec, const char *mensajeOpcional);
int compararFecha(const tFecha *fec1, const tFecha *fec2);
int aJuliano(const tFecha *fec);
int nroDeDiaDeLaSemana(const tFecha *fec);
long diasEntreFechas(const tFecha *fecDesde, const tFecha *fecHasta);
tFecha calcularEdad(const tFecha *fecDesde, const tFecha *fecHasta);



#endif // FECHA_H_INCLUDED
