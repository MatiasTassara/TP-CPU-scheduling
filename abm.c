#include "libMatriz.h"
#include <stdio.h>
#include <stdlib.h>             ////CUANDO EL USUARIO SE DA DE BAJA QUE LO SAQUE DEL SISTEMA
#include <string.h>
#include "abm.h"

void altaUsuario (char archiUsuario[])
{
    usuario nuevoUsuario;
    int verificacion = 1;
    char password [11];
    //char clave [11];

    FILE *newUser;
    newUser = fopen(archiUsuario, "ab");
    if (newUser != NULL)
    {
        nuevoUsuario.id = buscarultimoUsuario(archiUsuario);
        printf("Ingrese nombre\n");
        fflush(stdin);
        gets(nuevoUsuario.nombre);
        printf("Ingrese apellido\n");
        fflush(stdin);
        gets(nuevoUsuario.apellido);
        printf("\nIngrese un nombre de usuario (nick): \n");
        fflush(stdin);
        gets(nuevoUsuario.usuario);
        verificacion = buscaExistencia(archiUsuario, nuevoUsuario); //ESTA FUNCION SE FIJA SI ESE NOMBRE DE USUARIO YA EXISTE.
        while (verificacion == 0)
        {
            printf("\nNOMBRE DE USUARIO NO DISPONIBLE. Ingrese uno nuevo: \n");
            fflush(stdin);
            gets(nuevoUsuario.usuario);
            verificacion = buscaExistencia(archiUsuario, nuevoUsuario);
        }
            printf("\n");
            printf("\nINGRESE SU CLAVE DE SEGURIDAD DE 10 CARACTERES: \n");
            fflush(stdin);
            gets (password);
            //password[10] = '\0';
            EncriptaClave (password, nuevoUsuario.pass);
            nuevoUsuario.eliminado = 1;

            fwrite(&nuevoUsuario,sizeof(usuario),1,newUser);
            fclose(newUser);
      }
        else
      {
            printf("\nERROR EN EL ARCHIVO DE USUARIOS.\n");
      }
      printf("\nFELICITACIONES, USTED HA SIDO DE ALTA COMO USUARIO.\n");
}

//CUENTA CANTIDAD DE USUARIOS CARGADOS Y RETORNA EL ID PARA EL USUARIO
int buscarultimoUsuario(char archiUsuario[])
{
    int cant = 0;
    FILE * ultimoID;
    ultimoID = fopen(archiUsuario, "rb");

    if (ultimoID == NULL)
    {
        puts("Error al asignar ID\n");
    }
    else
    {
        fseek(ultimoID,0,SEEK_END);
        cant = ftell(ultimoID)/sizeof(usuario);
        cant++;                 // asigna uno mas que el numero de archivo, ejemplo al 0 le asigna 1,
        fclose(ultimoID);
    }
    return cant;
}

//FUNCION QUE COMPRUEBA SI EL USUARIO YA EXISTE
//SI RESPUESTA ES IGUAL A 0 EL USUARIO EXISTE, SI ES DISTINTO A 0, NO EXISTE
int buscaExistencia (char archiUsuario[],usuario aux)
{
  int respuesta = 1;
  usuario x;
  FILE * ptr;
  ptr = fopen(archiUsuario,"rb");
  if (ptr == NULL)
    {
        printf("\nError al abrir el archivo!!!(funcion busca existencia).\n");
    }
  else
    {
        while ((fread(&x, sizeof(usuario),1,ptr) > 0) && respuesta != 0)
        {
            respuesta = strcmp(x.usuario,aux.usuario);
        }
        fclose(ptr);
    }
   return respuesta;
}
// -------------FUNCIONES PARA DAR DE BAJA UN USUARIO----------------------
//-------------------------------------------------------------------------

