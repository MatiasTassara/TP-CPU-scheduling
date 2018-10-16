#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libMatriz.h"
#include "abm.h"
#include "listas.h"
#include "fila.h"
#include "arbol.h"
#include "caja.h"
#include <windows.h>

void AgregarPreOrder(nodoArbol* arbol, caja arre[], int validos)
{
    if (arbol != NULL)
    {
        PasaPersona(arbol->consumidor, arre, validos);
        AgregarPreOrder(arbol->izq, arre, validos);
        AgregarPreOrder(arbol->der, arre, validos);
    }
}

void AgregarInOrder(nodoArbol* arbol, caja arre[], int validos)
{
    if (arbol != NULL)
    {
        AgregarInOrder(arbol->izq, arre, validos);
        PasaPersona(arbol->consumidor, arre, validos);
        AgregarInOrder(arbol->der, arre, validos);
    }
}
void AgregarPostOrder(nodoArbol* arbol, caja arre[], int validos)
{
    if (arbol != NULL)
    {
        AgregarPostOrder(arbol->izq, arre, validos);
        AgregarPostOrder(arbol->der, arre, validos);
        PasaPersona(arbol->consumidor, arre, validos);
    }
}

//LA SIGUIENTE FUNCION ES COMUN A LAS TRES ANTERIORES Y ES LA QUE CONTINUA EL TRABAJO DEL INGRESO DE LAS PERSONAS A LAS CAJAS

void PasaPersona(persona Comprador, caja arre[], int validos)
{
    int posicion = 0;



    posicion = EleccionDeCaja(Comprador, arre, validos);
    arre[posicion].filita.cabecera = insertarNuevoCliente(arre[posicion], Comprador);

    arre[posicion].filita.contador = (arre[posicion].filita.contador) + 1;
}
//LA SIGUIENTE FUNCION REEMPLAZA A BUSCAR CAJA (FUNCION SUGERIDA EN CONSIGNA)
int EleccionDeCaja(persona Comprador, caja arre[], int validos)
{
    int i = 0;
    int posmenor;
    int menor = 500;

    while (i < validos)
    {
        if(arre[i].tipo_pago == Comprador.medioPago)
        {
            if(arre[i].AbiertaOcerrada == 1)
            {
                if(arre[i].filita.contador < menor)
                {
                    menor = arre[i].filita.contador;
                    posmenor = i;
                }
            }
        }
        i++;
    }
    return posmenor;

}
void agregarCaja(char archiCajas[])
{
    caja aux;

    FILE * archi;
    archi = fopen(archiCajas, "ab");
    if(archi != NULL)
    {
        fseek(archi,0,SEEK_END);
        aux.nro_de_caja = (ftell(archi) / sizeof(caja)) +1;
        printf("\nINGRESE EL NOMBRE DE CAJERO: \n");
        fflush(stdin);
        gets(aux.NombreCajero);
        printf("\nINGRESE TIPO DE PAGO: \n");
        scanf("%d", &aux.tipo_pago);
        printf("\nINGRESE 0 CAJA CERRADA - 1 CAJA ABIERTA: \n");
        scanf("%d", &aux.AbiertaOcerrada);
        muestraAlgoritmos();
        printf("\nINGRESE ALGORITMO DE PLANIFICACION: \n");
        fflush(stdin);
        gets(aux.algoritmoPlanificacion);
        fwrite(&aux, sizeof(caja), 1, archi);

        fclose(archi);

    }

}

void abrirOcerrarCaja(caja Arre[])
{
    int i, estado;
    char control = 's';

    printf("\nINGRESE LA POSICION DE LA CAJA QUE DESEA MODIFICAR: ");
    scanf("%d", &i);
    estado = Arre[i-1].AbiertaOcerrada;

    if (estado == 0)
    {
        printf("LA CAJA ESTA CERRADA, DESEA ABRIRLA? (s/n): ");
        fflush(stdin);
        scanf("%c", &control);

        if (control == 's')
        {
            Arre[i-1].AbiertaOcerrada = 1;
        }
    }
    else
    {
        if(Arre[i-1].filita.contador != 0)
        {
            printf("\nLA CAJA AUN TIENE CLIENTES, NO SE PUEDE CERRAR.\n");
        }
        else
        {
            printf("\nDESEA CERRAR LA CAJA? (s/n): ");
            fflush(stdin);
            scanf("%c", &control);

            if (control == 's')
             {
                Arre[i-1].AbiertaOcerrada = 0;
             }
        }

    }
}
int buscaCaja(caja Arre[], int validos) //FUNCION QUE DEVUELVE LA POSICION DE LA CAJA, SI NO LA ENCUENTRA DEVUELVE -1
{
    int pago, i = 0, habilitada = 0, resultado;
    printf("\nINGRESE TIPO DE PAGO: 1- efvo, 2- cred, 3- todos: ");
    scanf("%d", &pago);

    while (i < validos && habilitada == 0)
    {
        if(Arre[i].tipo_pago == pago && Arre[i].AbiertaOcerrada == 1)
        {
            habilitada = 1;
        }
        else
        {
            i++;
        }
    }
    if (habilitada == 1)
    {
        resultado = i;
    }
    else
    {
        resultado = -1;
    }
    return resultado;
}
//FUNCION DE MOSTRAR CAJA Y FILA DE PERSONAS

