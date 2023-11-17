//Adiconado dados de telefone e email
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define INFINITY (1<<20)

typedef struct p
{
    int IDPessoa;
    char nome[31];
    char telefone[12];
    char email[31];
    char cpf[12];
    char dataNascimento[11];
} PESSOA;

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
        while(fscanf(arquivo,"%d ; %s ; %s ; %s ; %s ; %s", &lista[cont].IDPessoa, lista[cont].nome,lista[cont].telefone,lista[cont].email, lista[cont].cpf, lista[cont].dataNascimento)!= EOF){
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
        printf("%d ; %s ; %s ; %s ; %s ; %s\n", lista[i].IDPessoa, lista[i].nome,lista[i].telefone,lista[i].email, lista[i].cpf, lista[i].dataNascimento);
    }
}

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
    for(i = 0; i<cont; i++)
    {
        fprintf(arquivo, "%d ; %s ; %s ; %s ; %s ; %s\n", lista[i].IDPessoa, lista[i].nome,lista[i].telefone,lista[i].email, lista[i].cpf, lista[i].dataNascimento);
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
            fprintf(arquivo, "%d ; %s ; %s ; %s ; %s ; %s\n", lista[i].IDPessoa, lista[i].nome,lista[i].telefone,lista[i].email, lista[i].cpf, lista[i].dataNascimento);
        }
    }
    fclose(arquivo);
}

void cadastraArquivo()
{
    PESSOA novaPessoa;
    printf("Digite o nome\n");
    scanf("%s", novaPessoa.nome);
    printf("Digite o Telefone\n");
    scanf("%s", novaPessoa.telefone);
    printf("Digite o Email\n");
    scanf("%s", novaPessoa.email);
    printf("Digite o CPF\n");
    scanf("%s", novaPessoa.cpf);
    printf("Digite a data de nascimento\n");
    scanf("%s", novaPessoa.dataNascimento);
    
    arquivo = fopen("pessoa.txt", "a+");
    fprintf(arquivo, "%d ; %s ; %s ; %s ; %s ; %s\n", ultimoID()+1, novaPessoa.nome,novaPessoa.telefone,novaPessoa.email, novaPessoa.cpf, novaPessoa.dataNascimento);
    fclose(arquivo);
    
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
