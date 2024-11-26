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
    CrearLista(&lista);
    while(fread(&lector,sizeof(Producto),1,pf) == 1){

        //MostrarProducto(&lector);
        insertarEnListaOrd(&lista,&lector,sizeof(Producto),CompararProducto);
    }
    fclose(pf);
    MapLista(&lista,MostrarProducto);
    VaciarLista(&lista);
    MapLista(&lista,MostrarProducto);
    return 0;
}
