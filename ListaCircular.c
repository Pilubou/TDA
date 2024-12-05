void crearLista(tLista * pl)
{
    *pl = NULL;
}

int insertarEnOrden(tLista *pl, void * dato, unsigned tamDato, int (*cmp)(const void *, const void *))
{
    tNodo * nue = (tNodo *)malloc(sizeof(tNodo));
    if(!nue || !(nue->dato = malloc(tamDato)))
    {
        free(nue);
        return 0;
    }
    memcpy(nue->dato, dato, tamDato);
    nue->tamDato = tamDato;
    if(!*pl)
    {
        nue->sig = nue;
        *pl = nue;
        return 1;
    }
    tNodo *act = *pl;
    int comp = cmp(act->dato,nue->dato);
    if(comp > 0)
    {
        nue->sig = act;
        act = act->sig;
        while(act->sig != *pl)
            act = act->sig;
        act->sig = nue;
        *pl = nue;
        return 1;
    }
    tLista *lista = &(*pl)->sig; // Comenzar con el siguiente nodo
    while (*lista != *pl && cmp((*lista)->dato, nue->dato) < 0)
        lista = &(*lista)->sig;

    nue->sig = *lista; // El nuevo nodo apunta al siguiente
    *lista = nue;      // Enlazar el nodo actual al nuevo
    return 1;
}
void Mostrar_Lista(tLista *pl, void (*mostrar)(const void *))
{
    if (!*pl) // Si la lista está vacía, no hay nada que mostrar
        return;

    tNodo *aux = *pl;
    while(aux->sig != *pl)
    {
        mostrar(aux->dato);
        aux = aux->sig;
    }
    mostrar(aux->dato);
}
