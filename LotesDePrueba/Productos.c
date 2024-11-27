#include "Productos.h"
int CreacionLoteBinario (const char *nombre_archivo)
{
    FILE * pf = fopen(nombre_archivo,"wb");
    if(!pf)
    {
        printf("Error al intentar crear archivo \n");
        fclose(pf);
        return 0;
    }

    Producto lote[10] = {
    {"A12345", "Cafe Arab", "Nestle", {12, 11, 2024}, {12, 11, 2026}, 50, 4.50, 7.99},
    {"B67890", "Pasta Fusil", "Barilla", {8, 10, 2024}, {8, 10, 2025}, 120, 1.20, 2.50},
    {"C23456", "Aceitunas V", "Goya", {15, 9, 2024}, {15, 9, 2025}, 80, 2.30, 3.99},
    {"D34567", "Mermelada F", "Hero", {1, 8, 2024}, {1, 8, 2026}, 100, 3.10, 5.50},
    {"E45678", "Arroz Inte", "Uncle Ben's", {22, 7, 2024}, {22, 7, 2025}, 200, 0.90, 1.80},
    {"F56789", "Choco Amarg", "Lindt", {30, 6, 2024}, {30, 6, 2025}, 70, 3.50, 6.00},
    {"G67891", "Leche Descr", "Alpura", {10, 5, 2024}, {10, 5, 2025}, 300, 1.10, 2.00},
    {"H78912", "Cereal Gran", "Kellogg's", {18, 4, 2024}, {18, 4, 2025}, 150, 2.20, 4.50},
    {"I89123", "Te Verde", "Lipton", {5, 3, 2024}, {5, 3, 2026}, 60, 2.00, 3.50},
    {"J91234", "Queso Chedd", "Kraft", {25, 2, 2024}, {25, 2, 2025}, 50, 4.00, 6.50}
    };


    fwrite(lote,sizeof(lote),1,pf);
    fclose(pf);
    return 1;
}

int AgregarRegistros()
{
    FILE * pf = fopen("datos.bin","wb");
    if(!pf)
    {
        printf("Error al intentar crear archivo \n");
        fclose(pf);
        return 0;
    }
    Producto lote[5] = {
    {"A12345", "Cafe Arab", "Nestle", {12, 2, 2025}, {12, 1, 2026}, 20, 5.50, 7.99}, ///Cambio en precio y fechas. 70
    {"F56789", "Choco Amarg", "Lindt", {26, 11, 2024}, {30, 6, 2025}, 10, 3.50, 8.00}, ///Precio mayor de venta y cambio en la fecha de compra 80
    {"F56789", "Miel", "Lindt", {30, 6, 2024}, {30, 6, 2025}, 70, 3.50, 6.00}, ///Error
    {"D34567", "Mermelada F", "Hero", {1, 4, 2024}, {1, 9, 2026}, 100, 3.10, 5.50}, ///se queda con la fecha de compra y vencimiento original.
    {"D34567", "Jamon", "Hero", {1, 8, 2024}, {1, 8, 2026}, 100, 3.10, 5.50}, ///Error
    };

    fwrite(lote,sizeof(lote),1,pf);
    fclose(pf);
    return 1;
}
int LeerLote(const char * nombre_archivo)
{
    Producto lector;
    FILE * pf = fopen(nombre_archivo,"rb");
    if(!pf)
    {
        printf("Error al intentar leer archivo %s",nombre_archivo);
        fclose(pf);
        return 0;
    }
    printf("%-10s %-15s %-15s %-12s %-12s %-10s %-13s %-13s\n",
    "Codigo", "Descripcion", "Proveedor", "F. Compra", "F. Venc", "Cantidad", "P. Compra", "P. Venta");
    while(fread(&lector,sizeof(Producto),1,pf) == 1)
    {
        printf("%-10s %-15s %-15s %02d/%02d/%04d  %02d/%02d/%04d  %-10d %-13.2f %-13.2f\n",
        lector.codigo,
        lector.descripcion,
        lector.proveedor,
        lector.compra.di, lector.compra.me, lector.compra.an, // Fecha de compra
        lector.vencimiento.di, lector.vencimiento.me, lector.vencimiento.an, // Fecha de vencimiento
        lector.cantidad,
        lector.pre_compra,
        lector.pre_venta);
    }
    fclose(pf);
    return 1;
}

