//É possivel validar os dados dos cadastrados antes de proseguir
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h> 
#define INFINITY (1<<20)
#include <regex.h>
#define EMAIL "([A-Z|a-z|0-9](\\.|_){0,1})+[A-Z|a-z|0-9]\\@([A-Z|a-z|0-9])+((\\.){0,1}[A-Z|a-z|0-9]){2,3}\\.[a-z]{2,3}"
#define TELEFONE "\\([0-9]{2}\\)[0-9]{4,5}-[0-9]{4}"
#define DATA_PATTERN "\\d{2}/\\d{2}/\\d{4}"

typedef struct p{
    int IDPessoa;
    char nome[31];
    char email[31];
    char cpf[12];
    char dataNascimento[11];
        char **telefones;
    int numTelefones;
} PESSOA;

void menu();
void carregaArquivo();
void escreverArquivo();
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

//VALIDACOES DE EXPRESSOES IRREGULARES
int valida_exp_regular(char expreg[], char texto[])
{
	/* aloca espaço para a estrutura do tipo regex_t */
	regex_t reg;

	/* compila a ER passada em argv[1]
	 * em caso de erro, a função retorna diferente de zero */
	if (regcomp(&reg , expreg, REG_EXTENDED|REG_NOSUB) != 0) {
		fprintf(stderr,"erro regcomp\n");
		exit(1);
	}
	/* tenta casar a ER compilada (&reg) com a entrada (argv[2]) 
	 * se a função regexec retornar 0 casou, caso contrário não */
	if ((regexec(&reg, texto, 0, (regmatch_t *)NULL, 0)) == 0)
		return 1;
	else
		return 0;
}

//VALIDAR DATA
int validarData(const char *data) 
{
    regex_t regex;

    if (regcomp(&regex, DATA_PATTERN, REG_EXTENDED) != 0) {
        fprintf(stderr, "Erro ao compilar a expressão regular\n");
        return -1;
    }

    if (regexec(&regex, data, 0, NULL, 0) == 0) {
        //printf("Data válida: %s\n", data);
        regfree(&regex);
        return 0;  // Data válida
    } else {
        //printf("Data inválida: %s\n", data);
        regfree(&regex);
        return 1;  // Data inválida
    }
}

//VALIDAR CPF
int validarCPF(char *cpf)
{
    int i, j, digito1 = 0, digito2 = 0;
    for (i = 0; i < 11; i++)
    {
        if (cpf[i] < 48 || cpf[i] > 57)
            return 1;
    }

    if (strlen(cpf) != 11)
        return 1;
    else if ((strcmp(cpf, "00000000000") == 0) || (strcmp(cpf, "11111111111") == 0) || (strcmp(cpf, "22222222222") == 0) ||
             (strcmp(cpf, "33333333333") == 0) || (strcmp(cpf, "44444444444") == 0) || (strcmp(cpf, "55555555555") == 0) ||
             (strcmp(cpf, "66666666666") == 0) || (strcmp(cpf, "77777777777") == 0) || (strcmp(cpf, "88888888888") == 0) ||
             (strcmp(cpf, "99999999999") == 0))
        return 1;
    else
    {
        for (i = 0, j = 10; i < strlen(cpf) - 2; i++, j--)
            digito1 += (cpf[i] - 48) * j;
        digito1 %= 11;
        if (digito1 < 2)
            digito1 = 0;
        else
            digito1 = 11 - digito1;
        if ((cpf[9] - 48) != digito1)
            return 1;
        else
        {
            for (i = 0, j = 11; i < strlen(cpf) - 1; i++, j--)
                digito2 += (cpf[i] - 48) * j;
            digito2 %= 11;
            if (digito2 < 2)
                digito2 = 0;
            else
                digito2 = 11 - digito2;
            if ((cpf[10] - 48) != digito2)
                return 1;
        }
    }
    return 0;
}


//====CARREGA ARQUIVO (ARQUIVO PARA MEMORIA)====
void carregaArquivo()
{
    cont = 0;
    arquivo = fopen("pessoa.txt", "r+");

    if (arquivo != NULL) {
        while (fscanf(arquivo, "%d ; %s ; %s ; %s ; %s ; %d",
                      &lista[cont].IDPessoa, lista[cont].nome, lista[cont].email,
                      lista[cont].cpf, lista[cont].dataNascimento, &lista[cont].numTelefones) != EOF) {
            if (lista[cont].numTelefones > 0) {
                lista[cont].telefones = (char **)malloc(lista[cont].numTelefones * sizeof(char *));
                for (int i = 0; i < lista[cont].numTelefones; i++) {
                    lista[cont].telefones[i] = (char *)malloc(15 * sizeof(char));
                    fscanf(arquivo, " ; %s", lista[cont].telefones[i]);
                }
            }

            cont++;
        }
        fclose(arquivo);
    } else {
        printf("\nNão foi possível abrir o arquivo\n");
        exit(1);
    }
}

