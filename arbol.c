#include <stdio.h>
#include <stdlib.h>             ////CUANDO EL USUARIO SE DA DE BAJA QUE LO SAQUE DEL SISTEMA
#include <string.h>
#include "libMatriz.h"
#include "abm.h"
#include "arbol.h"

nodoArbol* InicArbol()
{
    return NULL;
}

 //CREAR NODO RECIBE CUAL PAQUETE, LA ESTRUCTURA DESDE EL ARCHIVO CLIENTE

 nodoArbol* CrearNodoArbol(persona consumer)
 {
     nodoArbol* aux = (nodoArbol*) malloc(sizeof(nodoArbol));

     aux->consumidor.id = consumer.id;
     strcpy(aux->consumidor.apellido, consumer.apellido);
     strcpy(aux->consumidor.nombre, consumer.nombre);
     aux->consumidor.tipoCliente = consumer.tipoCliente;
     aux->consumidor.medioPago = consumer.medioPago;
     aux->consumidor.cantArticulos = consumer.cantArticulos;
     aux->consumidor.tiempoEspera = consumer.tiempoEspera;
     aux->consumidor.tiempoProcesado = consumer.tiempoProcesado;
     aux->consumidor.eliminado = consumer.eliminado;

     aux->der = NULL;
     aux->izq = NULL;

     return aux;
 }

//FUNCION QUE INSERTA POR ORDEN ALFABETICO LOS CLIENTES DEL ARCHIVO

nodoArbol* Insertar(nodoArbol* arbol, persona consumer)
{
    int rta;
    if(arbol == NULL)
    {
        arbol = CrearNodoArbol(consumer);
    }
    else
    {
        rta = strcmp(arbol->consumidor.nombre, consumer.nombre);

        if (rta > 0)
        {

            arbol->der = Insertar(arbol->der, consumer);
        }
        else
        {
            arbol->izq = Insertar(arbol->izq, consumer);

        }
    }
    return arbol;
}
//FUNCION GENERAL DE CARGA DESDE EL ARCHIVO AL ARBOL

nodoArbol* CargarArbol(nodoArbol* arbol, char archiCliente[])
{
    persona aux;
    FILE * archi;
    archi = fopen(archiCliente, "rb");
    if(archi != NULL)
    {
        while(fread(&aux, sizeof(persona), 1, archi) > 0)
        {
            arbol = Insertar(arbol, aux);
        }
        fclose(archi);
    }
    return arbol;
}
nodoArbol* iniciaYcargaArbol(nodoArbol* arbol, char archiCliente[])
{
    //arbol = InicArbol();
    arbol = CargarArbol(arbol, archiCliente);
    return arbol;
}
//FUNCIONES DE MUESTRA DE ARBOL, SON TRES MAS UNA AUXILIAR PARA MOSTRAR MODULADAMENTE EL DETALLE
//FUNCION DE MUESTRA DE DETALLE QUE SERÁ UTILIZADA EN TODAS LAS DE MUESTRA.

void VerPersona(nodoArbol* arbol)
{
    printf("\n--------------------------------------------------------------\n");
    printf("\nID:                                               %d", arbol->consumidor.id);
    printf("\nAPELLIDO:                                         %s", arbol->consumidor.apellido);
    printf("\nNOMBRE:                                           %s", arbol->consumidor.nombre);
    printf("\nTIPO DE CLIENTE:(1-embarazada,2-jubilado,3-comun) %d", arbol->consumidor.tipoCliente);
    printf("\nMEDIO DE PAGO: (1-efectivo,2-credito,3-todos)     %d", arbol->consumidor.medioPago);
    printf("\nTIEMPO DE ESPERA:                                 %d", arbol->consumidor.tiempoEspera);
    printf("\nTIEMPO PROCESADO:                                 %d", arbol->consumidor.tiempoProcesado);
    printf("\nELIMINADO:                                        %d", arbol->consumidor.eliminado);
    printf("\n--------------------------------------------------------------\n");
}

//PRE ORDER - PRIMERO LA RAIZ, LUEGO EL IZQUIERDO Y FINALMENTE EL LADO DERECHO
void Preorder(nodoArbol* arbol)
{
    if (arbol != NULL)
    {
        VerPersona(arbol);

        Preorder(arbol->izq);
        Preorder(arbol->der);
    }
}
// IN ORDER - PRIMERO EL IZQUIERDO, LUEGO LA RAIZ Y FINALMENTE LA DERECHA
void InOrder(nodoArbol* arbol)
{
    if (arbol != NULL)
    {
        InOrder(arbol->izq);
        VerPersona(arbol);
        InOrder(arbol->der);

    }

}

//POST ORDER - PRIMERO LA IZQUIERDA, LUEGO LA DERECHA Y FINALMENTE LA RAIZ

void PostOrder(nodoArbol* arbol)
{
    if (arbol != NULL)
    {
      PostOrder(arbol->izq);
      PostOrder(arbol->der);
      VerPersona(arbol);
    }

}
// FUNCIONES PARA BORRAR UN NODO - SON DOS, UNA PARA BORRAR Y OTRA PARA REEMPLAZAR

void EliminarNodoArbol(nodoArbol** arbol, char nombre[40])
{
    if((*arbol) == NULL)
    {
        printf("\nCLIENTE NO ENCONTRADO. \n");
    }
    else if((strcmp(nombre, (*arbol)->consumidor.nombre) < 0))
    {
                EliminarNodoArbol(&(*arbol)->izq, nombre);
    }
    else if ((strcmp(nombre, (*arbol)->consumidor.nombre)) > 0)
    {
            EliminarNodoArbol(&(*arbol)->der, nombre);
    }
    else
    {
            nodoArbol* aux = (*arbol);
            if (aux->izq == NULL)
            {
                (*arbol) = aux->der;
            }
            else if(aux->der == NULL)
            {
                (*arbol) = aux->izq;
            }
            else
            {
                Reemplazar(&aux);
            }
            free(aux);
     }
}
void Reemplazar(nodoArbol**aux)
{
    nodoArbol *x, *y;
    y = (*aux);
    x = (*aux)->izq;
    while (x->der != NULL)
    {
        y = x;
        x = x->der;
    }
    (*aux) = x;
    if (y == (*aux))
    {
        y->izq = x->izq;
    }
    else
    {
        y->der = x->izq;
    }
    (*aux) = x;
}

nodoArbol* borraNodoPorNombre(nodoArbol* arbol)
{
    char nombre[40];
    printf("\nINGRESE EL NOMBRE DEL CLIENTE A ELIMINAR DEL ARBOL: \n");
    fflush(stdin);
    gets(nombre);
    EliminarNodoArbol(&arbol, nombre);
    return arbol;
}
