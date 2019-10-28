#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
    DADO d;
    struct elemento *prox;
}ELEM;
typedef struct {
    int valor;
}DADO;
typedef struct elemento* Lista;
Lista* criarLista();
void liberarLista(Lista *li);
int tamanhoLista(Lista *li);
void inserir(Lista *li, DADO d);
void remover(Lista *li, int num);
void imprimirLista(Lista *li);

Lista *criarLista(){
    Lista *li = (Lista*)malloc(sizeof(Lista));
    if(li!=NULL){
        *li = NULL;
    }
    return li;
}
void liberarLista(Lista *li){
    if(li!=NULL){
        ELEM *aux;
        while(*li!=NULL){
            aux=*li;
            *li=aux->prox;
            free(aux);
        }
        free(li);
    }
}
int tamanhoLista(Lista *li){
    int n=0;
    if(li!=NULL){
        ELEM *aux=*li;
        while(aux!=NULL){
            n++;
            aux=aux->prox;
        }
    }
    return n;
}
void inserir(Lista *li, DADO d){
    if(li!=NULL){
        ELEM *e=(ELEM*)malloc(sizeof(ELEM));
        e->d=d;
        if(*li==NULL){
            e->prox=NULL;
            *li=e;
        }else{
            ELEM *aux=*li;
            if(aux->d.valor > e->d.valor){
                e->prox=*li;
                *li=e;
            }else{
                ELEM *ant;
                while((aux!=NULL)&&(aux->d.valor < e->d.valor)){
                    ant=aux;
                    aux=aux->prox;
                }
                ant->prox=e;
                e->prox=aux;
            }
        }
    }
}
void remover(Lista *li, int num){
    if(li!=NULL){
        if(*li==NULL)
            return;
        ELEM *aux=*li;
        if(aux->d.valor==num){
            *li=aux->prox;
            free(aux);
        }else{
            ELEM *ant;
                while((aux!=NULL)&&(aux->d.valor != num)){
                    ant=aux;
                    aux=aux->prox;
                }
                if(aux==NULL){
                    return;
                }
                ant->prox = aux->prox;
                free(aux);
        }
    }
}
void imprimirLista(Lista *li){
    if(li!=NULL){
        ELEM *aux=*li;
        if(aux!=NULL){
            printf("Elementos da Lista\n\n");
            while(aux!=NULL){
                printf("%d\n",aux->d.valor);
                aux=aux->prox;
            }
        }else{
            printf("Lista Vazia\n");
        }

    }
}
int menu(){
    int n;
    printf("\n1 - MOSTRAR A LISTA\n");
    printf("2 - TAMANHO DA LISTA\n");
    printf("3 - INSERIR ELEMENTO NA LISTA\n");
    printf("4 - REMOVER ELEMENTO DA LISTA\n");
    printf("0 - SAIR\n");
    printf("\nOPCAO >> ");
    scanf("%d",&n);
    system("cls");
    return n;
}
void pegarDado(DADO *d){
    printf("\nDigite um numero para ser armazenado >> ");
    scanf("%d",&d->valor);
}
main(){
    Lista *li = criarLista();
    DADO d;
    int o,v;
    while((o=menu())!=0){
        switch(o){
            case 1:
                system("cls");
                imprimirLista(li);
                break;
            case 2:
                system("cls");
                printf("tamanho da lista: %d\n",tamanhoLista(li));
                break;
            case 3:
                system("cls");
                pegarDado(&d);
                inserir(li,d);
                break;
            case 4:
                system("cls");
                imprimirLista(li);
                printf("Digite um valor para ser removido da lista >> ");
                scanf("%d",&v);
                remover(li,v);
                imprimirLista(li);
                break;
            default:
                printf("valor errado");
        }
    }
    liberarLista(li);
}
