#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

typedef struct Fila
{
    int contador;
    struct nodo* cabecera;
    struct nodo* cola;
}Fila;


void inicFila(Fila*);
void agregar(Fila*,nodo*);
nodo* quitar(Fila*);
void mostrarFila(Fila*);
int filaVacia(Fila*);
nodo* primero(Fila*);
void agregarOrdenadoPrioridad(Fila*,persona);
void AgregarOrdenadoArticulos(Fila*,persona);


#endif // FILA_H_INCLUDED
