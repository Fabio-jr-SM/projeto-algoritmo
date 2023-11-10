//https://www.cprogressivo.net/2013/11/Como-ler-arquivos-em-C-As-funcoes-fgetc-fscanf-fgets.html
#include <stdio.h>
#include <stdlib.h>
#include<locale.h>

typedef struct t
{
    int idTelefone, idPessoa;
	char telefone[14];
} TELEFONE;

typedef struct e
{
    int idEmail, idPessoa;
	char email[100];
} EMAIL;

typedef struct p
{
    int idPessoa;
	char nome[100];
    TELEFONE listaTelefone[10];
    EMAIL listaEmail[10];
} PESSOA;

//O ideal seria utilizar vetor dinamicamente alocado
PESSOA listaPessoa[1000];
TELEFONE listaTelefone[10000];
EMAIL listaEmail[10000];

int contador_pessoa, contador_telefone, contador_email;

int main(void)
{
    setlocale(LC_ALL, "Portuguese");
    carrega_vetor();
    //menu();
    //system("pause");
    return(0);
}

//Carrega o vetor que irá guardar os dados do arquivo
void carrega_vetor()
{
    FILE *pont_arq_pessoa, *pont_arq_telefone, *pont_arq_email;
    pont_arq_pessoa = fopen("pessoa.txt", "r");
    pont_arq_telefone = fopen("telefone.txt", "r");
    pont_arq_email = fopen("email.txt", "r");

    if(pont_arq_telefone == NULL)
    {
        printf("Não foi possível abrir o arquivo de TELEFONE\n");
    }
    else
    {
        contador_telefone = 0;
        //while( (fscanf(pont_arq_telefone,"%d ; %d ; %[^\n]%*c\n", &idTelefone, &idPessoa, telefone))!=EOF )
        //    printf("%d - %d - %s\n", idTelefone, idPessoa, telefone);

        while( (fscanf(pont_arq_telefone,"%d ; %d ; %[^\n]%*c\n", &listaTelefone[contador_telefone].idTelefone, &listaTelefone[contador_telefone].idPessoa, &listaTelefone[contador_telefone].telefone))!=EOF )
            contador_telefone++;
    }

    if(pont_arq_email == NULL)
    {
        printf("Não foi possível abrir o arquivo de EMAIL\n");
    }
    else
    {
        contador_email = 0;
        while( (fscanf(pont_arq_email,"%d ; %d ; %[^\n]%*c\n", &listaEmail[contador_email].idEmail, &listaEmail[contador_email].idPessoa, &listaEmail[contador_email].email))!=EOF )
            contador_email++;
    }

    if(pont_arq_pessoa == NULL)
    {
        printf("Não foi possível abrir o arquivo de PESSOA\n");
    }
    else
    {
        contador_pessoa = 0;
        while( (fscanf(pont_arq_pessoa,"%d ; %[^\n]%*c\n", &listaPessoa[contador_pessoa].idPessoa, &listaPessoa[contador_pessoa].nome))!=EOF )
        {
            int qtd_telefone_pessoa = 0, i = 0;
            for(i = 0; i< contador_telefone; i++)
            {
                if(listaTelefone[i].idPessoa == listaPessoa[contador_pessoa].idPessoa)
                {
                    printf("%s - %s\n", listaPessoa[contador_pessoa].nome, listaTelefone[i].telefone);
                    listaPessoa[contador_pessoa].listaTelefone[qtd_telefone_pessoa] = listaTelefone[i];
                    qtd_telefone_pessoa++;
                }
            }

            int qtd_email_pessoa = 0;
            i = 0;
            for(i = 0; i< contador_email; i++)
            {
                if(listaEmail[i].idPessoa == listaPessoa[contador_pessoa].idPessoa)
                {
                    printf("%s - %s\n", listaPessoa[contador_pessoa].nome, listaEmail[i].email);
                    listaPessoa[contador_pessoa].listaEmail[qtd_email_pessoa] = listaEmail[i];
                    qtd_email_pessoa++;
                }
            }

            contador_pessoa++;
        }
        printf(listaPessoa[0].listaTelefone[2].telefone);
        printf("Quantidade de Pessoas: %d\n", contador_pessoa);
        printf("Quantidade de Telefones: %d\n", contador_telefone);
        printf("Quantidade de E-mails: %d\n", contador_email);
    }

    fclose(pont_arq_pessoa);
    fclose(pont_arq_telefone);
    fclose(pont_arq_email);
}
/*
void edita_pessoa(int idPessoa)
{
    int i;
    char nome[100] = "André"; // Faz a leitura dos dados
    for(i = 0; i < tamanho_pessoa; i++)
    {
        if(listaPessoa[i].idPessoa = idPessoa)
        {
            "%[^\n]%*c ; %[^\n]%*c", listaPessoa[i].idPessoa, listaPessoa[i].nome = nome;
        }
    }
}

void salva_arquivo()
{
    listaPessoa[i].idPessoa 
}
*/
void menu()
{
    printf("1) Cadastrar\n");
    printf("2) Editar\n");
    printf("3) Consultar\n");
    printf("4) Excluir\n");
    printf("5) Sair\n");
}
