// agenda.c
#include "agenda.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <regex.h>
#define INFINITY (1<<20)

PESSOA lista[100];
int cont;
FILE *arquivo;

//VALIDACOES DE EXPRESSOES REGULARES
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


/**
 * A função carregaArquivo realiza a leitura de dados de um arquivo "pessoa.txt"
 * e armazena esses dados na estrutura de dados 'lista', que parece ser um array
 * de estruturas representando informações de pessoas.
 *
 * @note A função utiliza alocação dinâmica de memória para armazenar os números de telefone.
 * @note Certifique-se de liberar a memória alocada após o uso para evitar vazamento de memória.
 */
//====CARREGA ARQUIVO (ARQUIVO PARA MEMORIA)====
void carregaArquivo()
{
    // Inicializa o contador e abre o arquivo para leitura e escrita.
    cont = 0;
    arquivo = fopen("pessoa.txt", "r+");

    // Verifica se o arquivo foi aberto com sucesso.
    if (arquivo != NULL) {
        // Loop de leitura enquanto houver dados no arquivo.
        while (fscanf(arquivo, "%d ; %s ; %s ; %s ; %s ; %d",
                      &lista[cont].IDPessoa, lista[cont].nome, lista[cont].email,
                      lista[cont].cpf, lista[cont].dataNascimento, &lista[cont].numTelefones) != EOF) {
            
            // Se o número de telefones for maior que zero, aloca dinamicamente memória para os telefones.
            if (lista[cont].numTelefones > 0) {
                lista[cont].telefones = (char **)malloc(lista[cont].numTelefones * sizeof(char *));
                for (int i = 0; i < lista[cont].numTelefones; i++) {
                    // Aloca memória para armazenar um número de telefone.
                    lista[cont].telefones[i] = (char *)malloc(15 * sizeof(char));
                    // Lê um número de telefone do arquivo e armazena na estrutura de dados.
                    fscanf(arquivo, " ; %s", lista[cont].telefones[i]);
                }
            }

            // Incrementa o contador para o próximo elemento na lista.
            cont++;
        }

        // Fecha o arquivo após a leitura.
        fclose(arquivo);
    } else {
        // Exibe uma mensagem de erro se o arquivo não pôde ser aberto e encerra o programa.
        printf("\nNão foi possível abrir o arquivo\n");
        exit(1);
    }
}


/**
 * A função escreverArquivo cria ou sobrescreve o arquivo "pessoa.txt" e escreve as informações
 * armazenadas na estrutura de dados 'lista' no arquivo.
 *
 * @note Certifique-se de chamar esta função após realizar as operações desejadas e antes de encerrar o programa.
 */
//====CARREGA MEMORIA (MEMORIA PARA ARQUIVO)====
void escreverArquivo()
{
    // Abre o arquivo "pessoa.txt" para escrita e leitura.
    arquivo = fopen("pessoa.txt", "w+");

    // Loop para percorrer os elementos da lista e escrever no arquivo.
    for(int k = 0; k < cont; k++) {
        // Escreve as informações básicas de uma pessoa no arquivo.
        fprintf(arquivo, "%d ; %s ; %s ; %s ; %s ; %d",
                lista[k].IDPessoa, lista[k].nome, lista[k].email,
                lista[k].cpf, lista[k].dataNascimento, lista[k].numTelefones);

        // Se a pessoa tiver números de telefone, escreve-os no arquivo.
        if(lista[k].numTelefones > 0){
            for (int p = 0; p < lista[k].numTelefones; p++) {
                fprintf(arquivo, " ; %s", lista[k].telefones[p]);
            }
        }

        // Adiciona uma quebra de linha para separar os registros no arquivo.
        fprintf(arquivo, "\n");
    }

    // Fecha o arquivo após a escrita.
    fclose(arquivo);
}


/**
 * A função cadastraArquivo permite a interação do usuário para cadastrar informações de uma pessoa
 * no arquivo "pessoa.txt". Também possibilita o cadastro de telefones associados a uma pessoa existente.
 *
 * @note A função utiliza validações de entrada para garantir dados válidos.
 * @note O cadastro de telefones é associado a uma pessoa pelo nome ou ID.
 * @note Certifique-se de chamar esta função conforme necessário no programa.
 */
