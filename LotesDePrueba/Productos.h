#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED
#include "../Fecha/Fecha.h"

#define MAX(x,y) ((x) > (y) ? (x) : (y))
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

int AgregarRegistros();

void ActualizarProducto (void * registro_original, const void * nuevo_registro, void * params);

int Comparar_Clave_Producto (const void *p1, const void *p2);

int Comparar_Codigo_Producto (const void *p1, const void *p2);

void guardarDuplicadoEnArchivo(void * actualizado, const void * duplicado, void * params);

#endif // PRODUCTOS_H_INCLUDED
