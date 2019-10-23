#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void lerM(int *matriz, int m, int n);
void somarM(int *m1, int *m2, int *soma, int m, int n);
void MostrarM(int *matriz, int m, int n);
void subtrairM(int *matriz1, int *matriz2, int *sub, int m, int n);
void MultipliM(int *m1, int *m2, int *mult, int m, int n);


void lerM(int *matriz, int m, int n){
      int i, j, *pM;
      pM = matriz;
      for (i = 0; i < m; i = i + 1)
         for (j = 0; j < n; j = j + 1) scanf("%d", pM++);
  }
void somarM(int *m1, int *m2, int *soma, int m, int n){
     int i, j, *pA = m1, *pB = m2, *pC = soma;
      for (i = 0; i < m; i = i + 1)
         for (j = 0; j < n; j = j + 1) *pC++ = *pA++ + *pB++;
  }
void MostrarM(int *matriz, int m, int n){
      int i, j, *pM;
      pM = matriz;
      for (i = 0; i < m; i = i + 1){
          for (j = 0; j < n; j = j + 1) printf("%3d", *(pM + i * n + j));
          printf("\n");
       }
}
void subtrairM(int *matriz1, int *matriz2, int *sub, int m, int n){
     int i, j, *pA = matriz1, *pB = matriz2, *pC = sub;
      for (i = 0; i < m; i = i + 1)
         for (j = 0; j < n; j = j + 1) *pC++ = *pA++ - *pB++;
  }
void MultipliM(int *m1, int *m2, int *mult, int m, int n){
     int i, j, *pA = m1, *pB = m2, *pC = mult;
      for (i = 0; i < m; i = i + 1)
         for (j = 0; j < n; j = j + 1) *pC++ = *pA++ * *pB++;
  }
void MultipliME(int *m1, int m2, int *mult, int m, int n){
     int i, j, *pA = m1, pB = m2, *pC = mult;
      for (i = 0; i < m; i = i + 1)
         for (j = 0; j < n; j = j + 1) *pC++ = pB *  *pA++;
  }
void detMatriz(){
    int s = 0,cont = 0;;
    double **p = 0;
    int i = 0, j = 0, k = 0;
    double fator = 0,det = 0;
    printf("Digite a ordem da matriz: \n");
    scanf("%d", &s);
    p = (double **) calloc(s, sizeof(double *));
    for(i = 0; i < s; i++){
        p[i] = (double *) calloc(s, sizeof(double));
    }
    printf("Digite os valores da matriz:\n\n");
    for(i = 0; i < s; i++){
        for(j = 0; j < s; j++){
            printf("[%d][%d]=  ", i+1, j+1);
            scanf("%lf", &p[i][j]);}
}
    printf("A matriz é:\n");
    for(i = 0; i < s; i++){
        for(j = 0; j < s; j++){
            printf("\t %.0f", p[i][j]);
        }
        printf("\n");
}
    for(i = 0; i < s - 1; i++){
      if(p[i][i] == 0){
        for(k = i; k < s; k++){
           if(p[k][i] != 0){
              for(j = 0; j < s; j++){
                    det = p[i][j];
                    p[i][j] = p[k][j];
                    p[k][j] = det;
                    }
                k = s;
                }
            }
            cont++;
        }

    if(p[i][i] != 0){
            for(k = i + 1; k < s; k++){
                fator = -1.0 * p[k][i] /  p[i][i];
                for(j = i; j < s; j++){
                    p[k][j] = p[k][j] + (fator * p[i][j]);
                }
            }
        }
    }

    det = 1.0;

    for(i = 0; i < s; i++)
        det *= p[i][i];

    printf("\nDeterminante é: ");
    if(cont % 2 == 0)
        printf("%.0f\n", det);
    else
        printf("%.0f \n", -1.0 * det);
        system("pause");
        system("cls");
}

