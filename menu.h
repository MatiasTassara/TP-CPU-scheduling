#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

void menuPrincipal(int,char[],char[],char[], nodoArbol*,caja[], int);
void submenuLogin1(int,char[],char[],char[],int, nodoArbol*, caja[], int);
void subMenuPrograma(int,char[],char[], char[], nodoArbol*, caja[], int);
void menuDeArbol(int,char[],char[], char[], nodoArbol*, caja[], int);
void menuDeCajas(int,char[],char[], char[], nodoArbol*, caja[], int);
void menuCargaClientesAcaja(int,char[],char[], char[],nodoArbol*, caja[], int);
void datosEstadisticos(int,char[],char[], char[], nodoArbol*, caja[], int);
void subMenuUsuarios(int,char[],char[],char[],int, nodoArbol*, caja[], int);
void subMenuModificaUsuario(int,char[],char[],int);
void subMenuClientes(int,char[],char[], nodoArbol*,caja[], int);
void subMenuModificaCliente(int,char[],char[],nodoArbol*,caja[], int);
void EncuadrePrincipal();
void ReplicanteHorizontal1(int);
void ReplicanteHorizontal2(int, int);
void fDibujaLinea(char linea, int hasta);
void fMuestroFechaHora();
void encabezadoPantallaAgrandada();

#endif // MENU_H_INCLUDED