//ESTA FUNCION CHEKEA SI EL USUARIO ESTÁ ACTIVO PARA PODER ACCEDER A LAS TAREAS DE MODIFICACION.
int corroboraEstado(char archiUsuario[],int identificacion)
{
    int estado;
    usuario estaOnoEsta;
    FILE * archi;
    archi = fopen(archiUsuario, "rb");
    if (archi != NULL)
    {
        fseek(archi, sizeof (usuario) * (identificacion -1),SEEK_SET);
        fread(&estaOnoEsta, sizeof (usuario),1,archi);
        if (estaOnoEsta.eliminado == 1)
        {
            estado = 1;
        }
        else
        {
            estado = 0;
        }
        fclose(archi);
    }
    return estado;
}
void bajaUsuario (char archiUsuario[],int ident)
{
    FILE * punt;
    usuario a;
    int estado;
    char seguir = 'n';
    punt = fopen(archiUsuario,"r+b");
    if(punt == NULL)
    {
        puts("Error al abrir el archivo!!!\n");
    }
    else
    {
        estado = corroboraEstado(archiUsuario,ident);
        if(estado == 0)
        {
            puts("Este usuario fue dado de baja o no existe\n");
        }
        else
        {
            fseek(punt,sizeof(usuario) * (ident - 1),SEEK_SET);
            fread(&a,sizeof(usuario),1,punt);
            puts("Esta seguro que desea darse de baja? s:'si',n:'no'\n");
            fflush(stdin);
            scanf("%c",&seguir);
            if(seguir == 's')
            {
                a.eliminado = 0;
                fseek(punt,sizeof(usuario) * (ident - 1),SEEK_SET);
                fwrite(&a, sizeof(usuario), 1,punt);
                puts("Usted ha sido dado de baja del sistema.\n");
            }
            else
            {
                printf("Usted se ha arrepentido, no me haga trabajar de gusto!!!.\n");
            }

        }
        fclose(punt);

    }
}
//-------------FUNCIONES DE MODIFICACION DE USUARIOS-------------------
//---------------------------------------------------------------------
void modificaNombre(char archiUsuario[],int identificacion)
{
    char nuevo [30];
    printf("\nIngrese su nuevo nombre: \n");
    fflush(stdin);
    gets(nuevo);

    usuario aux;
    FILE * modifnom;
    modifnom = fopen (archiUsuario, "r+b");
    if (modifnom != NULL)
    {
        fseek(modifnom, sizeof (usuario) * (identificacion-1),SEEK_SET);
        fread(&aux, sizeof(usuario), 1,modifnom);
        strcpy(aux.nombre, nuevo);
        fseek(modifnom, sizeof (usuario) * (identificacion-1),SEEK_SET);
        fwrite(&aux, sizeof (usuario), 1,modifnom);
        fclose(modifnom);
        printf("Modificacion realizada con exito!\n");
        system("pause");
    }
}
void modificaApellido(char archiUsuario[],int identificacion)
{
    char nuevo [30];
    printf("\nIngrese su nuevo apellido: \n");
    fflush(stdin);
    gets(nuevo);

    usuario aux;
    FILE * modifApe;
    modifApe = fopen (archiUsuario, "r+b");
    if (modifApe != NULL)
    {
        fseek(modifApe, sizeof (usuario) * (identificacion-1),SEEK_SET);
        fread(&aux, sizeof(usuario), 1,modifApe);
        strcpy(aux.apellido, nuevo);
        fseek(modifApe, sizeof (usuario) * (identificacion-1),SEEK_SET);
        fwrite(&aux, sizeof (usuario), 1,modifApe);
        fclose(modifApe);
        printf("Modificacion realizada con exito!\n");
        system("pause");
    }
}
void modificaUsuario(char archiUsuario[],int identificacion)
{
    int verificacion;
    usuario aux,aux2;
    FILE *fusuario;
    fusuario = fopen(archiUsuario,"r+b");
    if (fusuario != NULL)
    {
        printf("\nIngrese un nuevo nombre de usuario: \n");
        fflush(stdin);
        gets(aux2.usuario);
        verificacion = buscaExistencia(archiUsuario,aux2);
        while (verificacion == 0)
        {
            printf("\nNOMBRE DE USUARIO NO DISPONIBLE. Ingrese uno nuevo: \n");
            fflush(stdin);
            gets(aux2.usuario);
            verificacion = buscaExistencia(archiUsuario,aux2);
        }
        fseek(fusuario, sizeof (usuario) * (identificacion -1),SEEK_SET);//PARTE MODIFICADA CHEQUEAR DESPUES
        fread(&aux,sizeof(usuario),1,fusuario);
        strcpy(aux.usuario,aux2.usuario);
        fseek(fusuario, sizeof (usuario) * (identificacion -1),SEEK_SET);
        fwrite(&aux, sizeof(usuario), 1,fusuario);
        fclose(fusuario);
    }
}
void modificaClave (char archiUsuario[],int identificacion)
{
    char nueva[11];
    usuario aModificar;
    printf("\nIngrese su nueva clave: \n");
    fflush(stdin);
    gets(nueva);
    FILE * archi;
    archi = fopen(archiUsuario, "r+b");
    if (archi != NULL)
    {
        fseek(archi, sizeof(usuario) * (identificacion-1), 0);
        fread(&aModificar,sizeof(usuario), 1, archi);
        EncriptaClave (nueva,aModificar.pass);
        fseek(archi, sizeof(usuario) * (identificacion-1), 0);
        fwrite(&aModificar, sizeof(usuario), 1, archi);
        fclose(archi);

    }
}
//-------------- FUNCIONES ALTA DE CLIENTES -------------------------------
//-------------------------------------------------------------------------
void altaDeCliente (char archiCliente[])
{
    persona nuevoCliente;
    FILE *newClient;
    newClient = fopen(archiCliente, "ab");
    if (newClient != NULL)
    {
        nuevoCliente.id = buscarultimoCliente(archiCliente);
        printf("Ingrese apellido\n");
        fflush(stdin);
        gets(nuevoCliente.apellido);
        printf("Ingrese nombre\n");
        fflush(stdin);
        gets(nuevoCliente.nombre);
        printf("\nIngrese tipo de cliente:\n1-Embarazada\n2-Jubilado\n3-Cliente comun\n");
        fflush(stdin);
        scanf("%d",&nuevoCliente.tipoCliente);
        while(nuevoCliente.tipoCliente < 1 && nuevoCliente.tipoCliente > 3)
        {
            printf("Tipo de cliente incorrecto, vuelva a ingresar tipo de cliente\n");
            printf("1-Embarazada\n2-Jubilado\n3-Cliente comun\n");
            fflush(stdin);
            scanf("%d",&nuevoCliente.tipoCliente);
        }
        printf("\nIngrese medio de pago:\n1-Efectivo\n2-Credito\n3-Todos\n");
        fflush(stdin);
        scanf("%d",&nuevoCliente.medioPago);
        while(nuevoCliente.medioPago < 1 && nuevoCliente.medioPago > 3)
        {
            printf("Medio de pago incorrecto, vuelva a ingresar un medio de pago\n");
            printf("1-Efectivo\n2-Credito\n3-Todos\n");
            fflush(stdin);
            scanf("%d",&nuevoCliente.medioPago);

        }
        printf("Ingrese cantidad de articulos:\n");
        scanf("%d",&nuevoCliente.cantArticulos);
        while(nuevoCliente.cantArticulos < 1)
        {
            printf("La cantidad de articulos debe ser un numero mayor a 0, vuelva a ingresar\n");
            fflush(stdin);
            scanf("%d",&nuevoCliente.cantArticulos);
        }
        nuevoCliente.tiempoEspera = 0;
        nuevoCliente.tiempoProcesado = 0;
        nuevoCliente.eliminado = 1;
        fwrite(&nuevoCliente,sizeof(persona),1,newClient);
        fclose(newClient);
      }
        else
      {
            printf("\nERROR EN EL ARCHIVO DE CLIENTES!!!.\n");
      }
      printf("\nCLIENTE DADO DE ALTA CON EXITO!.\n");
}