void mostrarCaja(caja registradora) //RECIBE LA CAJA QUE SE DESEA MOSTRAR
{
    imprimirCaja(registradora);

    printf("\nEN ESTOS MOMENTOS LA CAJA TIENE LOS SIGUIENTES CLIENTES: \n");

    mostrarFila(&registradora.filita);

}
//FUNCION PARA AGREGAR CAJA, ABRE EL ARCHIVO Y PERMITE CARGAR TODAS LAS QUE SE DESEE
//LA FUNCION VA A MOSTRAR EL ARCHIVO DE CAJAS Y TE VA A PEDIR QUE INGRESES LOS NUMEROS DE CAJA QUE QUERES PASAR AL ARREGLO

int deArchivoAcaja(char archiCajas[], caja Arre[], int validos)
{
    int elegida;
    caja aux;
    char control = 's';
    FILE *archi;
    archi = fopen(archiCajas, "rb");
    if (archi != NULL)
    {
        mostrarArchivoCaja(archiCajas);
        while (control == 's')
        {
            printf("\nINGRESE LA CAJA QUE QUIERE CARGAR AL SISTEMA DE CAJAS: ");
            fflush(stdin);
            scanf("%d", &elegida);
            fseek(archi, sizeof (caja)*(elegida-1), SEEK_SET);
            fread(&aux, sizeof(caja), 1, archi);
            insertarCajaEnArreglo(Arre, aux, &validos);
            inicFila(&Arre[validos-1].filita);
            printf("\nDESEA CARGAR OTRA CAJA A LA LINEA DE CAJAS? (s/n): ");
            fflush(stdin);
            scanf("%c", &control);

        }
        fclose(archi);
    }
    return validos;


}
//ARMAR MOSTRAR ARCHIVO DE CAJA Y LA DE INSERTAR CAJA EN ARREGLO

void mostrarArchivoCaja(char archiCajas[])
{
    caja aux;
    FILE * archi;
    archi =fopen(archiCajas, "rb");
    if(archi != NULL)
    {
        while(fread(&aux, sizeof(caja), 1, archi) > 0)
        {
            imprimirCaja(aux);

        }
        fclose(archi);
    }
}
void imprimirCaja(caja registradora)
{
    printf("\n---------------------------------------------------------------------------------------------------\n");
    printf("\nNUMERO DE CAJA:                                %d", registradora.nro_de_caja);
    printf("\nNOMBRE DE CAJERO:                              %s", registradora.NombreCajero);
    printf("\nTIPO DE PAGO:                                  %d", registradora.tipo_pago);
    printf("\nESTADO DE CAJA (0 abierta, 1 cerrada):         %d", registradora.AbiertaOcerrada);
    printf("\nALGORITMO DE PLANIFICACION:                    %s", registradora.algoritmoPlanificacion);



}
void insertarCajaEnArreglo(caja Arre[],caja aux, int * validos)
{
    Arre[*validos] = aux;
    (*validos) = (*validos) + 1;
}

void mostrarLineaDeCajas(caja arreglo[],int validos)  //MUESTRA TODA LA LINEA DE CAJAS CON SUS CLIENTES
{
    int i;
    for(i = 0;i < validos;i++)
    {
        mostrarCaja(arreglo[i]);
    }
}

int buscaCajaEspecifica(caja arreglo[],int validos,int numCaja)
{
    int i = 0;
    while((i < validos) && (arreglo[i].nro_de_caja != numCaja))
    {
        i++;
    }
    if(i == validos)
    {
        i = -1;
    }
    return i;
}

int evaluarCaja(caja registradora,persona comprador)
{
    int rta = 0;

    if(registradora.tipo_pago == comprador.medioPago)
    {

        if(registradora.AbiertaOcerrada == 1)
        {
            rta = 1;
        }
    }

    return rta;
}

