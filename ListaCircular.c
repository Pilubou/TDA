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
int EliminarPorValor(tLista *pl, const void *dato, int (*cmp)(const void *, const void *))
{
    if (!*pl)  // Si la lista está vacía, no se puede eliminar nada
        return 0;

    tNodo *actual = *pl;
    tNodo *anterior = NULL;

    // Caso 1: Si el primer nodo es el que queremos eliminar
    if (cmp((*pl)->dato, dato) == 0)
    {
        // Si hay más de un nodo
        if ((*pl)->sig != *pl)
        {
            // Encontramos el último nodo para actualizar su puntero
            while (actual->sig != *pl)
                actual = actual->sig;

            // El último nodo apunta al segundo nodo
            actual->sig = (*pl)->sig;
        }
        // Si hay solo un nodo
        else
        {
            *pl = NULL;  // La lista quedará vacía
        }

        // Liberar memoria del primer nodo
        free((*pl)->dato);
        free(*pl);
        *pl = actual->sig;  // Actualizar el puntero de la lista
        return 1;
    }

    // Caso 2: Buscar el nodo en el resto de la lista
    anterior = *pl;
    actual = anterior->sig;

    while (actual != *pl && cmp(actual->dato, dato) != 0)
    {
        anterior = actual;
        actual = actual->sig;
    }

    if (actual != *pl)  // Si se encontró el nodo
    {
        anterior->sig = actual->sig;  // El nodo anterior apunta al siguiente del nodo eliminado
        free(actual->dato);
        free(actual);
        return 1;
    }

    // Si llegamos aquí, el dato no se encontró en la lista
    return 0;
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