//------------- MODIFICACION Y BAJA DE CLIENTES -------------------------------
//-----------------------------------------------------------------------------
void bajaClientes(char archiCliente[])
{
    FILE *baja;
    persona a;
    int ident,validacion;
    char seguir = 'n';
    baja = fopen(archiCliente,"r+b");
    if(baja == NULL)
    {
        puts("Error al abrir el archivo!!!\n");
    }
    else
    {
        printf("Ingrese el ID del Cliente que quiere dar de baja: ");
        fflush(stdin);
        scanf("%d",&ident);
        validacion = corroboraEstadoCliente(archiCliente,ident);
        while(validacion != 1)
        {
            printf("Este Cliente no existe o ya fue dado de baja\n");
            printf("Ingrese un ID valido\n");
            fflush(stdin);
            scanf("%d",&ident);
            validacion = corroboraEstadoCliente(archiCliente,ident);
        }
        fseek(baja,sizeof(persona) * (ident - 1),SEEK_SET);
        fread(&a,sizeof(persona),1,baja);
        puts("Esta seguro que desea darse de baja? s:'si',n:'no'\n");
        fflush(stdin);
        scanf("%c",&seguir);
        if(seguir == 's')
        {
            a.eliminado = 0;
            fseek(baja,sizeof(persona) * (ident - 1),SEEK_SET);
            fwrite(&a, sizeof(persona), 1,baja);
            puts("El cliente fue dado de baja del sistema.\n");
        }
        else
        {
            printf("Usted se ha arrepentido, no me haga trabajar de gusto!!!.\n");
        }


        fclose(baja);
    }
}
//FUNCION PARA ASIGNAR EL ID
int buscarultimoCliente(char archiCliente[])
{
    int cant = 0;
    FILE * ultimoID;
    ultimoID = fopen(archiCliente, "rb");

    if (ultimoID == NULL)
    {
        puts("Error al asignar ID.\n");
    }
    else
    {
        fseek(ultimoID,0,SEEK_END);
        cant = ftell(ultimoID)/sizeof(persona);
        cant++;                 // asigna uno mas que el numero de archivo, ejemplo al 0 le asigna 1,
        fclose(ultimoID);
    }
    return cant;
}
int corroboraEstadoCliente(char archiCliente[],int identificacion)
{
    int estado = 0;
    persona estaOnoEsta;
    FILE * archi;
    archi = fopen(archiCliente, "rb");
    if (archi != NULL)
    {
        fseek(archi, sizeof (persona) * (identificacion -1),SEEK_SET);
        fread(&estaOnoEsta, sizeof(persona),1,archi);
        if (estaOnoEsta.eliminado == 1)
        {
            estado = 1;
        }
        else
        {
            estado = 0;
        }
        fclose(archi);

    }
    return estado;
}
void modificaApellidoCliente(char archiCliente[])
{
    char nuevo [30];
    int identificacion;
    int validacion;

    printf("Ingrese el ID del Cliente que quiere modificar: ");
    fflush(stdin);
    scanf("%d",&identificacion);
    validacion = corroboraEstadoCliente(archiCliente,identificacion);
    while(validacion != 1)
    {
        printf("Este Cliente no existe o ya fue dado de baja\n");
        printf("Ingrese un ID valido\n");
        fflush(stdin);
        scanf("%d",&identificacion);
        validacion = corroboraEstadoCliente(archiCliente,identificacion);
    }
    printf("\nIngrese su nuevo apellido: \n");
    fflush(stdin);
    gets(nuevo);

    persona aux;
    FILE * modifApe;
    modifApe = fopen (archiCliente, "r+b");
    if (modifApe != NULL)
    {
        fseek(modifApe, sizeof (persona) * (identificacion-1),SEEK_SET);
        fread(&aux, sizeof(persona), 1,modifApe);
        strcpy(aux.apellido, nuevo);
        fseek(modifApe, sizeof (persona) * (identificacion-1),SEEK_SET);
        fwrite(&aux, sizeof (persona), 1,modifApe);
        fclose(modifApe);
        printf("Modificacion realizada con exito!\n");
        system("pause");
    }
    else
    {
        printf("No se pudo realizar la modificacion.\n");
    }
}

