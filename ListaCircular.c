typedef struct sNodo
{
   void * dato;
   unsigned tam;
   struct sNodo * sig;

}tNodo;

typedef tLista * tNodo;

void CrearLista(tLista * pl)
{
   *pl = NULL;
}
int insertarEnOrden(tLista * pl, void * dato, unsigned tamDato, Cmp cmp)
{
   int rc;
   tNodo * nue = (tNodo*) malloc(sizeof(tNodo));
   void * datoN = malloc(tamDato);
   if(!nue || !datoN)
   {
     free(nue);
     free(datoN);
     return SIN_MEM;
   }
   memcpy(datoN, dato, tamDato);
   nue->dato = datoN;
   nue->tam = tamDato;
   if(!*pl) ///Caso de primer nodo a insertar
   {
     nue -> sig = nue;
     *pl = nue;
     return TODO_OK;
   }
   while(*pl && (rc = cmp (dato, (*pl)->dato)) < 0)
   {
      pl = &(*pl)->sig;
   }
   
 

}