//====CARREGA MEMORIA (MEMORIA PARA ARQUIVO)====
void escreverArquivo()
{
    arquivo = fopen("pessoa.txt", "w+");
    //printf("%d",cont);
    for(int k = 0; k < cont; k++) {
        fprintf(arquivo, "%d ; %s ; %s ; %s ; %s ; %d", lista[k].IDPessoa, lista[k].nome, lista[k].email, lista[k].cpf, lista[k].dataNascimento, lista[k].numTelefones);

        if(lista[k].numTelefones>0){
            for (int p = 0; p < lista[k].numTelefones; p++) {
                fprintf(arquivo, " ; %s", lista[k].telefones[p]);
            }
        }
        fprintf(arquivo, "\n");
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
            
            do{
                printf("Digite o Email: ");
                scanf("%s", novaPessoa.email);
                if(valida_exp_regular(EMAIL,novaPessoa.email)){
                    printf("Válido\n");
                }else{
                    printf("Invalido!\n");
                }
            }while(!valida_exp_regular(EMAIL,novaPessoa.email));
            
            do{
                printf("Digite o CPF: ");
                scanf("%s", novaPessoa.cpf);
                if((validarCPF(novaPessoa.cpf)==0)){
                    printf("Válido\n");
                }else{
                    printf("Invalido!\n");
                }
            }while((validarCPF(novaPessoa.cpf)==1));
            
            do{
                printf("Digite a data de nascimento: ");
                scanf("%s", novaPessoa.dataNascimento);
                if(validarData(novaPessoa.dataNascimento)==1){
                    printf("Válido\n");
                }else{
                    printf("Invalido!\n");
                }
            }while(validarData(novaPessoa.dataNascimento)==0);
            
            novaPessoa.numTelefones = 0;
            arquivo = fopen("pessoa.txt", "a+");
            fprintf(arquivo, "%d ; %s ; %s ; %s ; %s ; %d\n", ultimoID()+1, 
            novaPessoa.nome,novaPessoa.email, novaPessoa.cpf, novaPessoa.dataNascimento,novaPessoa.numTelefones);
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

                        cadastrarTelefones(&novoTelefone,i);
                        lista[i].telefones = novoTelefone.telefones;
                        lista[i].numTelefones = novoTelefone.numTelefones;
                        
                        encontrouNOME = 1;

                        if (novoTelefone.numTelefones > 0) {
                            printf("Telefones:\n");
                            for (int i = 0; i < novoTelefone.numTelefones; i++) {
                                printf("%d. %s\n", i + 1, novoTelefone.telefones[i]);
                            }
                        }
                        escreverArquivo();
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

                        cadastrarTelefones(&novoTelefone,i);
                        lista[i].telefones = novoTelefone.telefones;
                        lista[i].numTelefones = novoTelefone.numTelefones;

                        encontrouID = 1; 

                        if (novoTelefone.numTelefones > 0) {
                            printf("Telefones:\n");
                            for (int i = 0; i < novoTelefone.numTelefones; i++) {
                                printf("%d. %s\n", i + 1, novoTelefone.telefones[i]);
                            }
                        }
                        escreverArquivo();
                    }
                }

                if(encontrouID!=1){
                    printf("ID inexistente\n");
                }
            }
        }
        printf("\n(1) Cadastrar pessoa\n(2) Cadastrar Telefone\n(3) Return\n");
        scanf("%d",&op);
    }

}


// FUNÇÃO PARA CADASTRAR TELEFONES DINAMICAMENTE
void cadastrarTelefones(PESSOA *novoTelefone, int i) 
{
    // Liberar telefones existentes antes de cadastrar novos telefones
    liberarTelefones(i);

    char resposta;

    // Alocando inicialmente espaço para 5 telefones
    novoTelefone->telefones = (char **)malloc(5 * sizeof(char *));
    novoTelefone->numTelefones = 0;  // Inicializa o número de telefones para zero

    do {
        // Alocando espaço para armazenar um telefone
        novoTelefone->telefones[novoTelefone->numTelefones] = (char *)malloc(15 * sizeof(char));
        
        do{
            printf("Digite o telefone: ");
            scanf("%s", novoTelefone->telefones[novoTelefone->numTelefones]);
            if(valida_exp_regular(TELEFONE,novoTelefone->telefones[novoTelefone->numTelefones])){
                printf("Válido\n");
            }else{
                printf("Invalido!\n");
            }
        }while(!valida_exp_regular(TELEFONE,novoTelefone->telefones[novoTelefone->numTelefones]));
        
        
        novoTelefone->numTelefones++;

        printf("Deseja cadastrar outro telefone? (s/n): ");
        scanf(" %c", &resposta);
    } while (resposta == 's');
}