void modificaNombreCliente(char archiCliente[])
{
    char nuevo [30];
    int identificacion;
    int validacion;

    printf("Ingrese el ID del Cliente que quiere modificar: ");
    fflush(stdin);
    scanf("%d",&identificacion);
    validacion = corroboraEstadoCliente(archiCliente,identificacion);
    while(validacion != 1)
    {
        printf("Este Cliente no existe o ya fue dado de baja\n");
        printf("Ingrese un ID valido\n");
        fflush(stdin);
        scanf("%d",&identificacion);
        validacion = corroboraEstadoCliente(archiCliente,identificacion);
    }
    printf("\nIngrese su nuevo nombre: \n");
    fflush(stdin);
    gets(nuevo);

    persona aux;
    FILE * modifnomb;
    modifnomb = fopen (archiCliente, "r+b");
    if (modifnomb != NULL)
    {
        fseek(modifnomb, sizeof (persona) * (identificacion-1),SEEK_SET);
        fread(&aux, sizeof(persona), 1,modifnomb);
        strcpy(aux.nombre, nuevo);
        fseek(modifnomb, sizeof (persona) * (identificacion-1),SEEK_SET);
        fwrite(&aux, sizeof (persona), 1,modifnomb);
        fclose(modifnomb);
        printf("Modificacion realizada con exito!\n");
        system("pause");
    }
    else
    {
        printf("No se pudo realizar la modificacion.\n");
    }
}
void modificaTipoCliente(char archiCliente[])
{
    int tipo;
    int identificacion;
    int validacion;

    printf("Ingrese el ID del Cliente que quiere modificar: ");
    fflush(stdin);
    scanf("%d",&identificacion);
    validacion = corroboraEstadoCliente(archiCliente,identificacion);
    while(validacion != 1)
    {
        printf("Este Cliente no existe o ya fue dado de baja\n");
        printf("Ingrese un ID valido\n");
        fflush(stdin);
        scanf("%d",&identificacion);
        validacion = corroboraEstadoCliente(archiCliente,identificacion);
    }
    printf("\nIngrese nuevo tipo de cliente\n1-Embarazada\n2-Jubilado\n3-Cliente comun\n");
    fflush(stdin);
    scanf("%d",&tipo);
    while(tipo < 1 && tipo > 3)
    {
        printf("Tipo de cliente incorrecto, vuelva a ingresar\n");
        printf("1-Embarazada\n2-Jubilado\n3-Cliente comun\n");
        scanf("%d",&tipo);
    }
    persona aux;
    FILE * modifTipo;
    modifTipo = fopen (archiCliente, "r+b");
    if (modifTipo != NULL)
    {
        fseek(modifTipo, sizeof (persona) * (identificacion-1),SEEK_SET);
        fread(&aux, sizeof(persona), 1,modifTipo);
        aux.tipoCliente = tipo;
        fseek(modifTipo, sizeof (persona) * (identificacion-1),SEEK_SET);
        fwrite(&aux, sizeof (persona), 1,modifTipo);
        fclose(modifTipo);
        printf("Modificacion realizada con exito!\n");
        system("pause");
    }
    else
    {
        printf("No se pudo realizar la modificacion.\n");
    }
}
void modificaMedioPago(char archiCliente[])
{
    int medio;
    int identificacion;
    int validacion;

    printf("Ingrese el ID del Cliente que quiere modificar: ");
    fflush(stdin);
    scanf("%d",&identificacion);
    validacion = corroboraEstadoCliente(archiCliente,identificacion);
    while(validacion != 1)
    {
        printf("Este Cliente no existe o ya fue dado de baja\n");
        printf("Ingrese un ID valido\n");
        fflush(stdin);
        scanf("%d",&identificacion);
        validacion = corroboraEstadoCliente(archiCliente,identificacion);
    }
    printf("Ingrese nuevo medio de pago:\n1-Efectivo\n2-Credito\n3-Todos\n");
    fflush(stdin);
    scanf("%d",&medio);
    while(medio < 1 && medio > 3)
    {
        printf("Medio de pago incorrecto, vuelva a ingresar\n");
        printf("1-Efectivo\n2-Credito\n3-Todos\n");
        fflush(stdin);
        scanf("%d",&medio);
    }
    persona aux;
    FILE * modifMedio;
    modifMedio = fopen (archiCliente, "r+b");
    if (modifMedio != NULL)
    {
        fseek(modifMedio, sizeof (persona) * (identificacion-1),SEEK_SET);
        fread(&aux, sizeof(persona), 1,modifMedio);
        aux.medioPago = medio;
        fseek(modifMedio, sizeof (persona) * (identificacion-1),SEEK_SET);
        fwrite(&aux, sizeof (persona), 1,modifMedio);
        fclose(modifMedio);
        printf("Modificacion realizada con exito!\n");
        system("pause");
    }
    else
    {
        printf("No se pudo realizar la modificacion.\n");
    }
}
void modificaCantArticulos(char archiCliente[])
{
    int cant;
    int identificacion;
    int validacion;

    printf("Ingrese el ID del Cliente que quiere modificar: ");
    fflush(stdin);
    scanf("%d",&identificacion);
    validacion = corroboraEstadoCliente(archiCliente,identificacion);
    while(validacion != 1)
    {
        printf("Este Cliente no existe o ya fue dado de baja\n");
        printf("Ingrese un ID valido\n");
        fflush(stdin);
        scanf("%d",&identificacion);
        validacion = corroboraEstadoCliente(archiCliente,identificacion);
    }
    printf("Ingrese nueva cantidad de articulos\n");
    fflush(stdin);
    scanf("%d",&cant);
    while(cant < 1)
    {
        printf("La cantidad de articulos debe ser un numero mayor a 0, vuelva a ingresar\n");
        fflush(stdin);
        scanf("%d",&cant);
    }
    persona aux;
    FILE * modifCant;
    modifCant = fopen (archiCliente, "r+b");
    if (modifCant != NULL)
    {
        fseek(modifCant, sizeof (persona) * (identificacion-1),SEEK_SET);
        fread(&aux, sizeof(persona), 1,modifCant);
        aux.cantArticulos = cant;
        fseek(modifCant, sizeof (persona) * (identificacion-1),SEEK_SET);
        fwrite(&aux, sizeof (persona), 1,modifCant);
        fclose(modifCant);
        printf("Modificacion realizada con exito!\n");
        system("pause");
    }
    else
    {
        printf("No se pudo realizar la modificacion.\n");
    }
}
//---------FUNCION QUE RECIBE EL NOMBRE DE USUARIO Y DEVUELVE SU ID --------------
//--------------------------------------------------------------------------------
int buscaIdPorUsuario(char archiUsuario[],char usu[])
{
    usuario aux;
    FILE *fp;
    int id;
    fp = fopen(archiUsuario,"rb");
    if(fp == NULL)
    {
        printf("Error al abrir el archivo\n");
    }
    else
    {
        fread(&aux,sizeof(usuario),1,fp);
        while(strcmp(aux.usuario,usu) != 0)
        {
            fread(&aux,sizeof(usuario),1,fp);
        }
        id = aux.id;
    }
    return id;
}
int ingresoAlPrograma (char archiUsuario[]) //devuelve el id del que ingreso al sistema
{
    usuario ingresante;
    int contador = 0;
    int verifica;
    char password [11];        ////////FIJARSE SI EL CAMPO ELIMINADO ES 0 NO DEJAR ENTRAR/////
    char clave [11];
    int ident;
    int respuesta;



    printf("\nINGRESE SU NOMBRE DE USUARIO: \n");
    fflush(stdin);
    gets(ingresante.usuario);

    verifica = buscaExistencia(archiUsuario,ingresante);
    while(verifica != 0)
    {
        printf("\nUSUARIO INEXISTENTE, INGRESE UN USUARIO VALIDO: \n");
        fflush(stdin);
        gets(ingresante.usuario);
        verifica = buscaExistencia(archiUsuario,ingresante);
    }
    if (verifica == 0)
    {


        ident = obtencion_id(archiUsuario,ingresante);
        strcpy (clave, Busca_Y_Desencripta(ident,archiUsuario));
        //printf("\nClave : id%d  %s",ident,clave);




        printf("\nINGRESE PASSWORD: \n");
        fflush(stdin);
        gets(password);
        respuesta = strcmp(clave,password);

        while (respuesta != 0 && contador <3)
        {
            printf("\nClave Incorrecta.\n");
            printf("\nIngrese su Clave Privada: \n");
            fflush(stdin);
            gets(password);
            respuesta = strcmp(clave,password);
            contador++;
        }
        contador = 0;

            printf("\nBIENVENIDOS AL MINISUPER!!!\n");
            system("pause");


    }
    else
    {
        printf("\nNOMBRE DE USUARIO INEXISTENTE.\n");
    }
    return ident;
}
int obtencion_id(char archiUsuario[],usuario unUsuario)
{
    int respuesta = 854;
    int identificacion;
    usuario aux;
    FILE *archi;
    archi = fopen(archiUsuario, "rb");
    if (archi != NULL)
    {

        while (respuesta != 0 &&fread(&aux, sizeof(usuario), 1, archi)>0)
        {
                respuesta = strcmp(aux.usuario,unUsuario.usuario);
                //printf("\n[%s]%d\n - %s %d\n",aux.usuario,aux.id,unUsuario.usuario,unUsuario.id);
             //printf("respuesta: %d\n",respuesta);
            if (respuesta == 0)
            {
                identificacion = aux.id;
                //printf("identificacion[%d]\n",identificacion);
            }
        }

        fclose(archi);
    }
    return identificacion;
}