int MostrarProducto(const void *dato)
{
    Producto *elemento = (Producto *)dato;
    printf("%-10s %-15s %-15s %02d/%02d/%04d  %02d/%02d/%04d  %-10d %-13.2f %-13.2f\n",
        elemento->codigo,
        elemento->descripcion,
        elemento->proveedor,
        elemento->compra.di, elemento->compra.me, elemento->compra.an, // Fecha de compra
        elemento->vencimiento.di, elemento->vencimiento.me, elemento->vencimiento.an, // Fecha de vencimiento
        elemento->cantidad,
        elemento->pre_compra,
        elemento->pre_venta);
    return 1;  // O el código adecuado para indicar éxito
}

int CompararProducto(const void *p1, const void *p2)
{
    Producto *prod_1 = (Producto *)p1;
    Producto *prod_2 = (Producto *)p2;

    // Comparar por fecha de vencimiento
    int comp = compararFecha(&(prod_1->vencimiento), &(prod_2->vencimiento));
    if (comp != 0)
        return comp;

    // Si las fechas son iguales, comparar por proveedor
    comp = strcmp(prod_1->proveedor, prod_2->proveedor);
    if (comp != 0)
        return comp;

    // Si las fechas y proveedores son iguales, comparar por código
    return strcmp(prod_1->codigo, prod_2->codigo);
}

int Comparar_Clave_Producto (const void *p1, const void *p2)
{
    const Producto *prod_1 = (const Producto *)p1;
    const Producto *prod_2 = (const Producto *)p2;

    int cmp_codigo = strcmp(prod_1->codigo, prod_2->codigo);
    int cmp_descripcion = strcmp(prod_1->descripcion, prod_2->descripcion);

     // Ambas claves deben coincidir exactamente
    if (cmp_codigo == 0 && cmp_descripcion == 0) {
        return 0; // Claves iguales
    }

    // Si los códigos son distintos, devolver el resultado de su comparación
    if (cmp_codigo != 0) {
        return cmp_codigo;
    }

    // Si los códigos son iguales pero las descripciones difieren
    return cmp_descripcion;
}
int Comparar_Codigo_Producto (const void *p1, const void *p2)
{
    const Producto *prod_1 = (const Producto *)p1;
    const Producto *prod_2 = (const Producto *)p2;

    return strcmp(prod_1->codigo,prod_2->codigo);

}
void ActualizarProducto (void * registro_original, const void * nuevo_registro, void * params)
{
    /*Insertar los nuevos nodos al final de la lista, salvo que la clave ya estuviera cargada y la
    descripción coincide, con lo cual se acumula la cantidad, se retiene la última fecha de compra
    y la fecha de vencimiento más vieja, el mayor precio de compra y de venta; si la descripción
    no coincidiera, se genera un nuevo nodo.*/
    Producto * original = (Producto *) registro_original;
    Producto * nuevo = (Producto *) nuevo_registro;

    original->cantidad += nuevo->cantidad;
    if(compararFecha(&(original->vencimiento),&(nuevo->vencimiento)) > 0 ) ///Si la original es una fecha más reciente.
        original->vencimiento = nuevo->vencimiento;

    if(compararFecha(&(original->compra),&(nuevo->compra)) < 0)
        original->compra = nuevo->compra;

    original->pre_compra = MAX(original->pre_compra,nuevo->pre_compra);
    original->pre_venta = MAX(original->pre_venta,nuevo->pre_venta);

}
void guardarDuplicadoEnArchivo(void * actualizado, const void * duplicado, void * params)
{
    FILE * pf = (FILE *)params;
    Producto * producto = (Producto *)duplicado;

    fprintf(pf,
            "%s|%s|%s|%02d/%02d/%04d|%02d/%02d/%04d|%d|%.2f|%.2f\n",
            producto->codigo,
            producto->descripcion,
            producto->proveedor,
            producto->compra.di, producto->compra.me, producto->compra.an,
            producto->vencimiento.di, producto->vencimiento.me, producto->vencimiento.an,
            producto->cantidad,
            producto->pre_compra,
            producto->pre_venta);
}
