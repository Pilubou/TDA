#include "fecha.h"

int ingresarFechaDMA(tFecha *fec, const char *mensajeOpcional)
{
    if (mensajeOpcional)
        printf("%s", mensajeOpcional);
    else
        printf("Fecha (dd/mm/aaaa - 0=No Ingresa): ");
    fec->di = 0;
    fec->me = 0;
    fec->an = 0;
    fflush(stdin);
    scanf("%d/%d/%d", &fec->di, &fec->me, &fec->an);
    return fec->di && fec->me && fec->an;
}

void mostrarFechaDMA(const tFecha *fec)
{
    printf("%02d/%02d/%04d", fec->di, fec->me, fec->an);
}

int esFechaValida(const tFecha *fec)
{
    static const char dias[][12] = {
        { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
        { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } };
    return fec->me > 0 && fec->me <= 12 &&
           fec->an >= AN_MIN && fec->an <= AN_MAX &&
           fec->di > 0 && fec->di <= dias[esBisiesto(fec->an)][fec->me - 1];
}

int ingresarFechaValidaDMA(tFecha *fec, const char *mensajeOpcional)
{
    do
    {
        if (!ingresarFechaDMA(fec, mensajeOpcional))
            return 0;
    } while (!esFechaValida(fec));
    return 1;
}

int compararFecha(const tFecha *fec1, const tFecha *fec2)
{
    int cmp = fec1->an - fec2->an;
    if (cmp)
        return cmp;
    cmp = fec1->me - fec2->me;
    if (cmp)
        return cmp;
    return fec1->di - fec2->di;
}

int aJuliano(const tFecha *fec)
{
    int dias[][12] = {
        { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 },
        { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 } };

    return dias[esBisiesto(fec->an)][fec->me - 1] + fec->di;
}

int nroDeDiaDeLaSemana(const tFecha *fec)
{
    int distBase = fec->an % 400;
    return (SABADO - 1 + distBase + distBase / 4 - distBase / 100 +
            (distBase != 0) + aJuliano(fec)) % 7;
}

long diasEntreFechas(const tFecha *fecDesde, const tFecha *fecHasta)
{
    int anBase = fecDesde->an <= fecHasta->an ? fecDesde->an : fecHasta->an,
        distBaseDesde = fecDesde->an - anBase,
        distBaseHasta = fecHasta->an - anBase;
    long diasBaseAHasta = distBaseHasta * 365L + distBaseHasta / 4 -
                          distBaseHasta / 100 + distBaseHasta / 400 +
                          (distBaseHasta != 0) + aJuliano(fecHasta),
         diasBaseADesde = distBaseDesde * 365L + distBaseDesde / 4 -
                          distBaseDesde / 100 + distBaseDesde / 400 +
                          (distBaseDesde != 0) + aJuliano(fecDesde);
    return diasBaseAHasta - diasBaseADesde;
}

tFecha calcularEdad(const tFecha *fecDesde, const tFecha *fecHasta)
{
    static const char dias[][13] = {
        { 0, 31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30 },
        { 0, 31, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30 } };
    tFecha edad;

    edad = *fecHasta;
    if ((edad.di -= fecDesde->di) < 0)
    {
        edad.di += dias[esBisiesto(edad.an)][edad.me];
        edad.me--;
    }
    if ((edad.me -= fecDesde->me) < 0)
    {
        edad.me += 12;
        edad.an--;
    }
    edad.an -= fecDesde->an;
    return edad;
}