nodo* insertarNuevoCliente(caja registradora,persona comprador)
{
    nodo *nuevoNodo = NULL;
    char fifo[] = "fifo";
    char rr[] = "round robin";
    char pna[]= "prioridades no apropiativo";
    char pa[]= "prioridades apropiativo";
    char sjf[] = "sjf";
    char srtf[] = "srtf";

    if(strcmp(registradora.algoritmoPlanificacion,fifo) == 0 || strcmp(registradora.algoritmoPlanificacion,rr) == 0 )
    {
        nuevoNodo = crearNodo(comprador);
        agregar(&registradora.filita,nuevoNodo);

    }
    else if(strcmp(registradora.algoritmoPlanificacion,pna) == 0 || strcmp(registradora.algoritmoPlanificacion,pa) == 0)
    {
        agregarOrdenadoPrioridad(&registradora.filita,comprador);

    }

    else if(strcmp(registradora.algoritmoPlanificacion,sjf) == 0 || strcmp(registradora.algoritmoPlanificacion,srtf) == 0)
    {
        AgregarOrdenadoArticulos(&registradora.filita,comprador);

    }
    return registradora.filita.cabecera;
}
void muestraAlgoritmos()
{
    printf("----------------------------------------\n");
    printf("fifo\n");
    printf("round robin\n");
    printf("prioridades no apropiativo\n");
    printf("prioridades apropiativo\n");
    printf("sjf\n");
    printf("srtf\n");
    printf("\nESCRIBA EL NOMBRE DEL ALGORITMO TAL COMO\n SE ENCUENTRA EN LA LISTA Y EN MINUSCULAS\n");
    printf("----------------------------------------\n");
}


void impresionEstadisticas(int matrix[][20],int val)
{
    int i,j,acumRta = 0,acumEjec = 0;
    printf("\n******* ESTADISTICAS *******\n");
    for(j = 0; j < val; j++)
    {
        printf("-------------------------------\n");

        for(i = 0; i < 4; i++)
        {
            if(i == 0)
            {
                printf("ID de Cliente: %d\n",matrix[i][j]);
            }
            else if(i == 1)
            {
                printf("Tiempo de llegada del Cliente: %d\n",matrix[i][j]);
            }
            else if(i == 2)
            {
                printf("Tiempo de Respuesta: %d\n",matrix[i][j]);
                acumRta = acumRta + matrix[i][j];
            }
            else
            {
                printf("Tiempo de Ejecucion: %d\n",matrix[i][j]);
                acumEjec = acumEjec + matrix[i][j];
            }
        }
    }
    printf("\n-----------------------------------\n");
    printf("***********************************\n");
    printf("Tiempo medio de Respuesta: %d\n",acumRta / val);
    printf("Tiempo medio de Ejecucion: %d\n",acumEjec / val);
    printf("***********************************\n");
}
void FIFO(caja x,nodo *nuevoCliente,int tiempoNuevoCliente)
{
    int tiempo = 1;
    nodo *aux = NULL;
    nodo *residuo = NULL;
    int datos[4][20];
    int fil = 0,col = 0,cantidadColumnas = 0;
    int i = 0,tiempoEjecucion;
    aux = x.filita.cabecera;
    x.filita.cola = buscarUltimo(x.filita.cabecera);
    while(aux != NULL)
    {
        datos [fil][col] = aux->cliente.id;
        fil++;
        datos[fil][col] = 0;
        aux = aux->siguiente;
        col++;
        cantidadColumnas++;

        fil = 0;
    }
    if(tiempoNuevoCliente != -1)
    {
        datos[fil][col] = nuevoCliente->cliente.id;
        datos[1][col] = tiempoNuevoCliente;
        cantidadColumnas++;
    }
    printf("\n------------------------------------------------------------------------\n");
    printf("\nCAJA CON ALGORITMO FIFO: \n");
    printf("\n------------------------------------------------------------------------\n");
    while(!filaVacia(&x.filita))
    {
        aux = x.filita.cabecera;
        while(aux->cliente.tiempoProcesado < aux->cliente.cantArticulos)
        {
            if(tiempoNuevoCliente != -1)
            {
                if(tiempoNuevoCliente == tiempo)
                {
                    agregar(&x.filita,nuevoCliente);
                    x.filita.cola = nuevoCliente;
                }
            }
            aux = x.filita.cabecera;
            if(aux->cliente.tiempoProcesado == 0)
            {
                i = 0;
                while(i < cantidadColumnas && datos[0][i] != aux->cliente.id)
                {
                    i++;
                }
                datos[2][i] = tiempo - datos[1][i];
            }
            printf("\n------------------------");
            printf("\nId Cliente: [%d] ",aux->cliente.id);
            printf("\n-$$$-Cobrando Producto: %d",aux->cliente.tiempoProcesado+1);
            printf("\nApellido: %s\n",aux->cliente.apellido);
            tiempo++;
            aux->cliente.tiempoProcesado++;
            Sleep(300);
        }
        if(tiempoNuevoCliente != -1)
            {
                if(aux->cliente.id == nuevoCliente->cliente.id)
                {
                    tiempoEjecucion = tiempo - tiempoNuevoCliente;
                }
                else
                {
                    tiempoEjecucion = tiempo;
                }
            }
            else
            {
                tiempoEjecucion = tiempo;
            }

        i = 0;
        while(i < cantidadColumnas && datos[0][i] != aux->cliente.id)
        {
            i++;
        }
        datos[3][i] = tiempoEjecucion;

        residuo = quitar(&x.filita);
        free(residuo);
        aux = x.filita.cabecera;
    }

    impresionEstadisticas(datos,cantidadColumnas);
}


