#ifndef CAJA_H_INCLUDED
#define CAJA_H_INCLUDED

typedef struct caja
{
    int nro_de_caja;
    char NombreCajero[40];
    int tipo_pago; //1 efectivo, 2 credito, 3 todos
    int AbiertaOcerrada; // 1 abierta, 0 cerrada
    char algoritmoPlanificacion[30];
    Fila filita;
}caja;

//FUNCIONES COMPARTIDAS CON CAJA
void AgregarPreOrder(nodoArbol*, caja[], int);
void AgregarInOrder(nodoArbol*, caja[], int);
void AgregarPostOrder(nodoArbol*, caja[], int);

void PasaPersona(persona, caja[], int);
int EleccionDeCaja(persona, caja[], int);
void agregarCaja(char archiCajas[]);

 ////LIBRERIA CAJA
void abrirOcerrarCaja(caja[]);
int buscaCaja(caja[], int);
void mostrarCaja(caja);//MUESTRA CAJA CON FILA DE GENTE INCLUIDA
int deArchivoAcaja(char[], caja[], int);
void mostrarArchivoCaja(char[]);
void imprimirCaja(caja);
void insertarCajaEnArreglo(caja[],caja, int*);
int agregarClienteAcaja(caja[], int,nodo *);
nodo* cargaClienteNuevo(char[]);
void mostrarLineaDeCajas(caja[],int);
int buscaCajaEspecifica(caja[],int,int);
int evaluarCaja(caja,persona);
void muestraAlgoritmos();
nodo* insertarNuevoCliente(caja,persona);
void FIFO(caja,nodo *,int);
void ROUNDROBIN(caja,nodo *,int);
void impresionEstadisticas(int matrix[][20],int val);
void SJF(caja, nodo *,int);
void prioriadesApropiativo(caja,nodo*,int);
void prioridadesNoApropiativo(caja ,nodo*,int);
void mostrarCajaEspecificada(caja[], int);
void cobrarTodas(caja arreglo[], int,nodo *);
void cobrarUnaCaja(caja[],int, nodo *);



#endif // CAJA_H_INCLUDED
