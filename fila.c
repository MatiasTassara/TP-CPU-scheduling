#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libMatriz.h"
#include "abm.h"
#include "listas.h"
#include "fila.h"

void inicFila(Fila *filita)
{

    filita->cabecera = inicLista();
    filita->cola = inicLista();
    filita->contador = 0;
}
//CUANDO AGREGAMOS ELEMENTOS A LA FILA, ESTO DEBE REALIZARSE AGREGANDO AL FINAL DE LA LISTA
//LA LISTA ES LA QUE MANEJA LOS DATOS SIEMPRE, TIENE LA RESPONSABILIDAD
void agregar(Fila* filita,nodo* nuevo)
{

    if (filita->cabecera == NULL)
    {
        filita->cabecera = nuevo;
        filita->cola = nuevo;
    }
    else
    {
        filita->cabecera = agregarFinal(filita->cabecera,nuevo);
        filita->cola = nuevo;
    }

}
//LA FUNCION EXTRAER ES COMO EL DESAPILAR DE LA PILA. CUANDO EXTRAEMOS SACAMOS EL DATO DEL PRIMER NODO, LO RETORNAMOS
//ACTO SEGUIDO, ELIMINAMOS EL NODO DEL PRINCIPIO
nodo* quitar(Fila* filita)
{
    nodo* aux = NULL;

    if(filita->cabecera != NULL)
    {
        aux = filita->cabecera;
        nodo *sig = aux->siguiente;
        nodo *colita = buscarUltimo(filita->cabecera);
        if (filita->cabecera != colita)
        {
            filita->cabecera = sig;
            sig->anterior = NULL;
            aux->siguiente = NULL;

        }
        else
        {
            filita->cabecera = NULL;
            filita->cola = NULL;
        }

    }
    return aux;

}
/*
nodo* quitar(Fila *filita)
{
    nodo *retorno = NULL;
    if(filita->cabecera != NULL)
    {
        nodo *aux,*aux2;
        if(filita->cabecera == filita->cola)
        {
            aux = filita->cabecera;
            filita->cabecera = NULL;
            filita->cola = NULL;
        }
        else if(filita->cabecera != filita->cola)
        {
            aux = filita->cabecera;
            filita->cabecera = aux->siguiente;
            aux->siguiente = NULL;
            aux2 = filita->cabecera;
            aux2->anterior = NULL;
        }
    }
    return retorno;
}
*/
//PROBAMOS UN MOSTRAR FILA LLAMANDO A LA FUNCION DE MOSTRAR LISTA
void mostrarFila(Fila* filita)
{
      mostrarLista(filita->cabecera);
}

//FUNCION FILA VACIA QUE ES EL EQUIVALENTE A PILA VACIA. RETORNA O SI TIENE ELEMENTOS Y 1 SI ESTA VACIA

int filaVacia(Fila* filita)
{
    int rta = 0;
    if (filita->cabecera == NULL)
    {
        rta = 1;
    }

    return rta;
}

nodo* primero(Fila* filita)
{
    nodo* aux;
    int tope = 0;
    if (filita->cabecera != NULL)
    {
        aux = filita->cabecera;
        tope = aux;
    }
    return tope;

}


//Y SI NECESITAMOS AGREGAR EN ORDEN
//POR PRIORIDAD
void agregarOrdenadoPrioridad(Fila* filita,persona unCliente)
{
    nodo* ingresa;
    ingresa = crearNodo(unCliente);
    filita->cabecera = insertarPorPrioridad(filita->cabecera,ingresa);
    ////

    nodo *auxCola = filita->cola;

  /*  if(auxCola->siguiente == ingresa)
    {
        filita->cola = ingresa;
    }
        auxCola = NULL;
*/
}







//POR CANTIDAD DE ARTICULOS
void AgregarOrdenadoArticulos(Fila* filita,persona unCliente)
{
    nodo* ingresa;
    ingresa = crearNodo(unCliente);
    filita->cabecera = insertarPorCantProductos(filita->cabecera,ingresa);

}