void ROUNDROBIN(caja x,nodo *nuevoCliente,int tiempoNuevoCliente)
{
    int tiempo = 1;
    nodo *aux = x.filita.cabecera;
    int datos[4][20];
    int fil = 0,col = 0,cantidadColumnas = 0;
    int i = 0,tiempoEjecucion;

    while(aux != NULL)
    {
        datos [fil][col] = aux->cliente.id;
        fil++;
        datos[fil][col] = 0;
        aux = aux->siguiente;
        col++;
        cantidadColumnas++;

        fil = 0;
    }
    if(tiempoNuevoCliente != -1)
    {
        datos[fil][col] = nuevoCliente->cliente.id;
        datos[1][col] = tiempoNuevoCliente;
        cantidadColumnas++;
    }
    int quantum = 5;
    int j = 0;
    nodo* auxCabecera;
    nodo* auxCola;
    nodo* ingresa;
    nodo *residuo;
    auxCabecera = x.filita.cabecera;
    auxCola = buscarUltimo(x.filita.cabecera);
    x.filita.cola = auxCola;
    printf("\n------------------------------------------------------------------------\n");
    printf("\nCAJA CON ALGORITMO ROUND ROBIN: \n");
    printf("\n------------------------------------------------------------------------\n");

    while (!filaVacia(&x.filita))
    {
        while ((auxCabecera->cliente.tiempoProcesado < auxCabecera->cliente.cantArticulos) && (j < quantum))
        {
            if(tiempoNuevoCliente != -1)
            {
                if(tiempoNuevoCliente == tiempo)
                {
                    agregar(&x.filita,nuevoCliente);
                    x.filita.cola = nuevoCliente;
                }
            }
            if(auxCabecera->cliente.tiempoProcesado == 0)
            {
                i = 0;
                while(i < cantidadColumnas && datos[0][i] != auxCabecera->cliente.id)
                {
                    i++;
                }
                datos[2][i] = tiempo - datos[1][i];
            }
            auxCabecera->cliente.tiempoProcesado++;
            printf("\n------------------------");
            printf("\nId Cliente: [%d] ", auxCabecera->cliente.id);
            printf("\n-$$$-Cobrando Producto: %d", auxCabecera->cliente.tiempoProcesado+1);
            printf("\nApellido: %s\n", auxCabecera->cliente.apellido);
            j++;
            tiempo++;
            Sleep(300);
        }
        if(auxCabecera->cliente.tiempoProcesado == auxCabecera->cliente.cantArticulos)
        {

           if(tiempoNuevoCliente != -1)
            {
                if(auxCabecera->cliente.id == nuevoCliente->cliente.id)
                {
                    tiempoEjecucion = tiempo - tiempoNuevoCliente;
                }
                else
                {
                    tiempoEjecucion = tiempo;
                }
            }
            else
            {
                tiempoEjecucion = tiempo;
            }

            i = 0;
            while(i < cantidadColumnas && datos[0][i] != auxCabecera->cliente.id)
            {
                i++;
            }
            datos[3][i] = tiempoEjecucion;

            auxCabecera = auxCabecera->siguiente;
            residuo = quitar(&x.filita);
            free(residuo);
        }
        else
        {
            if(auxCabecera == auxCola)
            {
                x.filita.cabecera = auxCabecera;
            }
            else
            {
                auxCabecera = auxCabecera->siguiente;
                auxCola = buscarUltimo(x.filita.cabecera);
                x.filita.cola = auxCola;
                ingresa = quitar(&x.filita);
                x.filita.cola = auxCola;
                agregar(&x.filita, ingresa);
                auxCola = ingresa;
                x.filita.cabecera = auxCabecera;
                x.filita.cola = auxCola;
            }
        }
        j = 0;
    }
    impresionEstadisticas(datos,cantidadColumnas);
}


