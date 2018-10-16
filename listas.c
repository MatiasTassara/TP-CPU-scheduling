#include <stdio.h>
#include <stdlib.h>             ////CUANDO EL USUARIO SE DA DE BAJA QUE LO SAQUE DEL SISTEMA
#include <string.h>
#include "libMatriz.h"
#include "abm.h"
#include "listas.h"

nodo* inicLista()
{
    return  NULL;
}



nodo* crearNodo(persona unaPersona)
{
    nodo *nuevoNodo = (nodo*) malloc (sizeof(nodo));
    strcpy(nuevoNodo->cliente.apellido, unaPersona.apellido);
    strcpy(nuevoNodo->cliente.nombre, unaPersona.nombre);
    nuevoNodo->cliente.id = unaPersona.id;
    nuevoNodo->cliente.tipoCliente = unaPersona.tipoCliente;
    nuevoNodo->cliente.medioPago = unaPersona.medioPago;
    nuevoNodo->cliente.cantArticulos = unaPersona.cantArticulos;
    nuevoNodo->cliente.tiempoEspera = unaPersona.tiempoEspera;
    nuevoNodo->cliente.tiempoProcesado = unaPersona.tiempoProcesado;
    nuevoNodo->cliente.eliminado = unaPersona.eliminado;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->anterior = NULL;
    return nuevoNodo;
}

void pasaDeArchivoALista(char archiCliente[],nodo *lista)
{
    nodo *nuevo;
    persona aux;
    FILE *cli;
    cli = fopen(archiCliente,"rb");
    if(cli == NULL)
    {
        printf("Error al pasar clientes a la lista\n");
    }
    else
    {
        while(fread(&aux,sizeof(nodo),1,cli) > 0)
        {
            nuevo = crearNodo(aux);
            lista = agregarPrincipio(lista,nuevo);
        }
        fclose(cli);
    }
}

nodo* agregarPrincipio(nodo *lista,nodo *nuevo)
{
    if(lista == NULL)
    {
        lista = nuevo;
    }
    else
    {
        nuevo->siguiente = lista;
        lista->anterior = nuevo;
        lista = nuevo;
    }
    return lista;
}

nodo* buscarUltimo(nodo* lista)
{
    nodo *seg = lista;
    if(lista != NULL)
    {
        while(seg->siguiente != NULL)
        {
            seg = seg->siguiente;
        }
    }
    return seg;
}
nodo* agregarFinal(nodo *lista,nodo *nuevo)
{
    nodo *ultimo = lista;
    if(lista == NULL)
    {
        lista = nuevo;
    }
    else
    {
        ultimo = buscarUltimo(lista);
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;
    }
    return lista;
}

nodo* borrarClientePorId(nodo *lista,int dato)
{
    nodo* aBorrar = NULL;
    nodo* seg = NULL;

    if(lista != NULL)
    {
        if(lista->cliente.id == dato)
        {
            aBorrar = lista;
            lista = lista->siguiente;

            if(lista!=NULL)
            {
                lista->anterior = NULL;
            }
            free(aBorrar);
        }
        else
        {
            seg = lista->siguiente;
            while(seg != NULL && seg->cliente.id != dato)
            {
                seg = seg->siguiente;
            }

            if(seg != NULL)
            {
                nodo* ante = seg->anterior;
                ante->siguiente = seg->siguiente;
                if(seg->siguiente != NULL)
                {
                    nodo* proximo = seg->siguiente;
                    proximo->anterior = ante;
                }
                free(seg);
            }
            else
            {
                printf("Cliente no encontrado\n");
            }
         }
    }
    return lista;
}

nodo* borrarClientePorNombre(nodo *lista,char nombre[])
{
    nodo* aBorrar = NULL;
    nodo* seg = NULL;

    if(lista != NULL)
    {
        if(strcmp(lista->cliente.nombre,nombre) == 0)
        {
            aBorrar = lista;
            lista = lista->siguiente;
            if(lista!=NULL)
            {
                lista->anterior = NULL;
            }
            free(aBorrar);
        }
        else
        {
            seg = lista->siguiente;
            while(seg != NULL && strcmp(seg->cliente.nombre,nombre) != 0)
            {
                seg = seg->siguiente;
            }
            if(seg!= NULL)
            {
                nodo* ante = seg->anterior;
                ante->siguiente = seg->siguiente;
                if(seg->siguiente != NULL)
                {
                    nodo* proximo = seg->siguiente;
                    proximo->anterior = ante;
                }
                free(seg);
            }
            else
            {
                printf("Cliente no encontrado\n");
            }

         }
    }
    return lista;
}

