#ifndef ABM_H_INCLUDED
#define ABM_H_INCLUDED


typedef struct {
       int id;
       char apellido[30];
       char nombre[40];
       int tipoCliente; // Prioridad 1:embarazada, 2:jubilado y 3:cliente común
       int medioPago; // 1:efectivo, 2:crédito y 3:todos
       int cantArticulos;// es el tiempo de ejecución
       int tiempoEspera; //no se ingresa por teclado (0 por defecto)/// es el tiempo de respuesta
       int tiempoProcesado;//no se ingresa por teclado (0 por defecto// es el tiempo que ya fue procesado en linea de caja
       int eliminado;
} persona;

int ingresoAlPrograma (char[]);
void altaUsuario (char[]);
int buscarultimoUsuario(char[]);            //FUNCIONES DE USUARIO
int buscaExistencia (char[],usuario);
int corroboraEstado(char[],int);
void bajaUsuario (char[],int);
void modificaNombre(char[],int);
void modificaApellido(char[],int);
void modificaUsuario(char[],int);
void modificaClave (char[],int);

void abreParaMostrarUsuario(char[]);
void mostrarUsuariosRecursivo(FILE*);
void imprimeBloqueUsuario(usuario);
void abreParaMostrarCliente(char[]);
void muestraClienteRecursivo(FILE*);
void imprimeBloqueCliente(persona);


void altaDeCliente (char[]);                 //FUNCIONES DE CLIENTE
int buscarultimoCliente(char[]);
int corroboraEstadoCliente(char[],int);
void bajaClientes(char[]);
void modificaApellidoCliente(char[]);
void modificaNombreCliente(char[]);
void modificaTipoCliente(char[]);
void modificaMedioPago(char[]);
void modificaCantArticulos(char[]);

int obtencion_id(char[],usuario);


#endif // ABM_H_INCLUDED