void SRTF(caja x ,nodo* nuevoCliente,int tiempoNuevoCliente)
{
    int tiempo = 1;
    nodo *aux = NULL;
    nodo *residuo = NULL;
    int datos[4][20];
    int fil = 0,col = 0,cantidadColumnas = 0;
    int i = 0,tiempoEjecucion;
    aux = x.filita.cabecera;
    x.filita.cola = buscarUltimo(x.filita.cabecera);
    while(aux != NULL)
    {
        datos [fil][col] = aux->cliente.id;
        fil++;
        datos[fil][col] = 0;
        aux = aux->siguiente;
        col++;
        cantidadColumnas++;
        fil = 0;
    }
    if (tiempoNuevoCliente != -1)
        {
            datos[fil][col] = nuevoCliente->cliente.id;
            datos[1][col] = tiempoNuevoCliente;
            cantidadColumnas++;
        }


    printf("\n------------------------------------------------------------------------\n");
    printf("\nCAJA CON ALGORITMO SRTF: \n");
    printf("\n------------------------------------------------------------------------\n");
    while(!filaVacia(&x.filita))
    {
        aux = x.filita.cabecera;
        while(aux->cliente.tiempoProcesado < aux->cliente.cantArticulos)
        {
            if(tiempoNuevoCliente != -1)
            {
                if(tiempoNuevoCliente == tiempo)
                {
                    AgregarOrdenadoArticulos(&x.filita,nuevoCliente->cliente);
                    x.filita.cola = buscarUltimo(x.filita.cabecera);
                }
            }
            aux = x.filita.cabecera;
            if(aux->cliente.tiempoProcesado == 0)
            {
                i = 0;
                while(i < cantidadColumnas && datos[0][i] != aux->cliente.id)
                {
                    i++;
                }
                datos[2][i] = tiempo - datos[1][i];
            }
            printf("\n------------------------");
            printf("\nId Cliente: [%d] ",aux->cliente.id);
            printf("\n-$$$-Cobrando Producto: %d",aux->cliente.tiempoProcesado+1);
            printf("\nApellido: %s\n",aux->cliente.apellido);
            tiempo++;
            aux->cliente.tiempoProcesado++;
            Sleep(300);
        }
        if(tiempoNuevoCliente != -1)
        {
            if(aux->cliente.id == nuevoCliente->cliente.id)
            {
                tiempoEjecucion = tiempo - tiempoNuevoCliente;
            }
            else
            {
                tiempoEjecucion = tiempo;
            }
        }
        else
        {
            tiempoEjecucion = tiempo;
        }

        i = 0;
        while(i < cantidadColumnas && datos[0][i] != aux->cliente.id)
        {
            i++;
        }
        datos[3][i] = tiempoEjecucion;

        residuo = quitar(&x.filita);
        aux = x.filita.cabecera;
    }
    impresionEstadisticas(datos,cantidadColumnas);
}


void SJF(caja x, nodo *nuevoCliente,int tiempoNuevoCliente)
{
    int tiempo = 1;
    nodo *aux = NULL;
    nodo *residuo = NULL;
    int datos[4][20];

    int fil = 0,col = 0,cantidadColumnas = 0;
    int i = 0,tiempoEjecucion;

    aux = x.filita.cabecera;
    x.filita.cola = buscarUltimo(x.filita.cabecera);
    while(aux != NULL)
    {
        datos [fil][col] = aux->cliente.id;
        fil++;
        datos[fil][col] = 0;
        aux = aux->siguiente;
        col++;
        cantidadColumnas++;

        fil = 0;
    }
    if(tiempoNuevoCliente != -1)
    {
        datos[fil][col] = nuevoCliente->cliente.id;
        datos[1][col] = tiempoNuevoCliente;
        cantidadColumnas++;
    }
    printf("\n------------------------------------------------------------------------\n");
    printf("\nCAJA CON ALGORITMO SJF: \n");
    printf("\n------------------------------------------------------------------------\n");
    while(!filaVacia(&x.filita))
    {
        aux = x.filita.cabecera;
        while(aux->cliente.tiempoProcesado < aux->cliente.cantArticulos)
        {
            if(tiempoNuevoCliente != -1)
            {
                if(tiempoNuevoCliente == tiempo)
                {
                    x.filita.cabecera = aux->siguiente;
                    AgregarOrdenadoArticulos(&x.filita,nuevoCliente->cliente);
                    x.filita.cabecera = aux;
                    x.filita.cola = buscarUltimo(x.filita.cabecera);
                }
            }
            aux = x.filita.cabecera;
            if(aux->cliente.tiempoProcesado == 0)
            {
                i = 0;
                while(i < cantidadColumnas && datos[0][i] != aux->cliente.id)
                {
                    i++;
                }
                datos[2][i] = tiempo - datos[1][i];
            }
            printf("\n------------------------");
            printf("\nId Cliente: [%d] ",aux->cliente.id);
            printf("\n-$$$-Cobrando Producto: %d",aux->cliente.tiempoProcesado+1);
            printf("\nApellido: %s\n",aux->cliente.apellido);
            tiempo++;
            aux->cliente.tiempoProcesado++;
            Sleep(300);
        }
        if(tiempoNuevoCliente != -1)
        {
            if(aux->cliente.id == nuevoCliente->cliente.id)
            {
                tiempoEjecucion = tiempo - tiempoNuevoCliente;
            }
            else
            {
                tiempoEjecucion = tiempo;
            }
        }
        else
        {
            tiempoEjecucion = tiempo;
        }

        i = 0;
        while(i < cantidadColumnas && datos[0][i] != aux->cliente.id)
        {
            i++;
        }
        datos[3][i] = tiempoEjecucion;

        residuo = quitar(&x.filita);
        aux = x.filita.cabecera;
    }
    impresionEstadisticas(datos,cantidadColumnas);
}

