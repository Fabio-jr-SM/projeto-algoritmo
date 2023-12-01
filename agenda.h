// agenda.h
#ifndef AGENDA_H
#define AGENDA_H

#include <stdbool.h>

#define EMAIL "([A-Z|a-z|0-9](\\.|_){0,1})+[A-Z|a-z|0-9]\\@([A-Z|a-z|0-9])+((\\.){0,1}[A-Z|a-z|0-9]){2,3}\\.[a-z]{2,3}"
#define TELEFONE "\\([0-9]{2}\\)[0-9]{4,5}-[0-9]{4}"
#define DATA_PATTERN "\\d{2}/\\d{2}/\\d{4}"

typedef struct p {
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
void cadastrarTelefones(PESSOA *novoTelefone, int i);
void liberarTelefones(int indice);
int valida_exp_regular(char expreg[], char texto[]);
int validarData(const char *data);
int validarCPF(char *cpf);
int ultimoID();

#endif
