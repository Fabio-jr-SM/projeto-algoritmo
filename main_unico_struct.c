//O codigo a seguir depende que os arquivos sejam criados. é posssivel fazer inserção de telefones em outro arquivo
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>
#define INFINITY (1<<20)

typedef struct p{
    int IDPessoa;
    char nome[31];
    char email[31];
    char cpf[12];
    char dataNascimento[11];
	char **telefones;
    int numTelefones;
} PESSOA;

void carregaArquivo();
void imprimeArquivo();
void editaArquivo();
void excluiArquivo();
void cadastraArquivo();
void cadastrarTelefones();
void liberarTelefones();
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
            
            int op_cadastro_tel;
            PESSOA novoTelefone;
            char nome_comparacao[31];
            int ID_comparacao, encontrouID = 0,encontrouNOME=0;
            
            printf("\n(1) Cadastrar usando o Nome\n(2) Cadastrar usando o ID\n(3) Return\n");
            scanf("%d",&op_cadastro_tel);
            
            if(op_cadastro_tel==1){
                printf("Digite o nome: ");
                scanf("%s",nome_comparacao);
                for(int i = 0; i<cont; i++)
                {
                    if(strcmp(nome_comparacao, lista[i].nome) == 0)
                    {
                       
                        cadastrarTelefones(&novoTelefone);
                        lista[i].telefones = novoTelefone.telefones;
                        lista[i].numTelefones = novoTelefone.numTelefones;
                        /*printf("%s, Digite o telefone: ",lista[i].nome);
                        scanf("%s",novoTelefone.telefone);
                        
                        arquivo = fopen("pessoa.txt", "w+");
                        
                        for(int i; i<cont;i++){
                            fprintf(arquivo, "%d ; %s ; %s ; %s ; %s ; %s\n", lista[i].IDPessoa, lista[i].nome,lista[i].email, lista[i].cpf, lista[i].dataNascimento, novoTelefone.telefone);
                        }
                        fclose(arquivo);
                        
                        carregaArquivo();*/
                        encontrouNOME = 1;
                        
                        if (novoTelefone.numTelefones > 0) {
                            printf("Telefones:\n");
                            for (int i = 0; i < novoTelefone.numTelefones; i++) {
                                printf("%d. %s\n", i + 1, novoTelefone.telefones[i]);
                            }
                        }
                    }

                    if(encontrouNOME!=1){
                        printf("Nome inexistente\n");
                    }
                }
            }else if(op_cadastro_tel==2){
                int i;

                printf("\nDigite o ID da pessoa: ");
                scanf("%d",&ID_comparacao);

                for(i = 0; i<cont; i++)
                {
                    if(lista[i].IDPessoa == ID_comparacao)
                    {
                        
                        cadastrarTelefones(&novoTelefone);
                        lista[i].telefones = novoTelefone.telefones;
                        lista[i].numTelefones = novoTelefone.numTelefones;
                        /*printf("%s, Digite o telefone: ",lista[i].nome);
                        scanf("%s",novoTelefone.telefone);
                        
                        arquivo = fopen("pessoa.txt", "w+");
                        for(int i; i<cont;i++){
                            fprintf(arquivo, "%d ; %s ; %s ; %s ; %s ; %s\n", lista[i].IDPessoa, lista[i].nome,lista[i].email, lista[i].cpf, lista[i].dataNascimento, novoTelefone.telefone);
                        }
                        fclose(arquivo);
                        
                        carregaArquivo();*/
                        
                        encontrouID = 1; 
                        
                        if (novoTelefone.numTelefones > 0) {
                            printf("Telefones:\n");
                            for (int i = 0; i < novoTelefone.numTelefones; i++) {
                                printf("%d. %s\n", i + 1, novoTelefone.telefones[i]);
                            }
                        }

                    }
                }
                
                if(encontrouID!=1){
                    printf("ID inexistente\n");
                }
            }
           // liberarTelefones(&novoTelefone);
            
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
        fprintf(arquivo, "%d ; %s ; %s ; %s ; %s\n", lista[i].IDPessoa, lista[i].nome,lista[i].email, lista[i].cpf, lista[i].dataNascimento);
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
            fprintf(arquivo, "%d ; %s ; %s ; %s ; %s\n", lista[i].IDPessoa, lista[i].nome,lista[i].email, lista[i].cpf, lista[i].dataNascimento);
        }
    }
    fclose(arquivo);
}


//====IMPRIME CADASTROS====
void imprimeArquivo()
{
    int i;
     printf("| %-2s | %-30s | %-30s | %-12s | %-11s |\n", "ID", "Nome", "Email","CPF","Nascimento");
    for(i = 0; i<cont; i++)
    {
        printf("| %-2d | %-30s | %-30s | %-12s | %-11s |\n", lista[i].IDPessoa, lista[i].nome,lista[i].email, lista[i].cpf, lista[i].dataNascimento);
        
        if (lista[i].numTelefones > 0) {
            printf("Telefones:\n");
            for (int j = 0; j < lista[i].numTelefones; j++) {
                printf("%d. %s\n", j + 1, lista[i].telefones[j]);
            }
        }
    }
}


// Função para cadastrar telefones dinamicamente
void cadastrarTelefones(PESSOA *novoTelefone) {
    char resposta;

    // Alocando inicialmente espaço para 5 telefones
    novoTelefone->telefones = (char **)malloc(5 * sizeof(char *));
    novoTelefone->numTelefones = 0;

    do {
        // Alocando espaço para armazenar um telefone
        novoTelefone->telefones[novoTelefone->numTelefones] = (char *)malloc(15 * sizeof(char));

        printf("Digite o telefone: ");
        scanf("%s", novoTelefone->telefones[novoTelefone->numTelefones]);

        novoTelefone->numTelefones++;

        // Perguntando se o usuário deseja cadastrar outro telefone
        printf("Deseja cadastrar outro telefone? (s/n): ");
        scanf(" %c", &resposta);
    } while (resposta == 's');


}

// Função para liberar a memória alocada para os telefones
void liberarTelefones(PESSOA *novoTelefone) {
    for (int i = 0; i < novoTelefone->numTelefones; i++) {
        free(novoTelefone->telefones[i]);
    }
    //free(novoTelefone->telefones);
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