void prioriadesApropiativo(caja x,nodo* nuevoCliente,int tiempoNuevoCliente)
{
    int tiempo = 1;
    nodo *aux = NULL;
    nodo *residuo = NULL;
    int datos[4][20];
    int fil = 0,col = 0,cantidadColumnas = 0;
    int i = 0,tiempoEjecucion;


    aux = x.filita.cabecera;
    x.filita.cola = buscarUltimo(x.filita.cabecera);
    while(aux != NULL)
    {
        datos [fil][col] = aux->cliente.id;
        fil++;
        datos[fil][col] = 0;
        aux = aux->siguiente;
        col++;
        cantidadColumnas++;

        fil = 0;
    }
    if(tiempoNuevoCliente != -1)
    {
        datos[fil][col] = nuevoCliente->cliente.id;
        datos[1][col] = tiempoNuevoCliente;
        cantidadColumnas++;
    }
    printf("\n------------------------------------------------------------------------\n");
    printf("\nCAJA CON ALGORITMO PRIORIDADES APROPIATIVO: \n");
    printf("\n------------------------------------------------------------------------\n");

    while(!filaVacia(&x.filita))
    {
        aux = x.filita.cabecera;
        while(aux->cliente.tiempoProcesado < aux->cliente.cantArticulos)
        {
            if(tiempoNuevoCliente != -1)
            {
                if(tiempoNuevoCliente == tiempo)
                {
                    agregarOrdenadoPrioridad(&x.filita,nuevoCliente->cliente);
                    x.filita.cola = buscarUltimo(x.filita.cabecera);
                }
            }
            aux = x.filita.cabecera;
            if(aux->cliente.tiempoProcesado == 0)
            {
                i = 0;
                while(i < cantidadColumnas && datos[0][i] != aux->cliente.id)
                {
                    i++;
                }
                datos[2][i] = tiempo - datos[1][i];
            }
            printf("\n------------------------");
            printf("\nId Cliente: [%d] ",aux->cliente.id);
            printf("\n-$$$-Cobrando Producto: %d",aux->cliente.tiempoProcesado+1);
            printf("\nApellido: %s\n",aux->cliente.apellido);
            tiempo++;
            aux->cliente.tiempoProcesado++;
            Sleep(300);
        }
        if(tiempoNuevoCliente != -1)
        {
            if(aux->cliente.id == nuevoCliente->cliente.id)
            {
                tiempoEjecucion = tiempo - tiempoNuevoCliente;
            }
            else
            {
                tiempoEjecucion = tiempo;
            }
        }
        else
        {
            tiempoEjecucion = tiempo;
        }
        i = 0;
        while(i < cantidadColumnas && datos[0][i] != aux->cliente.id)
        {
            i++;
        }
        datos[3][i] = tiempoEjecucion;

        residuo = quitar(&x.filita);
        aux = x.filita.cabecera;
    }
    impresionEstadisticas(datos,cantidadColumnas);

}