// FUNÇÃO PARA LIBERAR A MEMÓRIA ALOCADA PARA OS TELEFONES
void liberarTelefones(int indice) 
{
    for (int i = 0; i < lista[indice].numTelefones; i++) {
        free(lista[indice].telefones[i]);
    }
    free(lista[indice].telefones);
    lista[indice].telefones = NULL;
    lista[indice].numTelefones = 0;
}


//====EDITA USUARIO====
void editaArquivo()
{
    int i;
    int IDPessoaAlteracao, op_editar, op_alteracao;
    char NomePessoaAlteracao[31];


    do{
        printf("\n(1) Editar usando o Nome\n(2) Editar usando o ID\n(3) Return\n");
        scanf("%d", &op_editar);
        if (op_editar == 1)
        {
            printf("Digite o nome: ");
            scanf("%s", NomePessoaAlteracao);

            for (int i = 0; i < cont; i++)
            {
                if (strcmp(NomePessoaAlteracao, lista[i].nome) == 0)
                {
                    printf("O que deseja alterar:\n (1) Nome\n(2) Data de nascimento\n(3) CPF\n(4) Email\n(5) Return\n");
                    scanf("%d", &op_alteracao);
                    switch (op_alteracao)
                    {
                        case 1:
                            printf("Digite o novo nome: ");
                            scanf("%s", lista[i].nome);
                            escreverArquivo();
                            break;
                        case 2:
                            printf("Digite a data de nascimento: ");
                            scanf("%s", lista[i].dataNascimento);
                            escreverArquivo();
                            break;
                        case 3:
                            printf("Digite o CPF: ");
                            scanf("%s", lista[i].cpf);
                            escreverArquivo();
                            break;
                        case 4:
                            printf("Digite o Email: ");
                            scanf("%s", lista[i].email);
                            escreverArquivo();
                            break;
                        case 5:
                            break;
                        default:
                        printf("Opção inválida");
                    }
                }
            }
        }else if(op_editar==2){
            printf("Digite o ID: ");
            scanf("%d", &IDPessoaAlteracao);

            for (int i = 0; i < cont; i++)
            {
                if (IDPessoaAlteracao == lista[i].IDPessoa)
                {
                    printf("O que deseja alterar:\n (1) Nome\n(2) Data de nascimento\n(3) CPF\n(4) Email\n(5) Return\n");
                    scanf("%d", &op_alteracao);
                    switch (op_alteracao)
                    {
                        case 1:
                            printf("Digite o novo nome: ");
                            scanf("%s", lista[i].nome);
                            escreverArquivo();
                            break;
                        case 2:
                            printf("Digite a data de nascimento: ");
                            scanf("%s", lista[i].dataNascimento);
                            escreverArquivo();
                            break;
                        case 3:
                            printf("Digite o CPF: ");
                            scanf("%s", lista[i].cpf);
                            escreverArquivo();
                            break;
                        case 4:
                            printf("Digite o Email: ");
                            scanf("%s", lista[i].email);
                            escreverArquivo();
                            break;
                        case 5:
                            break;
                        default:
                        printf("Opção inválida");
                    }
                }
            }
        }else{
            printf("Opção inválida!\n");
        }
    }while(op_editar != 3);
}

//====EXCLUI USUARIO====
void excluiArquivo()
{
    int IDPessoaExclusao;
    printf("Digite o ID para exclusao\n");
    scanf("%d", &IDPessoaExclusao);

    int i;
    for (i = 0; i < cont; i++)
    {
        if (lista[i].IDPessoa == IDPessoaExclusao)
        {
            // Liberar telefones antes de excluir a pessoa
            liberarTelefones(i);

            // Não escrever a pessoa excluída no arquivo
            continue;
        }

        fprintf(arquivo, "%d ; %s ; %s ; %s ; %s\n", lista[i].IDPessoa, lista[i].nome, lista[i].email, lista[i].cpf, lista[i].dataNascimento);
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
    carregaArquivo();
    do{
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
