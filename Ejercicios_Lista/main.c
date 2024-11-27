#include "../Lista_simple/Lista_simple.h"

#include "../LotesDePrueba/Productos.h"

int main()
{
    Producto lector;
    Lista lista;
    FILE * pf = fopen("datos1.bin","rb");
    if(!pf)
    {
        printf("Error al intentar leer archivo");
        fclose(pf);
        return 0;
    }
    printf("%-10s %-15s %-15s %-12s %-12s %-10s %-13s %-13s\n",
    "Codigo", "Descripcion", "Proveedor", "F. Compra", "F. Venc", "Cantidad", "P. Compra", "P. Venta\n");
    CrearLista(&lista);
    while(fread(&lector,sizeof(Producto),1,pf) == 1)
        insertarEnListaOrd(&lista,&lector,sizeof(Producto),CompararProducto);
    fclose(pf);
    MapLista(&lista,MostrarProducto);
    printf("\n");
    pf = fopen("datos.bin","rb");
    if(!pf)
    {
        printf("Error al intentar leer archivo");
        fclose(pf);
        return 0;
    }

    while(fread(&lector,sizeof(Producto),1,pf) == 1){

        insertarUltimoEnListaOActualizar(&lista,&lector,sizeof(lector),Comparar_Clave_Producto,ActualizarProducto,NULL);
    }
    printf("\n");
    MapLista(&lista,MostrarProducto);
    printf("\n");
    FILE *pe = fopen("errores2.txt","wt");
    if(!pe)
        return 0;
    eliminarDeListaDesordDuplicados(&lista,Comparar_Codigo_Producto,guardarDuplicadoEnArchivo,pe);
    fclose(pf);
    fclose(pe);
    printf("Lista sin duplicados \n");
    MapLista(&lista,MostrarProducto);
    return 0;
}
