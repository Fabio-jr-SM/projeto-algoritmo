/**
 * O arquivo de cabeçalho "agenda.h" contém a definição de tipos, constantes e protótipos de funções relacionados ao programa de cadastro telefônico.
 * Define padrões de expressões regulares para validação de dados como email, telefone e data.
 * Também define a estrutura PESSOA, que representa as informações de uma pessoa no cadastro.
 *
 * @note Inclui a biblioteca "stdbool.h" para utilizar o tipo de dado booleano.
 * @note Define macros para expressões regulares de email, telefone e data.
 * @note Declaração da estrutura PESSOA, que armazena informações de uma pessoa no cadastro.
 * @note Protótipos de funções para as operações principais do programa.
 * @note Certifique-se de incluir este arquivo em outros módulos do programa para acessar as definições e funcionalidades.
 */

#ifndef AGENDA_H
#define AGENDA_H

#include <stdbool.h>

#define EMAIL "([A-Z|a-z|0-9](\\.|_){0,1})+[A-Z|a-z|0-9]\\@([A-Z|a-z|0-9])+((\\.){0,1}[A-Z|a-z|0-9]){2,3}\\.[a-z]{2,3}"
#define TELEFONE "\\([0-9]{2}\\)[0-9]{4,5}-[0-9]{4}"
#define DATA_PATTERN "\\d{2}/\\d{2}/\\d{4}"

// Definição da estrutura PESSOA
typedef struct p {
    int IDPessoa;
    char nome[31];
    char email[31];
    char cpf[12];
    char dataNascimento[11];
    char **telefones; 
    int numTelefones;
} PESSOA;

// Protótipos de funções
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