int main( ){
    setlocale(LC_ALL, "Portuguese");
    int opcao,linhas, colunas,escalar,z;
	int *m1, *m2, *soma,*sub,*mult;
	do{
    printf("SELECIONE UMA OPCAO");
    printf("\n1. SOMA ENTRE DUAS MATRIZES\n");
    printf("2. SUBTRACAO ENTRE DUAS MATRIZES\n");
    printf("3. MULTIPLICACAO ENTRE DUAS MATRIZES\n");
    printf("4. MULTIPLICACAO ENTRE UMA MATRIZ E UM ESCALAR\n");
    printf("5. CALCULAR O DETERMINANTE DE UMA MATRIZ.\n");
    printf("6. SAIR DO PROGRAMA\n");
    printf("\nOPCAO:");
    scanf("%d",&opcao);
    system("cls");
    switch(opcao){
        case 1:
          printf("Digite o numeros de linhas:\n");
          scanf("%d", &linhas);
          printf("Digite o numero de colunas:\n");
          scanf("%d", &colunas);
          printf("Digite os valores da matriz 1:\n");
          m1 = malloc(sizeof(int) * linhas * colunas);
          m2 = malloc(sizeof(int) * linhas * colunas);
          soma = malloc(sizeof(int) * linhas * colunas);
          lerM(m1, linhas, colunas);
          MostrarM(m1, linhas, colunas);
          printf("valores da matriz 2:\n");
          lerM(m2, linhas, colunas);
          MostrarM(m2, linhas, colunas);
          printf("\n");
          somarM(m1, m2, soma, linhas, colunas);
          printf("Soma das matrizes:\n");
          MostrarM(soma, linhas, colunas);
          printf("\n");
          printf("\n");
          system("pause");
          system("cls");
        break;
        case 2:
          printf("Digite o numeros de linhas:\n");
          scanf("%d", &linhas);
          printf("Digite o numero de colunas:\n");
          scanf("%d", &colunas);
          printf("Digite os valores da matriz 1:\n");
          m1 = malloc(sizeof(int) * linhas * colunas);
          m2 = malloc(sizeof(int) * linhas * colunas);
          sub = malloc(sizeof(int) * linhas * colunas);
          lerM(m1, linhas, colunas);
          MostrarM(m1, linhas, colunas);
          printf("valores da matriz 2:\n");
          lerM(m2, linhas, colunas);
          MostrarM(m2, linhas, colunas);
          printf("\n");
          subtrairM(m1, m2, sub, linhas, colunas);
          printf("Subtração das matrizes:\n");
          MostrarM(sub, linhas, colunas);
          printf("\n");
          printf("\n");
          system("pause");
          system("cls");
        break;
        case 3:
          printf("Digite o numeros de linhas:\n");
          scanf("%d", &linhas);
          printf("Digite o numero de colunas:\n");
          scanf("%d", &colunas);
          printf("Digite os valores da matriz 1:\n");
          m1 = malloc(sizeof(int) * linhas * colunas);
          m2 = malloc(sizeof(int) * linhas * colunas);
          mult = malloc(sizeof(int) * linhas * colunas);
          lerM(m1, linhas, colunas);
          MostrarM(m1, linhas, colunas);
          printf("valores da matriz 2:\n");
          lerM(m2, linhas, colunas);
          MostrarM(m2, linhas, colunas);
          printf("\n");
          MultipliM(m1, m2, mult, linhas, colunas);
          printf("Multiplicação das matrizes:\n");
          MostrarM(mult, linhas, colunas);
          printf("\n");
          printf("\n");
          system("pause");
          system("cls");
        break;
        case 4:
          printf("Digite o numeros de linhas:\n");
          scanf("%d", &linhas);
          printf("Digite o numero de colunas:\n");
          scanf("%d", &colunas);
          printf("Digite os valores da matriz:\n");
          m1 = malloc(sizeof(int) * linhas * colunas);
          escalar = malloc(sizeof(int) * linhas * colunas);
          mult = malloc(sizeof(int) * linhas * colunas);
          lerM(m1, linhas, colunas);
          MostrarM(m1, linhas, colunas);
          printf("Digite a escalar:\n");
          scanf("%d", &escalar);
          MultipliME(m1, escalar, mult, linhas, colunas);
          printf("Multiplicação da matriz com escalar:\n");
          MostrarM(mult, linhas, colunas);
          printf("\n");
          printf("\n");
          system("pause");
          system("cls");
        break;
        case 5:
          detMatriz(z);
	    break;
        case 6:
         system("pause");
        break;
        default:
            printf("Opcao Invalida\n");
            printf("Pressione Qualquer tecla para voltar ao Menu Principal");
            getch();
            system("cls");
            break;
    }

}while(opcao!=6);
}