//====CADASTRA USUARIO====
void cadastraArquivo()
{
    int op;
    
    // Exibe um menu para o usuário escolher entre cadastrar pessoa, cadastrar telefone ou retornar.
    printf("\n(1) Cadastrar pessoa\n(2) Cadastrar Telefone\n(3) Return\n");
    scanf("%d", &op);

    // Loop principal para interação do usuário.
    while(op != 3) {
        if(op == 1) {
            // Cria uma nova pessoa e solicita informações ao usuário.
            PESSOA novaPessoa;
            
            do {
                printf("Digite o nome: ");
                scanf("%s", novaPessoa.nome);
                if(strlen(novaPessoa.nome) > 2) {
                    printf("Válido!\n");
                } else {
                    printf("Inválido! O nome deve ter mais de dois caracteres.\n");
                }
            } while(strlen(novaPessoa.nome) <= 2);
            
            // Solicita e valida o email.
            do {
                printf("Digite o Email: ");
                scanf("%s", novaPessoa.email);
                if(valida_exp_regular(EMAIL, novaPessoa.email)) {
                    printf("Válido\n");
                } else {
                    printf("Inválido! Insira um email válido.\n");
                }
            } while(!valida_exp_regular(EMAIL, novaPessoa.email));
            
            // Solicita e valida o CPF.
            do {
                printf("Digite o CPF: ");
                scanf("%s", novaPessoa.cpf);
                if(validarCPF(novaPessoa.cpf) == 0) {
                    printf("Válido\n");
                } else {
                    printf("Inválido! Insira um CPF válido.\n");
                }
            } while(validarCPF(novaPessoa.cpf) == 1);
            
            // Solicita e valida a data de nascimento.
            do {
                printf("Digite a data de nascimento: ");
                scanf("%s", novaPessoa.dataNascimento);
                if(validarData(novaPessoa.dataNascimento) == 1) {
                    printf("Válido\n");
                } else {
                    printf("Inválido! Insira uma data de nascimento válida.\n");
                }
            } while(validarData(novaPessoa.dataNascimento) == 0);
            
            // Inicializa o número de telefones e abre o arquivo para adicionar a nova pessoa.
            novaPessoa.numTelefones = 0;
            arquivo = fopen("pessoa.txt", "a+");
            fprintf(arquivo, "%d ; %s ; %s ; %s ; %s ; %d\n", ultimoID() + 1, 
            novaPessoa.nome, novaPessoa.email, novaPessoa.cpf, novaPessoa.dataNascimento, novaPessoa.numTelefones);
            fclose(arquivo);

            // Atualiza a lista de pessoas a partir do arquivo.
            carregaArquivo();
        } else if(op == 2) {
            // Exibe as informações existentes no arquivo.
            imprimeArquivo();

            // Variáveis para o cadastro de telefones.
            int op_cadastro_tel;
            PESSOA novoTelefone;
            char nome_comparacao[31];
            int ID_comparacao, encontrouID = 0, encontrouNOME = 0;

            // Exibe um menu para o usuário escolher como cadastrar o telefone.
            printf("\n(1) Cadastrar usando o Nome\n(2) Cadastrar usando o ID\n(3) Return\n");
            scanf("%d", &op_cadastro_tel);

            if(op_cadastro_tel == 1) {
                // Solicita o nome e cadastra telefones associados ao nome.
                printf("Digite o nome: ");
                scanf("%s", nome_comparacao);
                for(int i = 0; i < cont; i++) {
                    if(strcmp(nome_comparacao, lista[i].nome) == 0) {
                        cadastrarTelefones(&novoTelefone, i);
                        lista[i].telefones = novoTelefone.telefones;
                        lista[i].numTelefones = novoTelefone.numTelefones;
                        
                        encontrouNOME = 1;

                        // Exibe os telefones cadastrados.
                        if (novoTelefone.numTelefones > 0) {
                            printf("Telefones:\n");
                            for (int j = 0; j < novoTelefone.numTelefones; j++) {
                                printf("%d. %s\n", j + 1, novoTelefone.telefones[j]);
                            }
                        }
                        // Atualiza o arquivo após o cadastro.
                        escreverArquivo();
                    }
                }

                if(encontrouNOME != 1) {
                    printf("Nome inexistente\n");
                }
            } else if(op_cadastro_tel == 2) {
                // Solicita o ID e cadastra telefones associados ao ID.
                int i;

                printf("\nDigite o ID da pessoa: ");
                scanf("%d", &ID_comparacao);

                for(i = 0; i < cont; i++) {
                    if(lista[i].IDPessoa == ID_comparacao) {
                        cadastrarTelefones(&novoTelefone, i);
                        lista[i].telefones = novoTelefone.telefones;
                        lista[i].numTelefones = novoTelefone.numTelefones;

                        encontrouID = 1; 

                        // Exibe os telefones cadastrados.
                        if (novoTelefone.numTelefones > 0) {
                            printf("Telefones:\n");
                            for (int j = 0; j < novoTelefone.numTelefones; j++) {
                                printf("%d. %s\n", j + 1, novoTelefone.telefones[j]);
                            }
                        }
                        // Atualiza o arquivo após o cadastro.
                        escreverArquivo();
                    }
                }

                if(encontrouID != 1) {
                    printf("ID inexistente\n");
                }
            }
        }

        // Exibe novamente o menu para o usuário escolher a próxima ação.
        printf("\n(1) Cadastrar pessoa\n(2) Cadastrar Telefone\n(3) Return\n");
        scanf("%d", &op);
    }
}



