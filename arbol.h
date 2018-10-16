#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

typedef struct nodoArbol
 {
     persona consumidor;
     struct nodoArbol* izq;
     struct nodoArbol* der;

 }nodoArbol;

 nodoArbol* InicArbol();
 nodoArbol* CrearNodoArbol(persona);
 nodoArbol* Insertar(nodoArbol*, persona);
 nodoArbol* CargarArbol(nodoArbol*, char []);
 nodoArbol* iniciaYcargaArbol(nodoArbol*, char[]);
 void VerPersona(nodoArbol*);
 void Preorder(nodoArbol*);
 void InOrder(nodoArbol*);
 void PostOrder(nodoArbol*);
 void EliminarNodoArbol(nodoArbol**, char[40]);
 void Reemplazar(nodoArbol**);
 nodoArbol* borraNodoPorNombre(nodoArbol*);


#endif // ARBOL_H_INCLUDED