void prioridadesNoApropiativo(caja x,nodo*  nuevoCliente,int tiempoNuevoCliente)
{
    int tiempo = 1;
    nodo *aux = NULL;
    nodo *residuo = NULL;
    int datos[4][20];
    int fil = 0,col = 0,cantidadColumnas = 0;
    int i = 0,tiempoEjecucion;

     aux = x.filita.cabecera;
     x.filita.cola = buscarUltimo(x.filita.cabecera);
    while(aux != NULL)
    {
        datos [fil][col] = aux->cliente.id;
        fil++;
        datos[fil][col] = 0;
        aux = aux->siguiente;
        col++;
        cantidadColumnas++;

        fil = 0; //vuelve a la fila del id
    }
    if(tiempoNuevoCliente != -1)
    {
        datos[fil][col] = nuevoCliente->cliente.id;
        datos[1][col] = tiempoNuevoCliente;
        cantidadColumnas++;
    }
    printf("\n------------------------------------------------------------------------\n");
    printf("\nCAJA CON ALGORITMO PRIORIDADES NO APROPIATIVOS: \n");
    printf("\n------------------------------------------------------------------------\n");
    while(!filaVacia(&x.filita))
    {
        aux = x.filita.cabecera;
        while(aux->cliente.tiempoProcesado < aux->cliente.cantArticulos)
        {
            if(tiempoNuevoCliente != -1)
            {
                if(tiempoNuevoCliente == tiempo)
                {
                    x.filita.cabecera = aux->siguiente;
                    agregarOrdenadoPrioridad(&x.filita,nuevoCliente->cliente);
                    x.filita.cabecera = aux;
                    x.filita.cola = buscarUltimo(x.filita.cabecera);
                }
            }
            aux = x.filita.cabecera;
            if(aux->cliente.tiempoProcesado == 0)
            {
                i = 0;
                while(i < cantidadColumnas && datos[0][i] != aux->cliente.id)
                {
                    i++;
                }
                datos[2][i] = tiempo - datos[1][i];
            }
            printf("\n------------------------");
            printf("\nId Cliente: [%d] ",aux->cliente.id);
            printf("\n-$$$-Cobrando Producto: %d",aux->cliente.tiempoProcesado+1);
            printf("\nApellido: %s\n",aux->cliente.apellido);
            tiempo++;
            aux->cliente.tiempoProcesado++;
            Sleep(300);
        }
       if(tiempoNuevoCliente != -1)
        {
            if(aux->cliente.id == nuevoCliente->cliente.id)
            {
                tiempoEjecucion = tiempo - tiempoNuevoCliente;
            }
            else
            {
                tiempoEjecucion = tiempo;
            }
        }
        else
        {
            tiempoEjecucion = tiempo;
        }
        i = 0;
        while(i < cantidadColumnas && datos[0][i] != aux->cliente.id)
        {
            i++;
        }
        datos[3][i] = tiempoEjecucion;

        residuo = quitar(&x.filita);
        aux = x.filita.cabecera;

    }
    impresionEstadisticas(datos,cantidadColumnas);
}
void mostrarCajaEspecificada(caja arreglo[], int validos)
{
    int numero;
    int i = 0;
    printf("\nINGRESE EL NUMERO DE CAJA QUE DESEA VISUALIZAR: \n");
    scanf("%d", &numero);
    while (i < validos && arreglo[i].nro_de_caja != numero)
    {
        i++;
    }
    if (i!=validos)
    {
        mostrarCaja(arreglo[i]);
    }
    else
    {
        printf("\nCAJA NO EXISTENTE.");
    }
}


int agregarClienteAcaja(caja Arre[], int validos,nodo *comprador)
{
    int rta = 0, posicion, contador = 0, nro_caja;
    mostrarLineaDeCajas(Arre, validos);

    while (rta == 0 && contador < 3)
    {
        printf("\nINGRESE EL NUMERO DE CAJA DONDE QUIERE INSERTAR AL CLIENTE: ");
        fflush(stdin);
        scanf("%d", &nro_caja);
        posicion = buscaCajaEspecifica(Arre, validos, nro_caja);
        rta = evaluarCaja(Arre[posicion],comprador->cliente);

        if (rta == 0)
        {
            printf("\nLA CAJA NO ADMITE ESE TIPO DE PAGO O SE ENCUENTRA CERRADA.\n");

        }
        contador++;
    }
    if (rta != 1)
    {
        posicion = -1;
    }
    return posicion;
}

nodo* cargaClienteNuevo(char archicliente[])  //CARGA EL CLIENTE A ULTIMO MOMENTO
{

    FILE *archi;
    persona aux;
    altaDeCliente(archicliente);
    archi = fopen(archicliente,"rb");
    int identificacion;
    if(archi != NULL)
    {
        fseek(archi,0,SEEK_END);
        identificacion = ftell(archi) / sizeof(persona);
        fseek(archi,sizeof(persona) * (identificacion -1),SEEK_SET);
        fread(&aux,sizeof(persona),1,archi);
        fclose(archi);
    }
    nodo* resultado = crearNodo(aux);

    return resultado;
}
//-----------------------------------------------FUNCION GENERAL PARA LAS EJECUCIONES DE LAS CAJAS---------//
void cobrarTodas(caja arreglo[], int validos,nodo *aux)
{
    int tiempoIngreso = -1;
    int tiempoNulo = -1;
    int posicionDeCaja = -1;
    int i = 0;
    char fifo[] = "fifo";
    char rr[] = "round robin";
    char pna[]= "prioridades no apropiativo";
    char pa[]= "prioridades apropiativo";
    char sjf[] = "sjf";
    char srtf[] = "srtf";
    int comparacion;
    if(aux != NULL)
    {
        printf("En que tiempo desea ingresar el cliente nuevo?\n");
        fflush(stdin);
        scanf("%d",&tiempoIngreso);
        posicionDeCaja = agregarClienteAcaja(arreglo,validos,aux);
    }
    while(i < validos)
    {
        if(arreglo[i].AbiertaOcerrada == 1)
        {
            if(strcmp(arreglo[i].algoritmoPlanificacion,fifo) == 0)
            {
                if(i == posicionDeCaja)
                {
                    FIFO(arreglo[i],aux,tiempoIngreso);
                }
                else
                {
                    FIFO(arreglo[i],aux,tiempoNulo);
                }

            }
            else if(strcmp(arreglo[i].algoritmoPlanificacion,rr) == 0)
            {
                if (i == posicionDeCaja)
                {
                   ROUNDROBIN(arreglo[i], aux, tiempoIngreso);
                }
                else
                {
                    ROUNDROBIN(arreglo[i], aux, tiempoNulo);
                }

            }
            else if(strcmp(arreglo[i].algoritmoPlanificacion,pna) == 0)
            {
                if (i == posicionDeCaja)
                {
                   prioridadesNoApropiativo(arreglo[i],aux,tiempoIngreso);
                }
                else
                {
                    prioridadesNoApropiativo(arreglo[i],aux,tiempoNulo);
                }

            }
            else if(strcmp(arreglo[i].algoritmoPlanificacion,pa) == 0)
            {
                if (i == posicionDeCaja)
                {
                   prioriadesApropiativo(arreglo[i],aux,tiempoIngreso);
                }
                else
                {
                    prioriadesApropiativo(arreglo[i],aux,tiempoNulo);
                }

            }
            else if(strcmp(arreglo[i].algoritmoPlanificacion,sjf) == 0)
            {
                if (i == posicionDeCaja)
                {
                   SJF(arreglo[i],aux,tiempoIngreso);
                }
                else
                {
                    SJF(arreglo[i],aux,tiempoNulo);
                }

            }
            else if(strcmp(arreglo[i].algoritmoPlanificacion,srtf) == 0)
            {
                if (i == posicionDeCaja)
                {
                   SRTF(arreglo[i],aux,tiempoIngreso);
                }
                else
                {
                    SRTF(arreglo[i],aux,tiempoNulo);
                }

            }
        }
        i++;
    }


}
//FUNCION PARA COBRAR UNA SOLA CAJA TENIENDO EN CUENTA SI DESEA AGREGAR UN CLIENTE EN TIEMPO DETERMINADO//