nodo* insertarPorPrioridad(nodo *lista,nodo *nuevoNodo) //inserta por tipo de cliente (prioridad)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else if (nuevoNodo->cliente.tipoCliente < lista->cliente.tipoCliente)
    {
        lista = agregarPrincipio(lista,nuevoNodo);
    }
    else
    {
        nodo *ante = lista;
        nodo *seg = lista->siguiente;

        while(seg!=NULL && seg->cliente.tipoCliente < nuevoNodo->cliente.tipoCliente)
        {
            ante = seg;
            seg = seg->siguiente;
        }
        ante->siguiente = nuevoNodo;
        nuevoNodo->anterior = ante;
        nuevoNodo->siguiente = seg;
        if(seg != NULL)
        {
            seg->anterior = nuevoNodo;
        }
    }
    return lista;
}


nodo* insertarPorCantProductos(nodo *lista,nodo *nuevoNodo) //inserta por cant de productos
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else if (nuevoNodo->cliente.cantArticulos < lista->cliente.cantArticulos)
    {
        lista = agregarPrincipio(lista,nuevoNodo);
    }
    else
    {
        nodo *ante = lista;
        nodo *seg = lista->siguiente;
        while(seg!=NULL && seg->cliente.cantArticulos < nuevoNodo->cliente.cantArticulos)
        {
            ante = seg;
            seg = seg->siguiente;
        }
        ante->siguiente = nuevoNodo;
        nuevoNodo->anterior = ante;
        nuevoNodo->siguiente = seg;
        if(seg != NULL)
        {
            seg->anterior = nuevoNodo;
        }
    }
    return lista;
}



void mostrarFilaDesdePrimero(nodo *lista)
{
    if(lista != NULL)
    {
        mostrarCliente(lista);
        mostrarFilaDesdePrimero(lista->siguiente);
    }
}

void mostrarFilaDesdeUltimo(nodo *lista)
{
    if(lista != NULL)
    {
        mostrarFilaDesdeUltimo(lista->siguiente);
        mostrarCliente(lista);
    }
}

void mostrarCliente(nodo *unCliente)
{
    printf("--------------------------------\n");
    printf("ID del cliente: %d\n",unCliente->cliente.id);
    printf("Apellido: %s",unCliente->cliente.apellido);
    printf("Nombre: %s\n",unCliente->cliente.nombre);
    printf("Tipo de cliente (prioridad): %d- ",unCliente->cliente.tipoCliente);
    if(unCliente->cliente.tipoCliente == 1)
    {
        printf("Embarazada\n");
    }
    else if(unCliente->cliente.tipoCliente == 2)
    {
        printf("Jubilado/a\n");
    }
    else
    {
        printf("Cliente comun\n");
    }
    printf("Medio de pago: %d- ",unCliente->cliente.medioPago);
    if(unCliente->cliente.medioPago == 1)
    {
        printf("Efectivo\n");
    }
    else if(unCliente->cliente.medioPago == 2)
      {
          printf("Credito\n");
      }
    else
    {
        printf("Todos\n");
    }
    printf("Cantidad de articulos: %d\n",unCliente->cliente.cantArticulos);
    printf("--------------------------------\n");
}

int sumaCantidadArticulosCola(nodo *lista)
{
    int total = 0;
    if(lista != NULL)
    {
        total = lista->cliente.cantArticulos + sumaCantidadArticulosCola(lista->siguiente);
    }
    return total;
}

nodo* borrarLista(nodo *lista)
{
    nodo *prox;
    nodo *seg;
    seg = lista;
    while(seg != NULL)
    {
        prox = seg->siguiente;
        free(seg);
        seg = prox;
    }
    return seg;
}

nodo* borrarPrimerCliente(nodo *lista)
{
    nodo *aux = lista;
    lista = lista->siguiente;
    nodo *prox = lista->siguiente;
    prox->anterior = lista;
    free(aux);
    return lista;
}

nodo* borrarUltimoCliente(nodo *lista)
{
    nodo *aux = lista;
    nodo *ante;
    aux = buscarUltimo(lista);
    ante = aux->anterior;
    free(aux);
    ante->siguiente=NULL;
    return lista;
}

void mostrarLista(nodo *lista)
{
    nodo *seg = lista;
    while(seg != NULL)
    {
        mostrarCliente(seg);
        seg = seg->siguiente;
    }
}