/**
 * A função cadastrarTelefones é responsável por cadastrar dinamicamente telefones associados a uma pessoa.
 * Ela recebe como parâmetros uma estrutura de pessoa (novoTelefone) e o índice (i) da pessoa na lista.
 *
 * @param novoTelefone Ponteiro para a estrutura de pessoa à qual os telefones serão associados.
 * @param i Índice da pessoa na lista.
 *
 * @note Antes de cadastrar novos telefones, a função libera os telefones existentes para evitar vazamento de memória.
 * @note Inicialmente, alocam-se espaço para 5 telefones, e o número de telefones é inicializado como zero.
 * @note Utiliza validações para garantir que os telefones inseridos sejam válidos.
 */
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
        
        do {
            // Solicita e valida o telefone.
            printf("Digite o telefone: ");
            scanf("%s", novoTelefone->telefones[novoTelefone->numTelefones]);
            if(valida_exp_regular(TELEFONE, novoTelefone->telefones[novoTelefone->numTelefones])) {
                printf("Válido\n");
            } else {
                printf("Inválido! Insira um telefone válido.\n");
            }
        } while(!valida_exp_regular(TELEFONE, novoTelefone->telefones[novoTelefone->numTelefones]));
        
        // Incrementa o número de telefones cadastrados.
        novoTelefone->numTelefones++;

        // Pergunta ao usuário se deseja cadastrar outro telefone.
        printf("Deseja cadastrar outro telefone? (s/n): ");
        scanf(" %c", &resposta);
    } while (resposta == 's');
}



/**
 * A função liberarTelefones é responsável por liberar a memória alocada para os telefones de uma pessoa.
 * Ela recebe como parâmetro o índice (indice) da pessoa na lista cujos telefones serão liberados.
 *
 * @param indice Índice da pessoa na lista cujos telefones serão liberados.
 *
 * @note A função utiliza um loop para liberar a memória alocada para cada telefone individualmente.
 * @note Em seguida, libera a memória alocada para o array de ponteiros para telefones.
 * @note Define o ponteiro de telefones para NULL e reinicia o número de telefones para zero.
 */
// FUNÇÃO PARA LIBERAR A MEMÓRIA ALOCADA PARA OS TELEFONES
void liberarTelefones(int indice) 
{
    // Loop para liberar a memória de cada telefone individualmente.
    for (int i = 0; i < lista[indice].numTelefones; i++) {
        free(lista[indice].telefones[i]);
    }
    
    // Libera a memória alocada para o array de ponteiros para telefones.
    free(lista[indice].telefones);
    
    // Define o ponteiro de telefones como NULL e reinicia o número de telefones para zero.
    lista[indice].telefones = NULL;
    lista[indice].numTelefones = 0;
}



/**
 * A função editaArquivo permite ao usuário editar informações de uma pessoa no arquivo "pessoa.txt".
 * Ela oferece opções para editar utilizando o nome ou o ID da pessoa.
 *
 * @note A função exibe um menu interativo e solicita informações ao usuário para realizar as alterações.
 * @note Oferece a opção de editar nome, data de nascimento, CPF, email ou retornar ao menu anterior.
 * @note As alterações são efetuadas diretamente na lista de pessoas e refletidas no arquivo.
 * @note Certifique-se de chamar esta função conforme necessário no programa.
 */
