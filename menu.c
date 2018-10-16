#include "gotoxy.h"
#include <conio.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libMatriz.h"
#include "abm.h"
#include "listas.h"
#include "fila.h"
#include "arbol.h"
#include "caja.h"
#include "menu.h"

void fDibujaLinea(char linea, int hasta)
{
    int i=0;
    for(i=0;i<hasta;i++){
        printf("%c",linea);
    }
}
void fMuestroFechaHora()
 {
    int espacio=0;
    int tamCadena=0;
    char linea = '=';
    int hasta = 78;
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];
    color(31);
    fDibujaLinea(linea,hasta);
    color(10);
    strftime(output,128,"%d/%m/%Y %H:%M",tlocal);
    tamCadena=strlen(output);
    espacio=(25-tamCadena);
    printf(" %s ",output);
    color(31);
    fDibujaLinea(linea,hasta);

}
void encabezadoPantallaAgrandada()
{
    system("mode con: cols=174 lines=800");
    color(31);
    char linea = 205;
    char lineaVerti=186; //PARA EL RECUADRO PRINCIPAL
    int hasta = 174;
    int derecha = 0;
    int izquierda = 174;
    int seguimiento = 0; //sigue la evolucion de la impresion por pantalla

    fDibujaLinea(linea,hasta);
    fMuestroFechaHora();
    fDibujaLinea(linea,hasta);

    //fDibujaLinea(lineaVerti,hasta);

}
void EncuadrePrincipal()
{

    int cant1 = 172, cant2 = 60;
    //system("cls");
    ReplicanteHorizontal1(cant1);
    printf("\n");
    ReplicanteHorizontal2(cant1, cant2);

    ReplicanteHorizontal1(cant1);
    printf("\n");
    //system("PAUSE");
}
void ReplicanteHorizontal1(int cant1)
{
    int contador = 0;
    while (contador <= cant1)
    {
        printf("%c",205);
        contador++;
    }
}
void ReplicanteHorizontal2(int cant1, int cant2)
{
    int contador1 = 0, contador2 = 0;

    while (contador1 <= cant2)
    {
        printf("*");
        while (contador2 < cant1-1)
        {
            printf(" ");
            contador2++;

        }
        printf("*");
        printf("\n");
        contador1++;
        contador2 = 0;
    }
}
void menuPrincipal(int opcion,char archiUsuario[],char archiCliente[],char archiCajas[], nodoArbol* arbol, caja arreglo[], int validos)
{
    int idUsuario;
    do
    {

        system("cls");
        encabezadoPantallaAgrandada();
        EncuadrePrincipal();
        gotoxy(70,8);
        printf("SUPERMERCADO EL PROCESADOR");
        gotoxy(70,11);

        printf("1- Registrarse");
        gotoxy(70,13);
        printf("2- Login");
        gotoxy(70,15);
        printf("0- Salir");
        gotoxy(70,17);
        printf("Ingrese opcion: ");
        gotoxy(70,19);
        scanf("%d",&opcion);
        if(opcion  > -1 && opcion < 3)
        {
            switch(opcion)
            {
            case 0:
                printf("Gracias vuelva pronto!!!\n");
                printf("SUPERMERCADO EL PROCESADOR!!.\n\n");
                break;
            case 1:
                system("cls");
                altaUsuario(archiUsuario);
                system("pause");
                break;
            case 2:
                system("cls");
                idUsuario = ingresoAlPrograma(archiUsuario);
                submenuLogin1(opcion,archiUsuario,archiCliente, archiCajas,idUsuario,arbol,arreglo,validos);
                break;
            }
        }
        else
        {
            printf("Opcion incorrecta\n");
            system("pause");
        }


    }while(opcion != 0);
}
void submenuLogin1(int opcion,char archiUsuario[],char archiCliente[],char archiCajas[],int idUsuario,nodoArbol* arbol, caja arreglo[], int validos)
{
    do
    {
        system("cls");
        encabezadoPantallaAgrandada();
        EncuadrePrincipal();
        gotoxy(70,9);
        printf("1- Opciones de Mercado");
        gotoxy(70,11);
        printf("2- Opciones de Usuario");
        gotoxy(70,13);
        printf("3- Opciones de Clientes");
        gotoxy(70,15);
        printf("0- Volver al menu anterior");
        gotoxy(70,17);
        printf("Ingrese opcion: ");
        gotoxy(70,19);
        scanf("%d",&opcion);
        if(opcion < 4 && opcion > -1)
        {
        switch(opcion)
            {
            case 1:
                subMenuPrograma(opcion,archiUsuario,archiCliente, archiCajas, arbol, arreglo, validos);
                break;
            case 2:
                subMenuUsuarios(opcion,archiUsuario,archiCliente,archiCajas, idUsuario, arbol, arreglo, validos);
                break;
            case 3:
                subMenuClientes(opcion,archiUsuario,archiCliente,arbol,arreglo,validos);
                break;
            }
        }
        else
        {
            printf("Opcion incorrecta\n");
            system("pause");
        }
    }while(opcion != 0);
}
void subMenuPrograma(int opcion,char archiUsuario[],char archiCliente[], char archiCajas[], nodoArbol* arbol, caja arreglo[], int validos)
{
    nodo* nuevoCli = NULL;

    do
    {
        system("cls");
        encabezadoPantallaAgrandada();
        EncuadrePrincipal();
        gotoxy(70,8);
        printf("OPCIONES DEL MERCADO - RECUERDE RESPETAR EL ORDEN!!:");
        gotoxy(70,11);
        printf("1-Cargar Arbol");
        gotoxy(70,13);
        printf("2-Mostrar Arbol Pre Order");
        gotoxy(70,15);
        printf("3-Mostrar Arbol In Order");
        gotoxy(70,17);
        printf("4- Mostrar Arbol Post Order");
        gotoxy(70,19);
        printf("5- Cargar Cajas al Archivo");
        gotoxy(70,21);
        printf("6- Cargar Linea de Cajas");
        gotoxy(70,23);
        printf("7- Cargar Clientes Pre - Order");
        gotoxy(70,25);
        printf("8- Cargar Clientes In - Order");
        gotoxy(70,27);
        printf("9- Cargar Clientes Post - Order");
        gotoxy(70,29);
        printf("10- Abrir o Cerrar Caja");
        gotoxy(70,31);
        printf("11- Mostrar Linea de Cajas");
        gotoxy(70,33);
        printf("12- Agregar Cliente en tiempo determinado");
        gotoxy(70,35);
        printf("13- Cobrar todas las Cajas");
        gotoxy(70,37);
        printf("14- Cobrar una Caja especifica");
        gotoxy(70,39);
        printf("Ingrese opcion: ");
        gotoxy(70,41);
        scanf("%d",&opcion);
        if(opcion > -1 && opcion < 17)
        {
            switch(opcion)
            {
                case 1:

                    system("cls");
                    arbol = iniciaYcargaArbol(arbol,archiCliente);
                    system("pause");
                    break;

                case 2:

                    system("cls");
                    printf("\nA CONTINUACION MOSTRAMOS EL ARBOL EN MODO PRE ORDER: \n");
                    Preorder(arbol);
                    system("pause");
                    break;

                case 3:

                    system("cls");
                    printf("\nA CONTINUACION MOSTRAMOS EL ARBOL EN MODO IN ORDER: \n");
                    InOrder(arbol);
                    system("pause");
                    break;

                case 4:

                    system("cls");
                    printf("\nA CONTINUACION MOSTRAMOS EL ARBOL EN MODO POST ORDER: \n");
                    PostOrder(arbol);
                    system("pause");
                    break;


                case 5:

                    system("cls");
                    agregarCaja(archiCajas);
                    system("pause");
                    break;

                case 6:

                    system("cls");
                    validos = deArchivoAcaja(archiCajas,arreglo,validos);
                    system("pause");
                    break;

                case 7:

                    system("cls");
                    AgregarPreOrder(arbol,arreglo,validos);
                    system("pause");
                    break;

                 case 8:

                    system("cls");
                    AgregarInOrder(arbol,arreglo,validos);
                    system("pause");
                    break;

                case 9:

                    system("cls");
                    AgregarPostOrder(arbol,arreglo,validos);
                    system("pause");
                    break;

                case 10:
                    system("cls");
                    abrirOcerrarCaja(arreglo);//PROBAR FUNCIONAMIENTO
                    system("pause");
                    break;

                case 11:

                    system("cls");
                    mostrarLineaDeCajas(arreglo,validos);
                    system("pause");
                    break;

                case 12:
                    system("cls");
                    nuevoCli = cargaClienteNuevo(archiCliente);
                    system("pause");

                    break;
                case 13:
                    system("cls");
                    cobrarTodas(arreglo,validos,nuevoCli);
                    system("pause");
                    break;

                case 14:

                    system("cls");
                    cobrarUnaCaja(arreglo,validos,nuevoCli);

                    system("pause");
                    break;

            }
        }
        else
        {
            printf("Opcion incorrecta\n");
            system("pause");
        }
    }while(opcion != 0);
}

