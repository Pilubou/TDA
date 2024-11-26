#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED
#include "../Fecha/Fecha.h"

typedef struct
{
    char codigo[7];
    char descripcion[15];
    char proveedor[15];
    tFecha compra;
    tFecha vencimiento;
    int cantidad;
    float pre_compra;
    float pre_venta;

}Producto;

int CreacionLoteBinario (const char *nombre_archivo);

int LeerLote(const char * nombre_archivo);

int MostrarProducto(const void *dato);

int CompararProducto(const void *p1, const void *p2);

#endif // PRODUCTOS_H_INCLUDED
