#include <stdio.h>
#include <windows.h>
#include <conio.h> //Caso esta biblioteca nao pegue em sua maquina, deve-se importar manualmente
void menuCIMA(int tamanho);
void menuBAIXO(int tamanho);
void menuOPCAO(char opcao[], int tamanho);
//REFERENCIA https://www.youtube.com/watch?v=5FmC9dSaKq0
void gotoXY(int x, int y);

int menu_principal() {
    int o;
    menuCIMA(40);
    printf(" %c                  MENU                  %c\n", 186, 186);
    menuOPCAO("", 40);
    menuOPCAO(" 1 - CHECK IN", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 2 - CONTRATOS", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 3 - CHECK OUT", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 4 - Sair", 40);
    menuOPCAO("", 40);
    menuBAIXO(40);
    menuCIMA(10);
    menuOPCAO(" OPCAO: ", 10);
    menuBAIXO(10);
    gotoXY(10, 13);
    setbuf(stdin, NULL);
    scanf("%d", &o);
    return o;
}

void menuOPCAO(char opcao[], int tamanho) {
    printf(" %c", 186);
    printf("%-*s", tamanho, opcao);
    printf("%c\n", 186);
}

void menuCIMA(int tamanho) {
    int i;
    printf(" %c", 201);
    for (i = 0 ; i < tamanho; i++)
        printf("%c", 205);
    printf("%c\n", 187);
}

void menuBAIXO(int tamanho) {
    int i;
    printf(" %c", 200);
    for ( i = 0 ; i < tamanho; i++)
        printf("%c", 205);
    printf("%c\n", 188);
}

void gotoXY(int x,int y){
    COORD coordenadas = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordenadas);
}
int mat = 100;
//Estrutura para o cadastro de alunos
typedef struct alunos {
    int matricula;
    char nome[50];
    char cpf[12];
} CAD_ALUNOS;

void verificadorArquivo(FILE* arquivo);
void alterarAlunos();
void cadastrarAlunos();
void listarAlunos();
void editarAlunos();
void excluirAlunos();

void op_alunos () {
    int o = 0;
    struct alunos al;
    do {
        menuAluno();
        scanf("%d", &o);
        system("cls");
        switch(o) {
        case 1:
            cadastrarAlunos();
            break;
        case 2:
            excluirAlunos();
            break;
        case 3:
            editarAlunos();
            break;
        case 4:
            listarAlunos(al);
            break;
        case 5:
            return;
        default:
            printf("Op��o invalida\n");
            break;
        }
        fflush(stdin);
    } while(o != 5);
}

int contadorMat() {
    int aux = 0;
    FILE *arquivo;
    arquivo = fopen("cad_alunos.txt", "rb");
    CAD_ALUNOS al;
    verificadorArquivo(arquivo);
    while(fread(&al, sizeof(CAD_ALUNOS), 1, arquivo) == 1) {
        aux++;
    }
    fclose(arquivo);
    return aux+1;
}

