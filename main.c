//Adiconado dados de telefone e email
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define INFINITY (1<<20)

typedef struct p
{
    int IDPessoa;
    char nome[31];
    char email[31];
    char cpf[12];
    char dataNascimento[11];
} PESSOA;

typedef struct t
{
    int idTelefone, idPessoa;
	char telefone[12];
} TELEFONE;


void carregaArquivo();
void imprimeArquivo();
void editaArquivo();
void excluiArquivo();
void cadastraArquivo();
int ultimoID();


PESSOA lista[100];
int cont;
FILE *arquivo;

void carregaArquivo()
{
    
    cont = 0;
    arquivo = fopen("pessoa.txt", "r+");
    
    if (arquivo != NULL) {
        while(fscanf(arquivo,"%d ; %s ; %s ; %s ; %s", &lista[cont].IDPessoa, lista[cont].nome,lista[cont].email, lista[cont].cpf, lista[cont].dataNascimento)!= EOF){
            cont++;
        }
        fclose(arquivo);
    }else{
        arquivo = fopen("pessoa.txt", "w+");
        fclose(arquivo);
    }
}

void imprimeArquivo()
{
    int i;
    for(i = 0; i<cont; i++)
    {
        printf("%d ; %s ; %s ; %s ; %s\n", lista[i].IDPessoa, lista[i].nome,lista[i].email, lista[i].cpf, lista[i].dataNascimento);
    }
}

void editaArquivo()
{
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
    for(i = 0; i<cont; i++)
    {
        fprintf(arquivo, "%d ; %s ; %s ; %s ; %s \n", lista[i].IDPessoa, lista[i].nome,lista[i].email, lista[i].cpf, lista[i].dataNascimento);
    }
    fclose(arquivo);
}

void excluiArquivo()
{
    arquivo = fopen("pessoa.txt", "w+");
    int IDPessoaExclusao;
    printf("Digite o ID para exclusao\n");
    scanf("%d", &IDPessoaExclusao);
    int i;
    for(i = 0; i<cont; i++)
    {
        if(lista[i].IDPessoa != IDPessoaExclusao)
        {
            fprintf(arquivo, "%d ; %s ; %s ; %s ; %s\n", lista[i].IDPessoa, lista[i].nome,lista[i].email, lista[i].cpf, lista[i].dataNascimento);
        }
    }
    fclose(arquivo);
}

void cadastraArquivo()
{
    int op;
    printf("\n(1) Cadastrar pessoa\n(2) Cadastrar Telefone\n")
    scanf("%d",&op);
    while(op!=3){
        if(op==1){
            PESSOA novaPessoa;
            printf("Digite o nome: ");
            scanf("%s", novaPessoa.nome);
            printf("Digite o Email: ");
            scanf("%s", novaPessoa.email);
            printf("Digite o CPF: ");
            scanf("%s", novaPessoa.cpf);
            printf("Digite a data de nascimento: ");
            scanf("%s", novaPessoa.dataNascimento);
            
            arquivo = fopen("pessoa.txt", "a+");
            fprintf(arquivo, "%d ; %s ; %s ; %s ; %s\n", ultimoID()+1, novaPessoa.nome,novaPessoa.email, novaPessoa.cpf, novaPessoa.dataNascimento);
            fclose(arquivo);
        }else if(op==2){
            TELEFONE novoTelefone;
            for(int i = 0; i<cont; i++){
                printf("%d ; %s ; %s ; %s ; %s\n", lista[i].IDPessoa, lista[i].nome,lista[i].email, lista[i].cpf, lista[i].dataNascimento);
            }

            printf("Digite o ID: ");
            scanf("")
        }
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

void menu()
{
    int menu;
    do{
        printf("\n============CADASTRO TELEFONICO============\n");
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
                printf("\nCADASTRA\n");
                cadastraArquivo();
                break;
            case 2:
                printf("\nEDITA\n");
                editaArquivo();
                break;
            case 3:
                printf("\nEXCLUI\n");
                excluiArquivo();
                break;
            case 4:
                printf("\nIMPRIME\n");
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
