#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>

#define INFINITY (1<<20);

typedef struct p
{
    int IDPessoa;
    char nome[31];
    char cpf[12];
    char dataNascimento[11];
} PESSOA;

void menu();
void criarArquivo();
void carregaArquivo();
void imprimeArquivo();
void editaArquivo();
void excluiArquivo();
void cadastraArquivo();
int ultimoID();


PESSOA lista[100];
int cont;
FILE *arquivo;

//Criar arquivo e escrever nele no formato %d ; %s ; %s ; %s
void criarEscreverArquivo(){
    arquivo = fopen("pessoa.txt", "w+");
    int i;
    //Laço de repetição responsável por percorrer o vetor
    for(i = 0; i<cont; i++)
    {
        //Escreve no arquivoNovo.txt seguindo um novo formato
        fprintf(arquivo, "%d ; %s ; %s ; %s\n", lista[i].IDPessoa, lista[i].nome, lista[i].cpf, lista[i].dataNascimento);
    }
    //Fecha os dois arquivos que foram abertos com a função fopen
    fclose(arquivo);
}

void carregaArquivo()
{
    cont = 0;
    arquivo = fopen("pessoa.txt", "r+");
    while(fscanf(arquivo,"%d ; %s ; %s ; %s", &lista[cont].IDPessoa, lista[cont].nome, lista[cont].cpf, lista[cont].dataNascimento)!= EOF)
    {
        cont++;
    }
    fclose(arquivo);
}

//1 - CADASTRAR
void cadastraArquivo()
{
    int op;
    printf("1 - Cadastrar Pessoa\n2 - Cadastrar Telefone\n");
    scanf("%d",&op);
    
    if(op==1){
        PESSOA novaPessoa;
        //Cadastrar o registro na memória
        printf("Digite o nome\n");
        scanf("%s", novaPessoa.nome);
        printf("Digite o CPF\n");
        scanf("%s", novaPessoa.cpf);
        printf("Digite a data de nascimento\n");
        scanf("%s", novaPessoa.dataNascimento);
        
        criarEscreverArquivo();
    } 
}


//2 - EDITAR
void editaArquivo()
{
    //Alterar o registro na memória
    
    int i;
    int IDPessoaAlteracao;
    printf("Digite o ID para alteracao\n");
    scanf("%d", &IDPessoaAlteracao);
    for(i = 0; i<cont; i++)
    {
        if(lista[i].IDPessoa == IDPessoaAlteracao)
        {
            printf("Digite o nome\n");
            scanf("%s", lista[i].nome);
            break;
        }
    }
    
    arquivo = fopen("pessoa.txt", "w+");
    //Laço de repetição responsável por percorrer o vetor
    for(i = 0; i<cont; i++)
    {
        //Escreve no arquivoNovo.txt seguindo um novo formato
        fprintf(arquivo, "%d ; %s ; %s ; %s\n", lista[i].IDPessoa, lista[i].nome, lista[i].cpf, lista[i].dataNascimento);
    }
    //Fecha os dois arquivos que foram abertos com a função fopen
    fclose(arquivo);
}

//3 - EXCLUIR
void excluiArquivo()
{
    //Excluir o registro na memória
    arquivo = fopen("pessoa.txt", "w+");
    int IDPessoaExclusao;
    printf("Digite o ID para exclusao\n");
    scanf("%d", &IDPessoaExclusao);
    int i;
    for(i = 0; i<cont; i++)
    {
        if(lista[i].IDPessoa != IDPessoaExclusao)
        {
            fprintf(arquivo, "%d ; %s ; %s ; %s\n", lista[i].IDPessoa, lista[i].nome, lista[i].cpf, lista[i].dataNascimento);
        }
    }
    fclose(arquivo);
}

//4 - CONSULTAR
void imprimeArquivo()
{
    int i;
    for(i = 0; i<cont; i++)
    {
        printf("%d ; %s ; %s ; %s\n", lista[i].IDPessoa, lista[i].nome, lista[i].cpf, lista[i].dataNascimento);
    }
}

int ultimoID()
{
    int maiorID = -INFINITY;
    int i;
    for(i = 0; i<cont; i++)
    {
        if(lista[i].IDPessoa > maiorID)
        {
            maiorID = lista[i].IDPessoa;
        }
    }
}

//VOID MENU
void menu()
{
    int menu;
    do{
        printf("1 - Cadastrar\n");
        printf("2 - Editar\n");
        printf("3 - Excluir\n");
        printf("4 - Consultar\n");
        printf("5 - Sair\n");
        
        carregaArquivo();
        scanf("%d", &menu);
        switch(menu)
        {
            case 1:
                printf("CADASTRA\n");
                cadastraArquivo();
                break;
            case 2:
                printf("EDITA\n");
                editaArquivo();
                break;
            case 3:
                printf("EXCLUI\n");
                excluiArquivo();
                break;
            case 4:
                printf("IMPRIME\n");
                imprimeArquivo();
                break;
            case 5:
                printf("SAINDO!!!");
                break;
            default:
                printf("Menu invalido\n");
        }
    }while(menu != 5);
}

int main()
{
    menu();
    return 0;
}
