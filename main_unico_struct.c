//Erro na linha 103. o codigo não finaliza o cadastro do telefone
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#define INFINITY (1<<20)

typedef struct p
{
    int IDPessoa;
    char nome[31];
    char email[31];
    char cpf[12];
    char dataNascimento[11];
	char telefone[12];
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


//====CARREGA ARQUIVO====
void carregaArquivo()
{
    
    cont = 0;
    arquivo = fopen("pessoa.txt", "r+");
    
    if (arquivo != NULL) {
        //printf("Entrou aqui");
        ///rewind(arquivo);
        while(fscanf(arquivo,"%d ; %s ; %s ; %s ; %s", &lista[cont].IDPessoa, lista[cont].nome,lista[cont].email, lista[cont].cpf, lista[cont].dataNascimento)!= EOF){
            //printf("%d ; %s ; %s ; %s ; %s\n", lista[cont].IDPessoa, lista[cont].nome,lista[cont].email, lista[cont].cpf, lista[cont].dataNascimento);
            cont++;
        }
        fclose(arquivo);           
    }else{
        printf("\nNão foi possivel abrir o arquivo\n");
        exit(0);
    }
}


//====CADASTRA USUARIO====
void cadastraArquivo()
{
    int op;
    printf("\n(1) Cadastrar pessoa\n(2) Cadastrar Telefone\n(3) Return\n");
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
            fprintf(arquivo, "%d ; %s ; %s ; %s ; %s\n", ultimoID()+1, 
            novaPessoa.nome,novaPessoa.email, novaPessoa.cpf, novaPessoa.dataNascimento);
            fclose(arquivo);
            
            carregaArquivo();
        }else if(op==2){
            
            imprimeArquivo();
            
            PESSOA novoTelefone;
            int ID_comparacao;
            bool encontrouID = false;
            
            printf("\nDigite o ID da pessoa: ");
            scanf("%d",&ID_comparacao);
            
            int i;
            for(i = 0; i<cont; i++)
            {
                if(lista[i].IDPessoa == ID_comparacao)
                {
                    printf("%s, Digite o telefone: ",lista[i].nome);
                    scanf("%s",novoTelefone.telefone);
                    
                    arquivo = fopen("pessoa.txt", "w+");
                    fprintf(arquivo, "%d ; %s ; %s ; %s ; %s ; %s\n", lista[i].IDPessoa, lista[i].nome,lista[i].email, lista[i].cpf, lista[i].dataNascimento, novoTelefone.telefone);
                    fclose(arquivo);
                    
                    carregaArquivo();
                    
                    encontrouID = true; 
                    break; 

                }
            }
            
            if(!encontrouID){
                printf("ID inexistente\n");
            }
            
        }
        printf("\n(1) Cadastrar pessoa\n(2) Cadastrar Telefone\n(3) Return\n");
        scanf("%d",&op);
    }
}


//====EDITA USUARIO====
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
        fprintf(arquivo, "%d ; %s ; %s ; %s ; %s ; %s\n", lista[i].IDPessoa, lista[i].nome,lista[i].email, lista[i].cpf, lista[i].dataNascimento, lista[i].telefone);
    }
    fclose(arquivo);
}


//====EXCLUI USUARIO====
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
            fprintf(arquivo, "%d ; %s ; %s ; %s ; %s ; %s\n", lista[i].IDPessoa, lista[i].nome,lista[i].email, lista[i].cpf, lista[i].dataNascimento,lista[i].telefone);
        }
    }
    fclose(arquivo);
}


//====IMPRIME CADASTROS====
void imprimeArquivo()
{
    int i;
     printf("| %-2s | %-30s | %-30s | %-12s | %-11s | %-11s |\n", "ID", "Nome", "Email","CPF","Nascimento","telefone");
    for(i = 0; i<cont; i++)
    {
        printf("| %-2d | %-30s | %-30s | %-12s | %-11s | %-11s |\n", lista[i].IDPessoa, lista[i].nome,lista[i].email, lista[i].cpf, lista[i].dataNascimento,lista[i].telefone);
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
        carregaArquivo();
        printf("\n============CADASTRO TELEFONICO============\n");
        printf("1 - Cadastrar\n");
        printf("2 - Editar\n");
        printf("3 - Excluir\n");
        printf("4 - Consultar\n");
        printf("5 - Sair\n");
        
        scanf("%d", &menu);
        switch(menu)
        {
            case 1:
                system("clear");
                printf("\n====CADASTRA USUARIO====\n");
                cadastraArquivo();
                break;
            case 2:
                system("clear");
                printf("\n====EDITA USUARIO====\n");
                editaArquivo();
                break;
            case 3:
                system("clear");
                printf("\n====EXCLUI USUARIO====\n");
                excluiArquivo();
                break;
            case 4:
                system("clear");
                printf("\n====IMPRIME CADASTROS====\n");
                imprimeArquivo();
                break;
            case 5:
                system("clear");
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