//////////////  MOSTRAR ARCHIVO DE USUARIO  /////////////////////////////////
void abreParaMostrarUsuario(char archiUsuario[])
{
    FILE *rec;
    rec = fopen(archiUsuario,"rb");
    if(rec == NULL)
    {
        printf("Error al abrir el archivo!!!(imprimir usuario)\n");
    }
    else
    {
        printf("\nCONTENIDO DEL ARCHIVO DE USUARIOS:\n");
        mostrarUsuariosRecursivo(rec);
        fclose(rec);
    }
}
void mostrarUsuariosRecursivo(FILE *p)
{
    usuario aux;
    if(fread(&aux,sizeof(usuario),1,p) > 0)
    {
        imprimeBloqueUsuario(aux);
        mostrarUsuariosRecursivo(p);
    }
}
void imprimeBloqueUsuario(usuario a)
{
    int i,j;
    printf("---------------------------------\n");
    printf("ID Usuario:      %d\n",a.id);
    printf("Nombre:          %s\n",a.nombre);
    printf("Apellido:        %s\n",a.apellido);
    printf("Nick de Usuario: %s\n",a.usuario);
    printf("Pass encriptada: ");
    for(j = 0;j < 5;j++)
    {
        for(i = 0;i < 2;i++)
        {
            printf("[%d]",a.pass[i][j]);
        }
    }
    printf("\nEliminado (0-si / 1-no): %d\n",a.eliminado);
    printf("---------------------------------\n");
}

