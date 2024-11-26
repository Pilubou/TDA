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