void subMenuUsuarios(int opcion,char archiUsuario[],char archiCliente[],char archiCajas[],int idUsuario,nodoArbol* arbol, caja arreglo[], int validos)
{
    do
    {
        system("cls");
        encabezadoPantallaAgrandada();
        EncuadrePrincipal();
        gotoxy(70,9);
        printf("1- Modificar Datos de Usuario");
        gotoxy(70,11);
        printf("2- Darse de baja");
        gotoxy(70,13);
        printf("0- Volver atras");
        gotoxy(70,15);
        printf("Ingrese opcion: ");
        gotoxy(0,28);
        scanf("%d",&opcion);
        if(opcion < 3 && opcion > -1)
        {
            switch(opcion)
            {
            case 1:
                subMenuModificaUsuario(opcion,archiUsuario,archiCajas, idUsuario);
                break;
            case 2:
                system("cls");
                bajaUsuario(archiUsuario,idUsuario); //FUNCION DE BAJA USUSARIO
                menuPrincipal(opcion,archiUsuario,archiCliente,archiCajas,arbol,arreglo,validos);//DESPUES DE ELIMINARSE VUELVE AL MENU PRINCIPAL
                system("pause");
                break;
            }
        }
        else
        {
            printf("Opcion incorrecta\n");
            system("pause");
        }

    }while(opcion != 0);
}
void subMenuModificaUsuario(int opcion,char archiUsuario[],char archiCajas[],int idUsuario)
{
    do
    {
        system("cls");
        encabezadoPantallaAgrandada();
        EncuadrePrincipal();
        gotoxy(70,9);
        printf("1- Modificar Nombre");
        gotoxy(70,11);
        printf("2- Modificar Apellido");
        gotoxy(70,13);
        printf("3- Modificar Nick de Usuario");
        gotoxy(70,15);
        printf("4- Modificar Pass");
        gotoxy(70,17);
        printf("0- Volver atras");
        gotoxy(70,19);
        printf("Ingrese opcion: ");
        gotoxy(0,28);
        scanf("%d",&opcion);
        if(opcion < 5 && opcion > -1)
        {
            switch(opcion)
            {
            case 1:
                system("cls");
                modificaNombre(archiUsuario,idUsuario);  //FUNCION MODIFICA NOMBRE
                //system("pause");
                break;
            case 2:
                system("cls");
                modificaApellido(archiUsuario,idUsuario);  //FUNCION MODIFICA APELLIDO
                //system("pause");
                break;
            case 3:
                system("cls");
                modificaUsuario(archiUsuario,idUsuario);  //FUNCION MODIFICA USUARIO
                //system("pause");
                break;
            case 4:
                system("cls");
                modificaClave(archiUsuario,idUsuario);    //FUNCION MODIFICA PASS
                //system("pause");
                break;
            }
        }
        else
        {
            printf("Opcion incorrecta\n");
            system("pause");
        }

    }while(opcion != 0);
}
void subMenuClientes(int opcion,char archiUsuario[],char archiCliente[],nodoArbol* arbol, caja arreglo[], int validos)
{
    do
    {
        system("cls");
        encabezadoPantallaAgrandada();
        EncuadrePrincipal();
        gotoxy(70,9);
        printf("1- Alta de Cliente");
        gotoxy(70,11);
        printf("2- Baja de Cliente");
        gotoxy(70,13);
        printf("3- Modificacion de Cliente");
        gotoxy(70,15);
        printf("0- Volver atras");
        gotoxy(70,17);
        printf("Ingrese opcion: ");
        gotoxy(0,28);
        scanf("%d",&opcion);
        if(opcion < 4 && opcion > -1)
        {
            switch(opcion)
            {
            case 1:
                system("cls");
                altaDeCliente(archiCliente);  //FUNCION ALTA CLIENTE
                system("pause");
                break;
            case 2:
                system("cls");
                bajaClientes(archiCliente); //FUNCION BAJA CLIENTE
                system("pause");
                break;
            case 3:
                subMenuModificaCliente(opcion,archiUsuario,archiCliente,arbol,arreglo,validos);
                break;
            }
        }
        else
        {
            printf("Opcion incorrecta\n");
            system("pause");
        }
    }while(opcion != 0);

}