void abreParaMostrarCliente(char archiCliente[])
{
    FILE *cli;
    cli = fopen(archiCliente,"rb");
    if(cli == NULL)
    {
        printf("Error al abrir el archivo!(imprimir Cliente)\n");
    }
    else
    {
        printf("CONTENIDO DEL ARCHIVO DE CLIENTES:\n");
        muestraClienteRecursivo(cli);
        fclose(cli);
    }
}
void muestraClienteRecursivo(FILE *x)
{
    persona aux;
    if(fread(&aux,sizeof(persona),1,x) > 0)
    {
        imprimeBloqueCliente(aux);
        muestraClienteRecursivo(x);
    }
}
void imprimeBloqueCliente(persona a)
{
    printf("---------------------------------------------------\n");
    printf("ID Cliente:                                   %d\n",a.id);
    printf("Apellido:                                     %s\n",a.apellido);
    printf("Nombre:                                       %s\n",a.nombre);
    printf("Tipo de Cliente (prioridad):\n");
    printf("[1:Embarazada] [2:Jubilado] [3: Comun].......[[%d]]\n",a.tipoCliente);
    printf("Medio de pago:\n");
    printf("[1-Efectivo] [2-Credito] [3-Todos]...........[[%d]]\n",a.medioPago);
    printf("Cantidad de Articulos (tiempo de ejecucion): [[%d]]\n",a.cantArticulos);
    printf("Tiempo de espera (tiempo de respuesta):      [[%d]]\n",a.tiempoEspera);
    printf("Tiempo procsado (tiempo en linea de caja):   [[%d]]\n",a.tiempoProcesado);
    printf("\nEliminado (0-si / 1-no):                   <<%d>>\n",a.eliminado);
    printf("---------------------------------------------------\n");
}