//====EDITA USUARIO====
void editaArquivo()
{
    int i;
    int IDPessoaAlteracao, op_editar, op_alteracao;
    char NomePessoaAlteracao[31];

    // Loop principal para interação do usuário.
    do {
        imprimeArquivo();
        printf("\n(1) Editar usando o Nome\n(2) Editar usando o ID\n(3) Return\n");
        scanf("%d", &op_editar);

        // Editar usando o Nome.
        if (op_editar == 1) {
            printf("Digite o nome: ");
            scanf("%s", NomePessoaAlteracao);

            // Itera sobre a lista para encontrar a pessoa pelo nome.
            for (int i = 0; i < cont; i++) {
                if (strcmp(NomePessoaAlteracao, lista[i].nome) == 0) {
                    // Submenu para escolher o que editar.
                    printf("O que deseja alterar:\n(1) Nome\n(2) Data de nascimento\n(3) CPF\n(4) Email\n(5) Return\n");
                    scanf("%d", &op_alteracao);
                    switch (op_alteracao) {
                        case 1:
                            // Edita o nome.
                            do {
                                printf("Digite o novo nome: ");
                                scanf("%s", lista[i].nome);
                                if (strlen(lista[i].nome) > 2) {
                                    printf("Válido!\n");
                                } else {
                                    printf("Inválido! O nome deve ter mais de dois caracteres.\n");
                                }
                            } while (strlen(lista[i].nome) <= 2);
                            escreverArquivo();
                            break;

                        case 2:
                            // Edita a data de nascimento.
                            do {
                                printf("Digite a nova data de nascimento: ");
                                scanf("%s", lista[i].dataNascimento);
                                if (validarData(lista[i].dataNascimento) == 1) {
                                    printf("Válido\n");
                                } else {
                                    printf("Inválido! Insira uma data de nascimento válida.\n");
                                }
                            } while (validarData(lista[i].dataNascimento) == 0);
                            escreverArquivo();
                            break;

                        case 3:
                            // Edita o CPF.
                            do {
                                printf("Digite o novo CPF: ");
                                scanf("%s", lista[i].cpf);
                                if (validarCPF(lista[i].cpf) == 0) {
                                    printf("Válido\n");
                                } else {
                                    printf("Inválido! Insira um CPF válido.\n");
                                }
                            } while (validarCPF(lista[i].cpf) == 1);
                            escreverArquivo();
                            break;

                        case 4:
                            // Edita o email.
                            do {
                                printf("Digite o novo email: ");
                                scanf("%s", lista[i].email);
                                if (valida_exp_regular(EMAIL, lista[i].email)) {
                                    printf("Válido\n");
                                } else {
                                    printf("Inválido! Insira um email válido.\n");
                                }
                            } while (!valida_exp_regular(EMAIL, lista[i].email));
                            escreverArquivo();
                            break;

                        case 5:
                            break;
                    }
                }
            }
        } else if (op_editar == 2) {
            // Editar usando o ID.
            printf("Digite o ID: ");
            scanf("%d", &IDPessoaAlteracao);

            // Itera sobre a lista para encontrar a pessoa pelo ID.
            for (int i = 0; i < cont; i++) {
                if (IDPessoaAlteracao == lista[i].IDPessoa) {
                    // Submenu para escolher o que editar.
                    printf("O que deseja alterar:\n(1) Nome\n(2) Data de nascimento\n(3) CPF\n(4) Email\n(5) Return\n");
                    scanf("%d", &op_alteracao);
                    switch (op_alteracao) {
                        case 1:
                            // Edita o nome.
                            do {
                                printf("Digite o novo nome: ");
                                scanf("%s", lista[i].nome);
                                if (strlen(lista[i].nome) > 2) {
                                    printf("Válido!\n");
                                } else {
                                    printf("Inválido! O nome deve ter mais de dois caracteres.\n");
                                }
                            } while (strlen(lista[i].nome) <= 2);
                            escreverArquivo();
                            break;

                        case 2:
                            // Edita a data de nascimento.
                            do {
                                printf("Digite a nova data de nascimento: ");
                                scanf("%s", lista[i].dataNascimento);
                                if (validarData(lista[i].dataNascimento) == 1) {
                                    printf("Válido\n");
                                } else {
                                    printf("Inválido! Insira uma data de nascimento válida.\n");
                                }
                            } while (validarData(lista[i].dataNascimento) == 0);
                            escreverArquivo();
                            break;

                        case 3:
                            // Edita o CPF.
                            do {
                                printf("Digite o novo CPF: ");
                                scanf("%s", lista[i].cpf);
                                if (validarCPF(lista[i].cpf) == 0) {
                                    printf("Válido\n");
                                } else {
                                    printf("Inválido! Insira um CPF válido.\n");
                                }
                            } while (validarCPF(lista[i].cpf) == 1);
                            escreverArquivo();
                            break;

                        case 4:
                            // Edita o email.
                            do {
                                printf("Digite o novo email: ");
                                scanf("%s", lista[i].email);
                                if (valida_exp_regular(EMAIL, lista[i].email)) {
                                    printf("Válido\n");
                                } else {
                                    printf("Inválido! Insira um email válido.\n");
                                }
                            } while (!valida_exp_regular(EMAIL, lista[i].email));
                            escreverArquivo();
                            break;

                        case 5:
                            break;
                    }
                }
            }
        } else if((op_editar != 3) && (op_editar != 2) && (op_editar != 1)) {
            printf("Opção inválida!\n");
        }
    } while(op_editar != 3);
}


