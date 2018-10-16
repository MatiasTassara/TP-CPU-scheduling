#include <stdio.h>
#include <stdlib.h>             ////CUANDO EL USUARIO SE DA DE BAJA QUE LO SAQUE DEL SISTEMA
#include <string.h>
#include "libMatriz.h"
#include "abm.h"
#include "arbol.h"
#include "listas.h"
#include "fila.h"
#include "caja.h"


char archiUsuario[] = {"usuarios.dat"};
char archiCliente[] = {"clientes.dat"};
char archiCajas[] = {"cajas.dat"};


int main()
{

    int opcion;
    nodoArbol* arbol;
    arbol = InicArbol();
    caja arreglo [12];
    int validos = 0;

    menuPrincipal(opcion,archiUsuario,archiCliente,archiCajas,arbol,arreglo,validos);
    abreParaMostrarUsuario(archiUsuario);
    abreParaMostrarCliente(archiCliente);

    return 0;
}