void subMenuModificaCliente(int opcion,char archiUsuario[],char archiCliente[],nodoArbol* arbol, caja arreglo[], int validos)
{
    do
    {
        system("cls");
        encabezadoPantallaAgrandada();
        EncuadrePrincipal();
        gotoxy(70,9);
        printf("1- Modificar Apellido");
        gotoxy(70,11);
        printf("2- Modificar Nombre");
        gotoxy(70,13);
        printf("3- Modificar Tipo de Cliente (prioridad)");
        gotoxy(70,15);
        printf("4- Modificar medio de pago");
        gotoxy(70,17);
        printf("5- Modificar cantidad de articulos");
        gotoxy(70,19);
        printf("0- Volver atras");
        gotoxy(70,21);
        printf("Ingrese opcion: ");
        gotoxy(0,28);
        scanf("%d",&opcion);
        if(opcion < 5 && opcion > -1)
        {
            switch(opcion)
            {
            case 1:
                system("cls");
                modificaApellidoCliente(archiCliente); //FUNCION MODIFICA APELLIDO CLIENTE
                system("pause");
                break;
            case 2:
                system("cls");
                modificaNombreCliente(archiCliente); //FUNCION MOIFICA TIPO DE CLIENTE
                system("pause");
                break;
            case 3:
                system("cls");
                modificaTipoCliente(archiCliente); //FUNCION MOIFICA TIPO DE CLIENTE
                system("pause");
                break;
            case 4:
                system("cls");
                modificaMedioPago(archiCliente); //FUNCION MODIFICA MEDIO DE PAGO
                system("pause");
                break;
            case 5:
                system("cls");
                modificaCantArticulos(archiCliente);  // FUNCION MODIFICA CANTIDAD DE ARTICULOS
                system("pause");
                break;
            }
        }
        else
        {
            printf("Opcion incorrecta\n");
            system("pause");
        }
    }while(opcion != 0);
}