/**
 * A função excluiArquivo permite ao usuário excluir um registro de pessoa no arquivo "pessoa.txt".
 * Ela exibe a lista atual de pessoas, solicita o ID da pessoa a ser excluída e realiza a exclusão no arquivo.
 * Além disso, a função realiza a exclusão da memória alocada para os telefones da pessoa removida.
 *
 * @note A função solicita o ID da pessoa a ser excluída e itera sobre a lista, reescrevendo o arquivo sem o registro selecionado.
 * @note Os telefones associados à pessoa excluída são liberados da memória utilizando a função liberarTelefones.
 * @note Certifique-se de chamar esta função conforme necessário no programa.
 */
//====EXCLUI USUARIO====
void excluiArquivo()
{
    imprimeArquivo();
    
    // Excluir o registro na memória
    arquivo = fopen("pessoa.txt", "w+");
    int IDPessoaExclusao;
    printf("Digite o ID para exclusão: ");
    scanf("%d", &IDPessoaExclusao);
    int i;

    // Itera sobre a lista para reescrever o arquivo sem o registro selecionado.
    for(i = 0; i < cont; i++)
    {
        if(lista[i].IDPessoa != IDPessoaExclusao)
        {
            fprintf(arquivo, "%d ; %s ; %s ; %s ; %s ; %d", lista[i].IDPessoa, lista[i].nome, lista[i].email, lista[i].cpf, lista[i].dataNascimento, lista[i].numTelefones);
            
            // Reescreve os telefones associados à pessoa.
            if (lista[i].numTelefones > 0) {
                for (int j = 0; j < lista[i].numTelefones; j++) {
                    fprintf(arquivo, " ; %s", lista[i].telefones[j]);
                }
            }

            fprintf(arquivo, "\n");
        } else {
            // Libera a memória alocada para os telefones da pessoa removida.
            if(lista[i].numTelefones > 0){
                liberarTelefones(i);
            }   
        }
    }

    fclose(arquivo);
    // Atualiza a lista após a exclusão.
    carregaArquivo();
}



/**
 * A função imprimeArquivo exibe os cadastros armazenados no arquivo "pessoa.txt" na saída padrão.
 * Ela apresenta as informações básicas, como ID, nome, email, CPF e data de nascimento, para cada pessoa cadastrada.
 * Além disso, imprime a lista de telefones associados a cada pessoa, se houver.
 *
 * @note Utiliza formatação para apresentar as informações em uma tabela organizada.
 * @note Itera sobre a lista de pessoas, exibindo os dados e telefones, se presentes.
 * @note Certifique-se de chamar esta função conforme necessário no programa.
 */
//====IMPRIME CADASTROS====
void imprimeArquivo()
{
    int i;
    printf("| %-2s | %-30s | %-30s | %-12s | %-11s |\n", "ID", "Nome", "Email", "CPF", "Nascimento");
    
    // Itera sobre a lista de pessoas para imprimir os cadastros.
    for(i = 0; i < cont; i++)
    {
        printf("| %-2d | %-30s | %-30s | %-12s | %-11s |\n", lista[i].IDPessoa, lista[i].nome, lista[i].email, lista[i].cpf, lista[i].dataNascimento);

        // Imprime os telefones associados à pessoa, se houver.
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


/**
 * A função menu é responsável por exibir um menu interativo para gerenciar cadastros telefônicos.
 * Oferece opções para cadastrar, editar, excluir, consultar e sair do sistema.
 *
 * @note Utiliza a função system("clear") para limpar a tela (funciona em sistemas Unix-like).
 * @note Chama as funções correspondentes de acordo com a escolha do usuário.
 * @note Continua exibindo o menu até que o usuário escolha sair (opção 5).
 * @note Certifique-se de chamar esta função no ponto de entrada do seu programa para iniciar a interação com o usuário.
 */
void menu()
{
    int menu;
    carregaArquivo();

    // Loop principal para interação do usuário.
    do {
        printf("\n============CADASTRO TELEFONICO============\n");
        printf("1 - Cadastrar\n");
        printf("2 - Editar\n");
        printf("3 - Excluir\n");
        printf("4 - Consultar\n");
        printf("5 - Sair\n");

        scanf("%d", &menu);
        
        // Executa a opção escolhida pelo usuário.
        switch(menu) {
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
                printf("Menu inválido\n");
        }
    } while (menu != 5);
}
