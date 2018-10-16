#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED

typedef struct nodo{
        persona cliente;
        struct nodo * siguiente;
        struct nodo * anterior;
}nodo;

nodo* inicLista();
nodo* crearNodo(persona);
void pasaDeArchivoALista(char[],nodo*);
nodo* agregarPrincipio(nodo*,nodo*);
nodo* buscarUltimo(nodo*);
nodo* agregarFinal(nodo*,nodo*);
nodo* insertarPorPrioridad(nodo*,nodo*);
nodo* insertarPorCantProductos(nodo*,nodo*);
nodo* borrarClientePorId(nodo*,int);
nodo* borrarClientePorNombre(nodo*,char[]);
void mostrarFilaDesdeUltimo(nodo*) ;
void mostrarFilaDesdePrimero(nodo*);
void mostrarCliente(nodo*);
void mostrarLista(nodo *);
int sumaCantidadArticulosCola(nodo*);
nodo* borrarLista(nodo*);
nodo* borrarPrimerCliente(nodo*);
nodo* borrarUltimoCliente(nodo*);

#endif // LISTAS_H_INCLUDED