int verificarmatricula(int aux){
    int a = 0;
    FILE *arquivo;
    arquivo = fopen("cad_alunos.txt", "rb");
    CAD_ALUNOS al;
    verificadorArquivo(arquivo);
    while(fread(&al, sizeof(CAD_ALUNOS), 1, arquivo) == 1) {
        if(aux == al.matricula){
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
}

int verificarCpf(char cpf[12]) {
    int i=0;
    FILE *arquivo;
    arquivo = fopen("cad_alunos.txt", "rb");
    verificadorArquivo(arquivo);
    CAD_ALUNOS al;
    while(fread(&al,sizeof(CAD_ALUNOS), 1, arquivo) == 1) {
        if(strcmp(cpf, al.cpf ) == 0) {
            fclose(arquivo);
            return 1;
        }
    }
    system("cls");
    fclose(arquivo);
}

void cadastrarAlunos() {
    system("cls");
    int aux = 0, x=0;
    char cpf[12];
    FILE *arquivo; //FILE (sempre maiuscula), vari�vel do tipo file (arquivo � o nome do ponteiro), nesta linha est� sendo criado o ponteiro
    FILE *arq;
    CAD_ALUNOS al;
    arquivo = fopen ("cad_alunos.txt", "ab");// "ab" acrescenta dados bin�rios no fim do arquivo e se o arquivo n�o existir ele ser� criado e
    //e fopen � respons�vel fazer com que o ponteiro aponte para um arquivo no programa
    arq = fopen("cad_alunos.txt", "rb");
    verificadorArquivo(arq);
    verificadorArquivo(arquivo);
    char op;
    aux = contadorMat() + 1;
    system("cls");
    fflush(stdin);
    menuCIMA(strlen("Matricula do Aluno: ")+10);
    menuOPCAO("Matricula do Aluno: ", strlen("Matricula do Aluno: ")+10);
    gotoXY(0, 2);
    menuBAIXO(strlen("Matricula do Aluno: ")+10);
    gotoXY(22, 1);
    aux = aux + mat;
    if(verificarmatricula(aux) == 1){
        aux = aux + 2;
    }
    printf("%d\n\n", aux);
    al.matricula = aux;
    system("pause");
    system("cls");
    fflush(stdin);
    menuCIMA(strlen("Digite o Nome do Aluno: ")+50);
    menuOPCAO("Digite o Nome do Aluno: ", strlen("Digite o Nome do Aluno: ")+50);
    gotoXY(0, 2);
    menuBAIXO(strlen("Digite o Nome do Aluno: ")+50);
    gotoXY(26, 1);
    gets(al.nome);
    strupr(al.nome); //Converte o conte�do digitado em mai�sculo.
    fflush(stdin);
    system("cls");
    menuCIMA(strlen("Digite o CPF do Aluno: ")+15);
    menuOPCAO("Digite o CPF do Aluno: ", strlen("Digite o CPF do Aluno: ")+15);
    gotoXY(0, 2);
    menuBAIXO(strlen("Digite o CPF do Aluno: ")+15);
    gotoXY(25, 1);
    gets(al.cpf);
    strupr(al.cpf);//Converte o conte�do digitado em mai�sculo.
    x = verificarCpf(al.cpf);
    if(x == 1) {
        system("cls");
        printf("\n\n  CPF ja cadastrado!\n\n");
        system("pause");
        fclose(arquivo); //Fecha o arquivo que foi aberto.
        fclose(arq);
        system("cls");
        return;
    } else {
        fwrite(&al, sizeof(CAD_ALUNOS), 1, arquivo);
    }
    // o numero 1 representa a quantidade de elementos que desejo gravar na struct
    //SIZEOF passa para a fun��o o tamanho em bytes da struct
    system("cls");
    menuCIMA(strlen("Registro gravado com sucesso!"));
    menuOPCAO("Registro gravado com sucesso!", strlen("Registro gravado com sucesso!"));
    gotoXY(0, 2);
    menuBAIXO(strlen("Registro gravado com sucesso!"));
    gotoXY(2, 3);
    system("pause");
    fclose(arquivo); //Fecha o arquivo que foi aberto.
    fclose(arq);
    system("cls");
}

void listarAlunos() {
    int x = 0;
    FILE *arquivo;
    arquivo = fopen("cad_alunos.txt", "rb");
    CAD_ALUNOS al;
    menuCIMA(29);
    menuOPCAO("     LISTAGEM DE ALUNOS", 29);
    menuBAIXO(29);
    while(fread(&al, sizeof(CAD_ALUNOS), 1,arquivo)==1) {
        printf("\n Matricula: %d\n", al.matricula);
        printf("\n Nome: %s\n", al.nome);
        printf("\n CPF: %s\n\n", al.cpf);
        printf(" ---------------------------------------------\n");
        x++;
    }
    if(x == 0) {
        printf("\n\n  LISTA VAZIA!\n\n\n");
    }
    menuCIMA(31);
    menuOPCAO("   FIM DA LISTAGEM DE ALUNOS", 31);
    menuBAIXO(31);
    system("pause");
    system("cls");
    fclose(arquivo);
}

void editarAlunos() {
    int op = 0;
    do {
        system("cls");
        menuCIMA(29);
        menuOPCAO("     LISTAGEM DE ALUNOS", 29);
        menuOPCAO("", 29);
        menuOPCAO(" 1 - Procurar Por CPF ", 29);
        menuOPCAO("", 29);
        menuOPCAO(" 2 - Sair", 29);
        menuBAIXO(29);
        menuCIMA(10);
        menuOPCAO(" OPCAO: ", 10);
        menuBAIXO(10);
        gotoXY(10, 8);
        scanf("%d", &op);
        system("cls");
        switch(op) {
        case 1:
            alterarAlunos();
            break;
        case 2:
            break;
        default:
            printf("\n\n  Opcao invalida\n");
            system("pause");
            break;
        }
    } while(op != 2);
}

void alterarAlunos() {
    CAD_ALUNOS al;
    //variavel para contar a posicao
    int i = 0;
    //variavel para salvar o que o usuario digitar e comparar com os que est� no arquivo
    char auxiliar[12];
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo = fopen("cad_alunos.txt", "r+b");
    verificadorArquivo(arquivo);
    fflush(stdin);
    system("cls");
    menuCIMA(50);
    menuOPCAO("Digite o CPF que deseja editar: ", 50);
    menuBAIXO(50);
    gotoXY(35, 1);
    gets(auxiliar);
    //l� todos os dados do arquivo at� encontrar o final do arquivo (EOF)
    while(fread(&al, sizeof(CAD_ALUNOS), 1,arquivo)==1) {
        //comparar a cpf que o usuario digitou com os que ja est�o no arquivo
        if(strcmp(auxiliar, al.cpf) == 0) {
            printf("\n\n");
            menuCIMA(32);
            menuOPCAO("         Dados Atuais         ", 32);
            menuBAIXO(32);
            printf("\n Nome do Aluno: %s", al.nome);
            printf("\n Matricula do Aluno: %d", al.matricula);
            printf("\n CPF Atual: %s\n",al.cpf );
            printf("\n\n Digite o Novo CPF: ");
            fflush(stdin);
            fgets(al.cpf, 12, stdin);
            //O novo cpf que foi digitado vai receber um \0 para indicar o fim
            al.cpf[strlen(al.cpf) - 1]= '\0';
            printf("\n Digite o Novo Nome: ");
            fflush(stdin);
            fgets(al.nome, 50, stdin);
            strupr(al.nome);
            //O novo nome que foi digitado vai receber um \0 para indicar o fim
            al.nome[strlen(al.nome) - 1] = '\0';
            //vou para a posicao no arquivo que eu quero incluir os novos dados
            fseek(arquivo, i * sizeof(CAD_ALUNOS),SEEK_SET);
            //inscrevo os novos dados e verifico se foi feito com sucesso
            if(fwrite(&al,sizeof(CAD_ALUNOS), 1 , arquivo) != 1) {
                system("cls");
                printf("\n\n\n\n Falha ao Alterar o registro!\n");
                 system("cls");
                 fclose(arquivo);
                 return;
            } else {
                system("cls");
                printf("\n\n\n\n Registro alterado com sucesso!\n");
            }
            i++;
            break;
        }
    }
    if( i == 0 ){
        system("cls");
        printf("\n\n Nao ha registro com tal CPF!\n\n");

    }
    system("pause");
    system("cls");
    fclose(arquivo);
}

void excluirAlunos() {
    CAD_ALUNOS al;
    int i = 0, j = 0;
    char auxiliar[12];
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo = fopen("cad_alunos.txt", "a+b");
    FILE *arq_auxiliar = fopen("auxiliar.txt", "w+b");
    if(arquivo == NULL || arq_auxiliar == NULL) {
        printf("\n Impossivel Abrir o arquivo!\n");
    } else {
        fflush(stdin);
        menuCIMA(50);
        menuOPCAO("Digite o CPF que deseja excluir: ", 50);
        menuBAIXO(50);
        gotoXY(35, 1);
        gets(auxiliar);
        while(fread(&al, sizeof(CAD_ALUNOS), 1, arquivo) == 1) {
            i++;
            if(strcmp(auxiliar, al.cpf) == 0) {
                al.cpf[strlen(al.cpf) - 1] = '\0';
                al.nome[strlen(al.nome) - 1] = '\0';
                fseek(arquivo,(i - 1) * sizeof(CAD_ALUNOS),SEEK_SET);
                j++;
            } else {
                fwrite(&al,sizeof(CAD_ALUNOS), 1, arq_auxiliar);
            }
        }
        fclose(arquivo);
        fclose(arq_auxiliar);
        system("cls");
        if(j > 0) {
            printf("\n\n  Registro encontrado!\n\n");
            system("pause");
        } else {

            printf("\n\n  Nao ha registro com esse CPF!\n\n");
            system("pause");
            system("cls");
            fclose(arquivo);
            fclose(arq_auxiliar);
            return;
        }
        system("cls");
        if(remove("cad_alunos.txt") == 0) {
            rename("auxiliar.txt", "cad_alunos.txt");
            putchar('\n');
            menuCIMA(40);
            menuOPCAO("    Registro excluido com Sucesso", 40);
            menuBAIXO(40);
            system("pause");
        } else {
            printf("\n\n  Nao foi Possivel Excluir o Cadastro!\n");
            printf("\n\n%s\n\n", strerror(errno));
            system("pause");
        }
        system("cls");
    }
    fclose(arquivo);
    fclose(arq_auxiliar);
}
//Fun��o para verificar que op��o vai ser usada no menu aluno

void verificadorArquivo(FILE *arquivo) {
    if(arquivo == NULL) {
        system("cls");
        printf("\n\n  Saindo do programa...");
        Sleep(100);
        exit(1);
    }
}

int menuAluno() {
    int o;
    menuCIMA(40);
    printf(" %c                 ALUNOS                 %c\n", 186, 186);
    menuOPCAO("", 40);
    menuOPCAO(" 1 - Cadastrar Aluno", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 2 - Remover Aluno", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 3 - Editar Aluno", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 4 - Listar Alunos Cadastrados", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 5 - Ir para menu anterior", 40);
    menuOPCAO("", 40);
    menuBAIXO(40);
    menuCIMA(10);
    menuOPCAO(" OPCAO: ", 10);
    menuBAIXO(10);
    gotoXY(10, 15);

}
int cod_livro = 100;
//Estrutura para o cadastro de livros
typedef struct livro {
    int codigo;
    int quantidade;
    char nome_livro[50];
    char nome_autor[50];
    char area[50];
} CAD_LIVROS;

void procurarLivros();
void editarLivros();
void cadastrarLivros();
void excluirLivros();
int contadorCod();
void listarLivros();

void op_acervo () {
    int o = 0;
    struct livro li;
    do {
        menuAcervo();
        scanf("%d", &o);
        system("cls");
        switch(o) {
        case 1:
            cadastrarLivros();
            break;
        case 2:
            excluirLivros();
            break;
        case 3:
            editarLivros();
            break;
        case 4:
            listarLivros();
            break;
        case 5:
            return;
        default:
            system("cls");
            printf("\nOpcao invalida\n");
            system("pause");
            break;
        }
        fflush(stdin);
    } while(o != 5);
}

int contadorCod() {
    int aux = 0;
    FILE *arquivo;
    arquivo = fopen("cad_livros.txt", "rb");
    CAD_LIVROS li;
    if(arquivo == NULL) {
        system("cls");
        printf("\n\n  Problemas na abertura do arquivo!\n");
        system("pause");
    } else
        while(fread(&li, sizeof(CAD_LIVROS), 1,arquivo) == 1)
            if(&(li.codigo) != NULL)
                aux++;
    fclose(arquivo);
    return aux;
}

int verificarcodigo(int aux){
    int a = 0;
    FILE *arquivo;
    arquivo = fopen("cad_livros.txt", "rb");
    CAD_LIVROS li;
    verificadorArquivo(arquivo);
    while(fread(&li, sizeof(CAD_LIVROS), 1, arquivo) == 1) {
        if(aux == li.codigo){
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
}


void cadastrarLivros() {
    system("cls");
    FILE* arquivo; //FILE (sempre maiuscula), vari�vel do tipo file (arquivo � o nome do ponteiro), nesta linha est� sendo criado o ponteiro
    CAD_LIVROS livros;
    arquivo = fopen ("cad_livros.txt", "ab");// "ab" acrescenta dados bin�rios no fim do arquivo e se o arquivo n�o existir ele ser� criado e
    //e fopen � respons�vel fazer com que o ponteiro aponte para um arquivo no programa
    verificadorArquivo(arquivo);
    char op;
    int aux = 0;
    aux = contadorCod()+1;
    system("cls");
    fflush(stdin);
    menuCIMA(strlen("Codigo do Livro: ") + 15);
    menuOPCAO("Codigo do livro: ", strlen("Codigo do livro: ") + 15);
    gotoXY(0, 2);
    menuBAIXO(strlen("Codigo do livro: ") + 15);
    gotoXY(22, 1);
    aux = aux + cod_livro;
    if(verificarcodigo(aux) == 1){
        aux = aux + 2;
    }
    printf("%d\n\n", aux);
    livros.codigo = aux;
    system("pause");
    system("cls");
    fflush(stdin);
    menuCIMA(strlen("Area do Livro: ") + 30);
    menuOPCAO("Area do livro: ", strlen("Area do livro: ") + 30);
    gotoXY(0, 2);
    menuBAIXO(strlen("Area do livro: ") + 30);
    gotoXY(17, 1);
    scanf("%s", &livros.area);
    strupr(livros.area);
    system("cls");
    fflush(stdin);
    menuCIMA(strlen("Digite o Nome do livro: ") + 50);
    menuOPCAO("Digite o Nome do livro: ", strlen("Digite o Nome do livro: ") + 50);
    gotoXY(0, 2);
    menuBAIXO(strlen("Digite o Nome do livro: ") + 50);
    gotoXY(26, 1);
    gets(livros.nome_livro);
    strupr(livros.nome_livro); //Converte o conte�do digitado em mai�sculo.
    fflush(stdin);
    system("cls");
    menuCIMA(strlen("Digite o Nome do Autor do livro: ") + 30);
    menuOPCAO("Digite o Nome do Autor do livro: ", strlen("Digite o Nome do Autor do livro: ") + 30);
    gotoXY(0, 2);
    menuBAIXO(strlen("Digite o Nome do Autor do livro: ") + 30);
    gotoXY(35, 1);
    gets(livros.nome_autor);
    strupr(livros.nome_autor);//Converte o conte�do digitado em mai�sculo.
    system("cls");
    do {
        fflush(stdin);
        menuCIMA(strlen("Quantidade de Livros: ") + 10);
        menuOPCAO("Quantidade de Livros: ", strlen("Quantidade de Livros: ") + 10);
        gotoXY(0, 2);
        menuBAIXO(strlen("Quantidade de Livros: ") + 10);
        gotoXY(24, 1);
        scanf("%d", &livros.quantidade);
    } while(livros.quantidade <= 0);
    fwrite(&livros, sizeof(CAD_LIVROS), 1, arquivo); // o numero 1 representa a quantidade de elementos que desejo gravar na struct
    //SIZEOF passa para a fun��o o tamanho em bytes da struct
    system("cls");
    gotoXY(0, 2);
    printf("\n\n  Livro gravado com sucesso!\n\n");
    gotoXY(22, 1);
    system("pause");
    fclose(arquivo); //Fecha o arquivo que foi aberto.
    system("cls");
}

void editarLivros() {
    int op = 0;
    menuCIMA(42);
    menuOPCAO("         PROCURAR LIVROS PARA EDITAR", 42);
    menuBAIXO(42);
    do {
        printf("\n 1 - Procurar Por Codigo do livro ");
        printf("\n 2 - Sair");
        printf("\n Opcao: ");
        scanf("%d", &op);
        setbuf(stdin, NULL);
        system("cls");
        switch(op) {
        case 1:
            procurarLivros();
            break;
        case 2:
            return;
            break;
        default:
            system("cls");
            printf("\n\n  Opcao invalida\n");
            system("pause");
            break;
        }
    } while(op != 2);
}

void listarLivros() {
    int x = 0;
    FILE *arquivo;
    arquivo = fopen("cad_livros.txt", "rb");
    CAD_LIVROS livros;
    menuCIMA(29);
    menuOPCAO("     LISTAGEM DE LIVROS", 29);
    menuBAIXO(29);
    while(fread(&livros, sizeof(CAD_LIVROS), 1,arquivo)==1) {
        printf("\n Codigo do Livro: %d\n", livros.codigo);
        printf("\n Nome do Livro: %s\n", livros.nome_livro);
        printf("\n Nome do Autor do Livro: %s\n", livros.nome_autor);
        printf("\n Area que o Livro se encaixa: %s\n", livros.area);
        printf("\n Quantidade de Livros no Acervo: %d\n", livros.quantidade);
        printf("\n ---------------------------------------------\n");
        x++;
    }
    if(x == 0) {
        printf("\n\n  LISTA VAZIA!\n\n\n");
    }
    menuCIMA(31);
    menuOPCAO("   FIM DA LISTAGEM DE LIVROS", 31);
    menuBAIXO(31);
    system("pause");
    system("cls");
    fclose(arquivo);
}

void procurarLivros() {
    CAD_LIVROS livros;
    //variavel para contar a posi��o
    int i=0, op=0;
    //variavel para salvar o que o usuario digitar e comparar com os que est� no arquivo
    int auxiliar;
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo = fopen("cad_livros.txt", "r+b");
    if(arquivo == NULL) {
        printf("\n Impossivel Abrir o arquivo!\n");
    } else {
        fflush(stdin);
        menuCIMA(57);
        menuOPCAO("Digite o Codigo do Livro que Deseja Procurar: ", 57);
        menuBAIXO(57);
        gotoXY(48, 1);
        scanf("%d", &auxiliar);
        system("cls");
        //l� todos os dados do arquivo at� encontrar o final do arquivo (EOF)
        while(fread(&livros, sizeof(CAD_LIVROS), 1,arquivo)==1) {
            i++;
            //comparar a cpf que o usuario digitou com os que ja est�o no arquivo
            if(auxiliar == livros.codigo) {
                menuCIMA(32);
                menuOPCAO("         DADOS ATUAIS         ", 32);
                menuBAIXO(32);
                printf("\n Codigo do livro: %d", livros.codigo);
                printf("\n Nome do livro: %s", livros.nome_livro);
                printf("\n Nome do Autor do Livro: %s", livros.nome_autor );
                printf("\n Area de Conhecimento do Livro: %s", livros.area );
                printf("\n Quantidade de Livros: %d\n\n", livros.quantidade);
                menuCIMA(32);
                menuOPCAO("O que voce deseja alterar ?", 32);
                menuBAIXO(32);
                printf("\n 1 - Nome do Livro");
                printf("\n 2 - Nome do Autor do Livro");
                printf("\n 3 - Area de Conhecimento do Livro");
                printf("\n 4 - Quantidade de Livros");
                printf("\n 5 - Sair\n");
                menuCIMA(10);
                menuOPCAO(" OPCAO: ", 10);
                menuBAIXO(10);
                gotoXY(10, 20);
                scanf("%d", &op);
                system("cls");
                switch(op) {
                case 1:
                    fflush(stdin);
                    menuCIMA(strlen("Digite o Novo Nome do Livro: ") + 30);
                    menuOPCAO("Digite o Novo Nome do Livro: ", strlen("Digite o Novo Nome do Livro: ") + 30);
                    gotoXY(0, 2);
                    menuBAIXO(strlen("Digite o Novo Nome do Livro: ") + 30);
                    gotoXY(strlen("Digite o Novo Nome do Livro:   "), 1);
                    fgets(livros.nome_livro, 50, stdin);
                    //O novo campo que foi digitado vai receber um \0 para indicar o fim
                    livros.nome_livro[strlen(livros.nome_livro) - 1]= '\0';
                    strupr(livros.nome_livro);
                    break;
                case 2:
                    fflush(stdin);
                    menuCIMA(strlen("Digite o Novo Nome do Autor do Livro: ") + 30);
                    menuOPCAO("Digite o Novo Nome do Autor do Livro: ", strlen("Digite o Novo Nome do Autor do Livro: ") + 30);
                    gotoXY(0, 2);
                    menuBAIXO(strlen("Digite o Novo Nome do Autor do Livro: ") + 30);
                    gotoXY(strlen("Digite o Novo Nome do Autor do Livro:   "), 1);
                    fgets(livros.nome_autor, 50, stdin);
                    //O novo campo que foi digitado vai receber um \0 para indicar o fim
                    livros.nome_autor[strlen(livros.nome_autor) - 1]= '\0';
                    strupr(livros.nome_autor);
                    break;
                case 3:
                    fflush(stdin);
                    menuCIMA(strlen("Digite a Nova Area de Conhecimento do Livro: ") + 30);
                    menuOPCAO("Digite a Nova Area de Conhecimento do Livro: ", strlen("Digite a Nova Area de Conhecimento do Livro: ") + 30);
                    gotoXY(0, 2);
                    menuBAIXO(strlen("Digite a Nova Area de Conhecimento do Livro: ") + 30);
                    gotoXY(strlen("Digite a Nova Area de Conhecimento do Livro:   "), 1);
                    fgets(livros.nome_livro, 50, stdin);
                    //O novo campo que foi digitado vai receber um \0 para indicar o fim
                    livros.area[strlen(livros.area) - 1]= '\0';
                    strupr(livros.area);

                    break;
                case 4:
                    fflush(stdin);
                    menuCIMA(strlen("Digite a Nova Quantidade de Livros: ") + 20);
                    menuOPCAO("Digite a Nova Quantidade de Livros: ", strlen("Digite a Nova Quantidade de Livros: ") + 20);
                    gotoXY(0, 2);
                    menuBAIXO(strlen("Digite a Nova Quantidade de Livros: ") + 20);
                    gotoXY(strlen("Digite a Nova Quantidade de Livros:   "), 1);
                    scanf("%d", &livros.quantidade);
                    break;
                case 5:
                    break;
                default:
                    printf("Opcao Incorreta!\n");
                }
                fseek(arquivo,(i-1)*sizeof(CAD_LIVROS),SEEK_SET);
                if(fwrite(&livros,sizeof(CAD_LIVROS), 1, arquivo) != 1) {
                    printf("\n Falha ao Alterar o registro!\n");
                    system("pause");
                } else {
                    printf("\n Registro alterado com sucesso!\n");
                }
                break;
            }
        }
    }
    menuCIMA(32);
    menuOPCAO("         FIM DA EDICAO         ", 32);
    menuBAIXO(32);
    system("pause");
    system("cls");
    fclose(arquivo);
}

void excluirLivros() {
    CAD_LIVROS li;
    int i = 0;
    char auxiliar[12];
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo = fopen("cad_livros.txt", "r+b");
    FILE *arq_auxiliar = fopen("auxiliar.txt", "w+b");
    if(arquivo == NULL || arq_auxiliar == NULL) {
        printf("\n\n  Impossivel Abrir o arquivo!\n");
    } else {
        fflush(stdin);
        menuCIMA(60);
        menuOPCAO("Digite o Nome do Livro que Deseja Excluir:    ", 60);
        menuBAIXO(60);
        gotoXY(47, 1);
        gets(auxiliar);
        strupr(auxiliar);
        while(fread(&li, sizeof(CAD_LIVROS), 1,arquivo)==1) {
            i++;
            if(strcmp(auxiliar, li.nome_livro) == 0) {
                fseek(arquivo,(i-1) * sizeof(CAD_LIVROS), SEEK_SET);
            } else {
                fwrite( &li, sizeof(CAD_LIVROS), 1, arq_auxiliar);
            }
        }
        fclose(arquivo);
        fclose(arq_auxiliar);
        if(remove("cad_livros.txt")==0) {
            menuCIMA(60);
            menuOPCAO("         Livro excluido com Sucesso", 60);
            menuBAIXO(60);
        } else {
            menuCIMA(60);
            menuOPCAO("         Nao foi possivel excluir o Livro         ", 60);
            menuBAIXO(60);
            printf("\n\n%s\n\n", strerror(errno));
        }
        rename("auxiliar.txt", "cad_livros.txt");
        system("pause");
        system("cls");
        fclose(arquivo);
        fclose(arq_auxiliar);
    }
    system("pause");
    system("cls");
    fclose(arquivo);
    fclose(arq_auxiliar);
}

int menuAcervo() {
    menuCIMA(40);
    printf(" %c                 LIVROS                 %c\n", 186, 186);
    menuOPCAO("", 40);
    menuOPCAO(" 1 - Cadastrar livro", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 2 - Remover livro", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 3 - Editar livro", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 4 - Listar livros Cadastrados", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 5 - Ir para menu anterior", 40);
    menuOPCAO("", 40);
    menuBAIXO(40);
    menuCIMA(10);
    menuOPCAO(" OPCAO: ", 10);
    menuBAIXO(10);
    gotoXY(10, 15);
}
int codEmprestimo = 100;

//Estrutura para o cadastro de alunos
typedef struct emprestimos {
    int cod_livro;
    int cod_emprestimo;
    int matricula_aluno;
    char nome_livro[50];
    char nome_aluno[50];
    int dia_em;
    int mes_em;
    int ano_em;
    int diadev;
    int mesdev;
    int anodev;
} CAD_EMP;

typedef struct {
    int dia;
    int mes;
    int ano;
} DAT;

void p_data(char str[9], DAT *Alvo) {
    char _dia[3] = {
        str[3],
        str[4],
        0
    };
    char _mes[3] = {
        str[0],
        str[1],
        0
    };
    char _ano[3] = {
        str[6],
        str[7],
        0
    };
    Alvo->dia = atoi(_dia);
    Alvo->mes = atoi(_mes);
    Alvo->ano = atoi(_ano);
}

int contadorCodEm() {
    int aux = 0;
    FILE *arquivo;
    arquivo = fopen("emprestimos", "rb");
    CAD_EMP em;
    if(arquivo == NULL) {
        printf("\n\n  Problemas na abertura do arquivo!\n");
    } else
        while(fread(&em, sizeof(CAD_EMP), 1,arquivo) == 1) {
            if(&(em.cod_emprestimo) != NULL) {
                aux++;
            }
        }
    fclose(arquivo);
    return aux;
}

int veri_cpf(int cod) {
    FILE *arquivo;
    arquivo = fopen("cad_alunos.txt", "rb");
    verificadorArquivo(arquivo);
    CAD_ALUNOS al;
    while(fread(&al, sizeof(CAD_ALUNOS), 1, arquivo) == 1) {
        if(cod == al.matricula) {
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
    return 0;
}

int verificarcod(int aux){
    int a = 0;
    FILE *arquivo;
    arquivo = fopen("emprestimo", "rb");
    CAD_EMP em;
    verificadorArquivo(arquivo);
    while(fread(&em, sizeof(CAD_EMP), 1, arquivo) == 1) {
        if(aux == em.cod_emprestimo){
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
}

void cadastrarEmprestimos() {
    system("cls");
    char dataatual[9];
    // pega a data atual
    _strdate( dataatual);
    DAT atual;
    p_data(dataatual, &atual);
    int ano = atual.ano;
    int dia = atual.dia;
    int mes = atual.mes;
    int cod = 0, aux = 0, x = 0, i = 0;
    FILE *arquivo;
    FILE *livro;
    FILE *aluno; //FILE (sempre maiuscula), vari�vel do tipo file (arquivo � o nome do ponteiro), nesta linha est� sendo criado o ponteiro
    CAD_EMP em;
    CAD_LIVROS li;
    CAD_ALUNOS al;
    arquivo = fopen ("emprestimos", "a+b");// "ab" acrescenta dados bin�rios no fim do arquivo e se o arquivo n�o existir ele ser� criado e
    livro = fopen("cad_livros.txt", "r+b");
    aluno = fopen("cad_alunos.txt", "rb");
    verificadorArquivo(arquivo);
    verificadorArquivo(livro);
    verificadorArquivo(aluno);
    menuCIMA(29);
    menuOPCAO(" REALIZANDO EMPRESTIMO", 29);
    menuBAIXO(29);
    char op;
    printf("\n\n Digite o codigo do livro que deseja realizar o emprestimo: ");
    scanf("%d", &cod);
    while(fread(&li, sizeof(CAD_LIVROS), 1, livro)==1) {
        aux++;
        if(cod == li.codigo) {
            li.quantidade = li.quantidade - 1;
            if(li.quantidade < 0) {
                printf("Sem livro para emprestimo.\n");
                system("pause");
                return;
            } else {
                fseek(livro,(aux-1)*sizeof(CAD_LIVROS),SEEK_SET);
                fwrite(&li,sizeof(CAD_LIVROS), 1,livro);
            }
            break;
        }
    }
    printf("\n\n Digite a Matricula do Aluno que deseja realizar o emprestimo: ");
    scanf("%d", &cod);
    //continuar a fazer a busca para saber se os alunos tem o mesmo CPF
    x = veri_cpf(cod);
    if(x != 1) {
        system("cls");
        printf("\n\n  Matricula nao existe!\n");
        system("pause");
        return;
    } else {
        while(fread(&al, sizeof(CAD_ALUNOS), 1, aluno)==1) {
            x = al.matricula;
            if(cod == al.matricula) {
                em.matricula_aluno = al.matricula;
                strcpy(em.nome_aluno, al.nome);
                break;
            }
        }
        //Verificando se o aluno ja tem mais de 2 emprestimos
        while(fread(&em, sizeof(CAD_EMP), 1, arquivo) == 1) {
            if(cod == em.matricula_aluno) {
                i++;
            }
        }
        if(i >= 2) {
            system("cls");
            printf("\n\n Nao foi possivel realizar o Emprestimo aluno, devido a quantidade maxima de Emprestimos\n");
            system("pause");
            return;
        } else {
            aux = contadorCodEm();
            system("cls");
            menuCIMA(30);
            menuOPCAO("     DADOS DO EMPRESTIMO", 30);
            menuBAIXO(30);
            printf("\n Codigo do Emprestimo: %d\n", codEmprestimo);
            codEmprestimo = codEmprestimo + aux;
            printf("\n Codigo do Livro: %d\n", li.codigo);
            printf("\n Nome do Livro: %s\n", strupr(li.nome_livro));
            printf("\n Matricula do Aluno: %d\n", em.matricula_aluno);
            printf("\n Nome do Aluno: %s\n", strupr(em.nome_aluno));
            printf("\n Data do Emprestimo: %d/%d/%d\n\n", dia, mes, ano);
            em.dia_em = dia;
            em.mes_em = mes;
            em.ano_em = ano;
            menuCIMA(41);
            dia = dia + 10;
            if(dia > 30) {
                dia = dia % 30;
                mes = mes + 1;
                if(mes > 12) {
                    mes = 1;
                    ano = ano + 1;
                }
            }
            printf(" %c Data da Devolucao do Emprestimo: %d/%d/%d %c\n", 186, dia, mes, ano, 186);
            menuBAIXO(41);
            menuCIMA(40);
            menuOPCAO("    Emprestimo Salvo com Sucesso!", 40);
            menuBAIXO(40);
            em.cod_livro = li.codigo;
            strcpy(em.nome_livro, li.nome_livro);
            //em.matricula_aluno = al.matricula;
            //strcpy(em.nome_aluno, al.nome);
            em.diadev = dia;
            em.mesdev = mes;
            em.anodev = ano;
            em.cod_emprestimo = codEmprestimo;
            fwrite(&em, sizeof(CAD_EMP), 1, arquivo);
        }
    }

    fclose(arquivo); //Fecha o arquivo que foi aberto.
    fclose(livro);
    fclose(aluno);
    system("pause");
    system("cls");
}

void listartodos() {
    int x = 0;
    FILE *arquivo;
    arquivo = fopen("emprestimos", "rb");
    CAD_EMP em;
    menuCIMA(27);
    menuOPCAO("  LISTAGEM DE EMPRESTIMOS", 27);
    menuBAIXO(27);
    while(fread(&em, sizeof(CAD_EMP), 1,arquivo)==1) {
        printf("\n Codigo do Emprestimo: %d\n", em.cod_emprestimo);
        printf("\n Matricula do Aluno: %d\n", em.matricula_aluno);
        printf("\n Nome do Aluno: %s\n", em.nome_aluno);
        printf("\n Codigo do Livro: %d\n", em.cod_livro);
        printf("\n Nome do Livro: %s\n", em.nome_livro);
        printf("\n Data do Emprestimo do Livro: %d/%d/%d\n", em.dia_em, em.mes_em, em.ano_em);
        printf("\n Data da Devolucao do Livro: %d/%d/%d\n\n", em.diadev, em.mesdev, em.anodev);
        printf("---------------------------------------------\n\n");
        x++;
    }
    if(x == 0) {
        printf("\n\n  LISTA VAZIA!\n\n\n");
    }
    menuCIMA(32);
    menuOPCAO(" FIM DA LISTAGEM DE EMPRESTIMOS", 32);
    menuBAIXO(32);
    system("pause");
    system("cls");
    fclose(arquivo);
    return;
}

void listar_por_Alunos() {
    int aux;
    int x = 0;
    FILE *arquivo;
    arquivo = fopen("emprestimos", "rb");
    CAD_EMP em;
    menuCIMA(36);
    menuOPCAO(" LISTAGEM DE EMPRESTIMOS POR ALUNO", 36);
    menuBAIXO(36);
    printf("\n\n Digite a Matricula do Aluno: ");
    scanf("%d", &aux);
    while(fread(&em, sizeof(CAD_EMP), 1,arquivo)==1) {
        if(aux == em.matricula_aluno) {
            printf("\n Matricula do Aluno: %d\n", em.matricula_aluno);
            printf("\n Nome do Aluno: %s\n", em.nome_aluno);
            printf("\n Codigo do Livro: %d\n", em.cod_livro);
            printf("\n Nome do Livro: %s\n", em.nome_livro);
            printf("\n Data do Emprestimo do Livro: %d/%d/%d\n", em.dia_em, em.mes_em, em.ano_em);
            printf("\n Data da Devolucao do Livro: %d/%d/%d\n\n", em.diadev, em.mesdev, em.anodev);
            printf("---------------------------------------------\n\n");
            x++;
        }
    }
    if(x == 0) {
        printf("\n\n  LISTA VAZIA!\n\n\n");
    }
    menuCIMA(32);
    menuOPCAO(" FIM DA LISTAGEM DE EMPRESTIMOS", 32);
    menuBAIXO(32);
    system("pause");
    system("cls");
    fclose(arquivo);
    return;
}

void listar_por_livros() {
    int aux;
    int x = 0;
    FILE *arquivo;
    arquivo = fopen("emprestimos", "rb");
    CAD_EMP em;
    menuCIMA(36);
    menuOPCAO(" LISTAGEM DE EMPRESTIMOS POR LIVRO", 36);
    menuBAIXO(36);
    printf("\n\n Digite o Codigo do Livro: ");
    scanf("%d", &aux);
    while(fread(&em, sizeof(CAD_EMP), 1,arquivo) == 1) {
        if(aux == em.cod_livro) {
            printf("\n Matricula do Aluno: %d\n", em.matricula_aluno);
            printf("\n Nome do Aluno: %s\n", em.nome_aluno);
            printf("\n Codigo do Livro: %d\n", em.cod_livro);
            printf("\n Nome do Livro: %s\n", em.nome_livro);
            printf("\n Data do Emprestimo do Livro: %d/%d/%d\n", em.dia_em, em.mes_em, em.ano_em);
            printf("\n Data da Devolucao do Livro: %d/%d/%d\n\n", em.diadev, em.mesdev, em.anodev);
            printf("---------------------------------------------\n\n");
            x++;
        }
    }
    if(x == 0) {
        printf("\n\n  LISTA VAZIA!\n\n\n");
    }
    menuCIMA(32);
    menuOPCAO(" FIM DA LISTAGEM DE EMPRESTIMOS", 32);
    menuBAIXO(32);
    system("pause");
    system("cls");
    fclose(arquivo);
    return;
}

void devolucao() {
    int aux=0,j =0,i=0;
    char auxlivro[50];
    FILE *arquivo;
    FILE *livro;
    CAD_EMP em;
    CAD_LIVROS li;
    arquivo = fopen("emprestimos", "rb");
    livro = fopen("cad_livros.txt", "r+b");
    verificadorArquivo(arquivo);
    if(livro == NULL){
        printf("\n\n  Nao ha livro para devolver!");
        system("pause");
        system("cls");
        fclose(arquivo);
        fclose(livro);
        return;
    }
    menuCIMA(60);
    menuOPCAO("  Qual Codigo do Emprestimo que Deseja fazer a Devolucao:", 60);
    menuBAIXO(60);
    gotoXY(60, 1);
    scanf("%d", &aux);
    while(fread(&em, sizeof(CAD_EMP), 1, arquivo)==1) {
        if(aux == em.cod_emprestimo) {
            j = em.cod_livro;
            break;
        }
    }
    system("cls");
    while(fread(&li, sizeof(CAD_LIVROS), 1, livro) == 1) {
        i++;
        if(em.cod_livro == li.codigo) {
            li.quantidade = li.quantidade + 1;
            fseek(livro,(i-1)*sizeof(CAD_LIVROS),SEEK_SET);
            if(fwrite(&li, sizeof(CAD_LIVROS), 1, livro) != 1) {
                menuCIMA(27);
                menuOPCAO("  Falha ao fazer devolucao!", 27);
                menuBAIXO(27);
                system("pause");
                printf("\n\n%s\n\n", strerror(errno));
            } else {
                menuCIMA(20);
                menuOPCAO("  Devolucao feita com Sucesso!", 20);
                menuBAIXO(20);
                system("pause");
            }
            break;
        }
    }
    system("cls");
    fclose(arquivo);
    fclose(livro);
    return;
}

void cancelar() {
    CAD_EMP em;
    int i = 0;
    int auxiliar;
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo = fopen("emprestimos", "a+b");
    FILE *arq_auxiliar = fopen("auxiliar", "w+b");
    if(arquivo == NULL || arq_auxiliar == NULL) {
        printf("\n\n Impossivel abrir o arquivo!\n");
    } else {
        fflush(stdin);
        printf("\n\n  Digite o Codigo do Emprestimo que deseja Cancelar: ");
        scanf("%d", &auxiliar);
        while(fread(&em, sizeof(CAD_EMP), 1, arquivo) == 1) {
            i++;
            if(auxiliar == em.cod_emprestimo) {
                fseek(arquivo,(i - 1) * sizeof(CAD_EMP),SEEK_SET);
            } else {
                fwrite(&em,sizeof(CAD_EMP), 1, arq_auxiliar);
            }
        }
        fclose(arquivo);
        fclose(arq_auxiliar);
        if(remove("emprestimos") == 0) {
            rename("auxiliar", "emprestimos");
            menuCIMA(40);
            menuOPCAO("Emprestimo Cancelado com Sucesso", 40);
            menuBAIXO(40);
            system("pause");
        } else {
            printf("Nao foi possivel Cancelar o Emprestimo!\n");
            printf("\n\n%s\n\n", strerror(errno));
            system("pause");
        }
        system("cls");
    }
    fclose(arquivo);
    fclose(arq_auxiliar);
    return;
}

void listar_emprestimos() {
    int op = 0;
    do {
        menuCIMA(33);
        menuOPCAO("     LISTAGEM DE EMPRESTIMOS", 33);
        menuOPCAO("", 33);
        menuOPCAO(" 1 - Listar Todos Emprestimos", 33);
        menuOPCAO("", 33);
        menuOPCAO(" 2 - Listar Por Livro Especifico", 33);
        menuOPCAO("", 33);
        menuOPCAO(" 3 - Listar Por Aluno Especifico", 33);
        menuOPCAO("", 33);
        menuOPCAO(" 4 - Sair", 33);
        menuOPCAO("", 33);
        menuBAIXO(33);
        menuCIMA(10);
        menuOPCAO(" OPCAO:", 10);
        menuBAIXO(10);
        gotoXY(10, 13);
        setbuf(stdin, NULL);
        scanf("%d", &op);
        system("cls");
        switch(op) {
        case 1:
            listartodos();
            break;
        case 2:
            listar_por_livros();
            break;
        case 3:
            listar_por_Alunos();
            break;
        case 4:
            return;
            break;
        default:
            printf("\n\n  Opcao invalida\n");
            system("pause");
            break;
        }
    } while(op != 4);
    return;
}

//Fun��o para verificar que op��o vai ser usada no menu aluno

void op_emprestimos () {
    int o = 0;
    struct emprestimos em;
    do {
        menuCIMA(32);
        menuOPCAO("           EMPRESTIMOS", 32);
        menuOPCAO("", 32);
        menuOPCAO(" 1 - Novo Emprestimo", 32);
        menuOPCAO("", 32);
        menuOPCAO(" 2 - Confirma Devolucao", 32);
        menuOPCAO("", 32);
        menuOPCAO(" 3 - Cancelar Emprestimo", 32);
        menuOPCAO("", 32);
        menuOPCAO(" 4 - Listar Emprestimos", 32);
        menuOPCAO("", 32);
        menuOPCAO(" 5 - Ir para menu anterior", 32);
        menuOPCAO("", 32);
        menuBAIXO(32);
        menuCIMA(10);
        menuOPCAO(" OPCAO: ", 10);
        menuBAIXO(10);
        gotoXY(10, 15);
        scanf("%d", &o);
        system("cls");
        switch(o) {
        case 1:
            cadastrarEmprestimos();
            break;
        case 2:
            devolucao();
            break;
        case 3:
            cancelar();
            break;
        case 4:
            listar_emprestimos();
            break;
        case 5:
            return;
            break;
        default:
            printf("\n\n  Opcao invalida\n");
            system("pause");
            break;
        }
    } while(o != 5);
}
main() {
    int i, j, op;
    menuCIMA(116);
    printf("                                    ...:::::  BIBLIOTECA CENTRAL DA UEPB  :::::...");
    gotoXY(0, 28);
    menuBAIXO(55);
    gotoXY(0, 24);
    menuCIMA(23);
    menuOPCAO(" Carregando Sistema...", 23);
    menuBAIXO(23);
    for (i = 1; i <= 50; i++) {
        printf ("  %d%%\r", i*2);
        for (j = 0; j < i; j++) {
            if (j == 0)
                printf("  ");
            printf ("%c", 177);
            Sleep(2);
        }
    }
    gotoXY(26, 26);
    system("cls");
    do {
        op = menu_principal();
        system("cls");
        setbuf(stdin, NULL);
        switch(op) {
        case 1:
            op_alunos();
            break;
        case 2:
            op_acervo();
            break;
        case 3:
            op_emprestimos();
            break;
        case 4:
            menuCIMA(24);
            menuOPCAO(" Finalizando Sistema...", 24);
            menuBAIXO(24);
            system("pause");
            exit(0);
        default:
            system("cls");
            printf("\n\n Opcao incorreta!\n\n");
            system("pause");
            system("cls");
            break;
        }
    } while(op != 4);
    return 0;
}