void cobrarUnaCaja(caja arreglo[],int validos, nodo *aux)
{
    int tiempoIngreso = -1;
    int tiempoNulo = -1;
    int posicionDeCaja = -1;
    int i = 0, j;
    char fifo[] = "fifo";
    char rr[] = "round robin";
    char pna[]= "prioridades no apropiativo";
    char pa[]= "prioridades apropiativo";
    char sjf[] = "sjf";
    char srtf[] = "srtf";
    int comparacion;
    if(aux != NULL)
    {
        printf("En que tiempo desea ingresar el cliente nuevo?\n");
        fflush(stdin);
        scanf("%d",&tiempoIngreso);
        posicionDeCaja = agregarClienteAcaja(arreglo,validos,aux);
    }
    printf("\nINGRESE EL NUMERO DE CAJA QUE DESEA COBRAR: ");
    fflush(stdin);
    scanf("%d", &j);
    i = buscaCajaEspecifica(arreglo, validos, j);
    if(arreglo[i].AbiertaOcerrada == 1)
        {
            if(strcmp(arreglo[i].algoritmoPlanificacion,fifo) == 0)
            {
                if(i == posicionDeCaja)
                {
                    FIFO(arreglo[i],aux,tiempoIngreso);
                }
                else
                {
                    FIFO(arreglo[i],aux,tiempoNulo);
                }

            }
            else if(strcmp(arreglo[i].algoritmoPlanificacion,rr) == 0)
            {
                if (i == posicionDeCaja)
                {
                   ROUNDROBIN(arreglo[i], aux, tiempoIngreso);
                }
                else
                {
                    ROUNDROBIN(arreglo[i], aux, tiempoNulo);
                }

            }
            else if(strcmp(arreglo[i].algoritmoPlanificacion,pna) == 0)
            {
                if (i == posicionDeCaja)
                {
                   prioridadesNoApropiativo(arreglo[i],aux,tiempoIngreso);
                }
                else
                {
                    prioridadesNoApropiativo(arreglo[i],aux,tiempoNulo);
                }

            }
            else if(strcmp(arreglo[i].algoritmoPlanificacion,pa) == 0)
            {
                if (i == posicionDeCaja)
                {
                   prioriadesApropiativo(arreglo[i],aux,tiempoIngreso);
                }
                else
                {
                    prioriadesApropiativo(arreglo[i],aux,tiempoNulo);
                }

            }
            else if(strcmp(arreglo[i].algoritmoPlanificacion,sjf) == 0)
            {
                if (i == posicionDeCaja)
                {
                   SJF(arreglo[i],aux,tiempoIngreso);
                }
                else
                {
                    SJF(arreglo[i],aux,tiempoNulo);
                }

            }
            else if(strcmp(arreglo[i].algoritmoPlanificacion,srtf) == 0)
            {
                if (i == posicionDeCaja)
                {
                   SRTF(arreglo[i],aux,tiempoIngreso);
                }
                else
                {
                    SRTF(arreglo[i],aux,tiempoNulo);
                }

            }
        }

}

