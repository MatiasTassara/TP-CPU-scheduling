#ifndef LIBMATRIZ_H_INCLUDED
#define LIBMATRIZ_H_INCLUDED
#define maxC 5



typedef struct {
       int id;
       char nombre[30];
       char apellido[30];
       char usuario[20];
       int pass[2][5];
       int eliminado;
} usuario;

//PROTOTIPADO

void GeneraMatrizPass(int[][maxC], int, char[]); //TRANSFORMA UN STRING EN MATRIX DE 2 X 5
void MultiplicaYgeneraEncriptada(int [][2], int [][maxC], int [][maxC], int); //ENCRIPTA LA MATRIZ, UTILIZA UNA MATRIZ M PARA ENCRIPTAR
int ObtieneDeterminante (int[][2], int); //OBTIENE DETERMINANTE PARA COMENZAR PROCESO DE DESENCRIPTACION
void ObtieneMatrizCofactores (int[][2], int[][2]); //PARTE DE LA FUNCION DESENCRIPTAR
void ObtieneMatrizAdjunta (int[][2], int[][2]); //PARTE DE LA FUNCION DESENCRIPTAR
void ObtieneInversa (int , int [][2], double[][2], int); //PARTE DE LA FUNCION DESENCRIPTAR
void MultiplicaYdesencripta (double Inversa [][2], int[][maxC], char[11], int); //GENERA UN STRING QUE SE DECLARA EN EL MENU PARA MOSTRAR LA CONTRASENIA

void EncriptaClave(char[], int [][maxC]); //FUNCION FUNDAMENTAL
void DesencriptaClave (char [],int [][maxC]); //FUNCION FUNDAMENTAL

void MostrarMatriz (int matrix [][maxC], int maxF);//MUESTRA LA MATRIZ DE 2 X 5
char* Busca_Y_Desencripta(int,char[]);




#endif // LIBMATRIZ_H_INCLUDED
