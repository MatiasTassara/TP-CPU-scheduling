#include "libMatriz.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void GeneraMatrizPass(int MatrizPass[][maxC], int maxF, char Password [])
{
    int p = 0, fila = 0, columna = 0;
    while (p < 10)
    {
        while (fila < maxF)
        {
            while (columna < maxC)
            {
                MatrizPass [fila][columna] = Password[p];
                p++;
                columna++;
            }
            fila++;
            columna = 0;
        }
    }
}
void MultiplicaYgeneraEncriptada(int MatrizM [][2], int MatrizPass [][maxC], int MatrizEncriptada [][maxC], int maxF)
{
    int fM = 0, cM = 0, fP = 0, cP = 0, fE = 0, cE = 0;
    for (fM = 0; fM < maxF; fM++)
    {
        for (fP = 0; fP < maxF - 1; fP++)
        {
            for (cP = 0; cP < maxC; cP++)
            {
                MatrizEncriptada[fE][cE] = MatrizM [fM][cM] * MatrizPass [fP][cP] + MatrizM[fM][cM+1] * MatrizPass[fP+1][cP];
                cE++;
            }
            cE = 0;
            fE++;
            cP = 0;

        }
    }
}
//----------------------------------------------OBTENEMOS EL DETERMINANTE DE LA MATRIZM------------------------------------------------
int ObtieneDeterminante (int MatrizM [][2], int maxF)
{
    int i = 0, j = 0, diagonal1, diagonal2, verificador = 0;

    diagonal1 = MatrizM [i][j] * MatrizM [i+1][j+1];
    j++;
    diagonal2 = MatrizM [i][j] * MatrizM [i+1][j-1];
    verificador = diagonal1 - diagonal2;


    return verificador;
}

//---------------------------------------------OBTENEMOS LA MATRIZ COFACTORES---------------------------------------------------------
void ObtieneMatrizCofactores (int MatrizM [][2], int Cofactores [][2])
{
    int i = 0, j = 0, f = 0, c = 0;
    Cofactores [i][j] = MatrizM [f+1] [c+1];
    Cofactores [i][j+1] = MatrizM [f+1][c] * (-1);
    Cofactores [i+1][j] = MatrizM [f][c+1] * (-1);
    Cofactores [i+1][j+1] = MatrizM [f][c];


}
//-------------------------------------------MATRIZ ADJUNTA = TRASPUESTA DE MATRIZ COFACTORES------------------------------------------
void ObtieneMatrizAdjunta (int Cofactores[][2], int Adjunta [][2])
{
    int f = 0, c = 0, i = 0, j = 0;
    Adjunta [i][j] = Cofactores [f][c];
    Adjunta [i+1][j] = Cofactores [f][c+1];
    Adjunta [i][j+1] = Cofactores [f+1][c];
    Adjunta [i+1][j+1] = Cofactores [f+1][c+1];
}
//------------------------------------------MATRIZ INVERSA = ADJUNTA / DETERMINANTE----------------------------------------------------
void ObtieneInversa (int Determinante, int Adjunta [][2], double Inversa [][2], int maxF)
{
    int i = 0, j = 0, f = 0, c = 0;
    for (f = 0; f < maxC; f++)
    {
        for (c = 0; c < 2; c++)
        {
            Inversa [i][j] = (float) Adjunta [f][c] / (float)Determinante;
            j++;
        }
        c = 0;
        j = 0;
        i++;
    }
}
void MultiplicaYdesencripta (double Inversa [][2], int MatrizEncriptada [][maxC], char PassDesencriptada[11], int maxF)
{
    int fI = 0, cI = 0, fE = 0, cE = 0, p = 0;
    float resultado = 0;
    for (fI = 0; fI < maxF; fI++)
    {
        for (fE = 0; fE < maxF-1; fE++)
        {
            for (cE = 0; cE < maxC; cE++)
            {
                resultado = (Inversa [fI][cI] * (float) MatrizEncriptada[fE][cE]) + (Inversa[fI][cI+1] * (float) MatrizEncriptada[fE+1][cE]);
                PassDesencriptada[p] =  resultado;
                p++;
            }

            //cI = 0;
            //cE = 0;

        }
        PassDesencriptada [p]='\0';


    }
}
//-------------------------------------------------------------------------------------------------------------------------------------
//--------LAS SIGUIENTES FUNCIONES SON LAS PRINCIPALES DE ENCRIPTACION Y DESENCRIPTACION-----------------------------------------------

void EncriptaClave(char Password [11], int Encriptada [][maxC])
{
    int MatrizPass [2][maxC];
    int maxF = 2;
    int MatrizM [2][2] = {{5,2}, {4,3}};
    GeneraMatrizPass(MatrizPass, maxF, Password);
    MultiplicaYgeneraEncriptada(MatrizM, MatrizPass, Encriptada, maxF);
}
void DesencriptaClave (char password [],int Encriptada [][maxC])
{
    int Determinante = 0;
    int maxF = 2;
    int Cofactores [2][2];
    int Adjunta [2][2];
    double Inversa [2][2];
    int MatrizM [2][2] = {{5,2},{4,3}};
    //MostrarMatriz(Encriptada, maxF);
    //system("pause");



    Determinante = ObtieneDeterminante(MatrizM, maxF);
    Sleep(500);
    //system("pause");
    ObtieneMatrizCofactores(MatrizM, Cofactores);

    ObtieneMatrizAdjunta(Cofactores, Adjunta);

    ObtieneInversa(Determinante, Adjunta, Inversa, maxF);

    MultiplicaYdesencripta(Inversa, Encriptada, password, 2);


    //printf("\nLa contrasenia desencriptada es: %s", password);


}
void MostrarMatriz (int matrix [][maxC], int maxF)
{
    int i,j;
    printf("\n");

    for (i = 0; i < maxF; i++)
    {
        for (j = 0; j < maxC; j++)
        {
            printf(" |%d| ", matrix [i][j]);
        }
        printf("\n");
    }
}
char* Busca_Y_Desencripta(int identificacion,char archiUsuario[])
{
    char* Password = (char*)malloc(11 * sizeof(char));
    usuario aux;

    FILE * fusuario;
    fusuario = fopen(archiUsuario, "rb");
    if (fusuario != NULL)
    {
        fseek(fusuario, sizeof(usuario)* (identificacion-1), 0);
        fread(&aux,sizeof(usuario),1,fusuario);

        DesencriptaClave(Password,aux.pass);



        //Password[10] = '\0';
        fclose(fusuario);
    }
    return Password;
}

