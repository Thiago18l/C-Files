#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// lab10 THIAGO LOPES MOREIRA
typedef struct {
    char campeao[40], vice[40];
    int ano;
    char city[18];
}competion;


typedef struct elemento{
    competion dados;
    struct elemento *ant;
    struct elemento *prox;
} ELEM;


typedef struct{
    ELEM *inicio;
}LISTA;


LISTA* criar(){
    LISTA* li = (LISTA*) malloc(sizeof(LISTA));
    if(li != NULL);
    {
        li->inicio= NULL;
    }
    return li;
}


void liberar(LISTA *li){
    if(li !=NULL){
        ELEM * aux;
        while(li->inicio!=NULL)
        {
            aux = li->inicio;
            li->inicio = li->inicio->prox;
            free(aux);
        }
        free(li);
    }
}


int tamanho(LISTA *li){
    if(li==NULL){
        return -1;
    }
    int cont=0;
    ELEM *aux = li->inicio;
    while(aux != NULL)
    {
        cont++;
        aux= aux->prox;
    }
    return cont;
}


void vazia(LISTA *li){
    int tam = tamanho(li);
    if(li !=NULL)
    {
        if(li->inicio==NULL)
        {
            printf("\nLISTA VAZIA\n");
        }else
        {
            printf("\nLISTA NAO VAZIA\n");
        }
        printf("\nLISTA COM %d CAMPEONATOS\n",tam);
    }
    else
    {
        printf("\nERRO DE ALOCACAO\n");
    }
}
void inserir(LISTA *li, competion c)
{
    if(li==NULL)
    {
        printf("\nERRO DE ALOCAÇÃO\n");
    }
    else
    {
        ELEM *novo = (ELEM*) malloc(sizeof(ELEM));
        if(novo != NULL)
        {
            novo->dados= c;
            if(li->inicio==NULL){
                novo->prox=NULL;
                novo->ant=NULL;
                li->inicio=novo;
            }else{
                if(strcmp(li->inicio->dados.campeao,novo->dados.campeao)>0){
                    novo->ant=NULL;
                    novo->prox=li->inicio;
                    li->inicio->ant=novo;
                    li->inicio=novo;
                }else{
                    ELEM *ante,*aux=li->inicio;
                    while((aux!=NULL)&&(strcmp(aux->dados.campeao,novo->dados.campeao)<=0)){
                        ante=aux;
                        aux=aux->prox;
                    }
                    ante->prox=novo;
                    novo->ant=ante;
                    novo->prox=aux;
                    if(aux!=NULL)
                        aux->ant=novo;
                }

            }
            printf("\nCAMPEONATO CADASTRADO\n");
        }
        else
        {
            printf("\nERRO DE ALOCACAO\n");
        }
    }
}
void excluir(LISTA *li, int pos){

    if(li==NULL)
    {
        printf("\nERRO DE ALOCACAO\n");
    }
    else
    {
        if(li->inicio==NULL)
        {
            printf("\nLISTA VAZIA\n");
        }
        else
        {
            ELEM *aux=li->inicio;
            int cont=1;
            if(cont==pos){
                li->inicio=aux->prox;
                if(aux->prox!=NULL)
                    aux->prox->ant=NULL;
                free(aux);
            }else{
                ELEM *ant;
                while((aux!=NULL)&&(cont != pos)){
                    ant=aux;
                    aux=aux->prox;
                    cont++;
                }
                if(aux==NULL){
                    return;
                }
                ant->prox = aux->prox;
                if(aux->prox!=NULL)
                    aux->prox->ant=ant;
                free(aux);
            }
            printf("\nCAMPEONATO REMOVIDO\n");
        }
    }
}

void show(LISTA *li)
{
    if(li == NULL)
    {
        printf("\nERRO DE ALOCACAO\n");
    }
    else
    {
        if(li->inicio==NULL)
        {
            printf("\nLISTA VAZIA\n");
        }else{

            ELEM* aux = li->inicio;
            int cont=0;
            printf("CODIGO:\t\tANO:\t\t\tNOME DO CAMPEÃO:\t\t VICE: \t\t\tCIDADE:\n");
            while(aux != NULL){
                cont++;
                printf("%d\t\t%d\t\t\t\t%s\t\t\t%s\t\t",cont,aux->dados.ano,aux->dados.campeao,aux->dados.vice);//APRESENTA O NOME DO CONTATO
                printf("\t%s\n",aux->dados.city);
                aux = aux->prox;
            }
        }
    }
}
int menu()
{
    int op;
    printf("1 - LISTA DE CAMPEONATOS\n");
    printf("2 - CAMPEONATOS\n");
    printf("3 - INSERIR CAMPEONATO\n");
    printf("4 - REMOVER CAMPEONATO\n");
    printf("5 - SAIR\n");
    printf("\nOPÇÃO: ");
    scanf("%d",&op);
    putchar('\n');
    system("cls");
    return op;

}
void cadastro(competion *c){
    int x;
    printf("DIGITE O NOME DO CAMPEÃO: ");
    setbuf(stdin,NULL);
    gets(c->campeao);
    printf("DIGITE O NOME DO VICE:");
    setbuf(stdin,NULL);
    gets(c->vice);
    printf("DIGITE O ANO DO CAMPEONATO:");
    setbuf(stdin,NULL);
    scanf("%d",&c->ano);
    printf("DIGITE A CIDADE QUE REALIZOU:");
    setbuf(stdin,NULL);
    gets(c->city);

}
main(){
    setlocale(LC_ALL, "Portuguese");
    int o, x;
    LISTA *li = criar();

    competion c;

    while((o=menu())!=0)
    {
        switch(o)
        {

        case 1:
            show(li);
            break;
        case 2:
            vazia(li);
            break;
        case 3:
            cadastro(&c);
            inserir(li,c);
            break;
        case 4:
            show(li);
            printf("DIGITE O CODIGO DO CAMPEONATO QUE SERA REMOVIDO:");
            scanf("%d",&x);
            excluir(li,x);
            break;
        case 5:
            break;
        default:
            printf("OPÇÃO INVALIDA\n\n");
        }
    }
    liberar(li);
}
