# Projeto Algoritmo
Projeto Final – Algoritmos 2![](Aspose.Words.cada281d-f890-4652-9a87-630368d60e0c.001.png)

Informações

Para esta atividade, implementar uma agenda telefônica que contenha os dados de Nome, Telefone, E-mail, CPF e Data de Nascimento. A agenda deve permitir que mais de um telefone seja cadastrado para a mesma pessoa.

Estrutura de Armazenamento

- Nome: Texto de 30 caracteres.
  - Telefone: Texto com 11 caracteres.
    - E-mail: Texto de 30 caracteres.
      - CPF: Texto de 11 caracteres.
        - Data de Nascimento: Texto de 10 caracteres.

Validações

Os campos devem conter as seguintes validações:

- Nome: Maior que 2 caracteres.
  - Telefone: Possuir 10 ou 11 caracteres numéricos (DDD incluso).
    - E-mail: Maior que 10 caracteres e e-mail válido.
      - CPF: Deverá ser um CPF válido.
        - Data de Nascimento: A data deve ser menor ou igual a data atual e data válida (dd/mm/YYYY).

Os itens validados só seguirão para o próximo item, quando forem validados, ou seja, o usuário deverá repetir a digitação do item até que este seja validado positivamente.

Menus

Os menus sempre receberão valores numéricos inteiros (*int*) para a navegação. Ao realizar a escolha da opção, o menu deve ser direcionado ao novo menu ou ação escolhida.

Estrutura Resumida dos Menus

1\.  Cadastrar

1. Pessoa
1. Telefone
   1. Nome
   1. IDPessoa
   1. Retornar
1. Retornar

2\.  Editar

1\.  Pessoa

1. Nome
   1. Nome
   1. Data de Nascimento
   1. CPF
   1. E-mail
   1. Retornar
1. IDPessoa
   1. Nome
   1. Data de Nascimento
   1. CPF
   1. E-mail
   1. Retornar
1. Retornar
3. Excluir
3. Consultar
3. Sair

Menu *Principal*

Ao acessar o programa, o usuário deverá realizar a leitura de um número inteiro (*int*) para direcionar ao próximo menu. Os números de 1 a 4 direcionam para outro menu indicado abaixo. O número 5 finaliza o programa, encerrando o código fonte. Qualquer outro número digitado, que não sejam números de 1 a 5, devem ser lidos novamente, até que se digite um número válido de menu.

1. Cadastrar (Realiza o cadastro de pessoas e telefones)
1. Editar (Realiza a edição de pessoas e telefones)
1. Excluir (Realiza a exclusão de pessoas e telefones)
1. Consultar (Realiza a consulta de pessoas e telefones)
1. Sair (Finaliza o programa)

Menu *Cadastrar* (1)

Ao acessar o menu cadastrar, o usuário deverá realizar a leitura de um número inteiro (*int*) para direcionar ao próximo menu. Os números de 1 a 2 direcionam para o outro menu indicado abaixo. O número 3 retorna ao menu anterior (*Menu Principal*). Qualquer outro número digitado, que não sejam números de 1 a 3, devem ser lidos novamente, até que se digite um número válido de menu.

1. Pessoa (Realiza o cadastro das informações de uma pessoa)
2. Telefone (Realiza o cadastro de um telefone, com base em uma pessoa selecionada)
2. Retornar (Retorna ao Menu Principal)

Menu *Cadastrar / Pessoa* (1...1)

Ao acessar o menu para cadastrar pessoas, o usuário deverá entrar com as informações de Nome, Data de Nascimento, CPF e E-mail respectivamente, seguindo as formatações e regras descritas na seção Validações.

Ao informar um nome que já consta na lista de pessoas, o usuário deverá digitar um novo nome, até que seja um nome inexistente na lista.

Ao finalizar a digitação dos 3 campos anteriores, o usuário deve iniciar a digitação do campo do Telefone, seguindo as formatações e regras descritas na seção Validações. Ao final, é necessário perguntar ao usuário se deseja inserir um novo telefone, esperando a resposta "S" ou "s" para Sim e "N" ou "n" para Não. Neste caso, enquanto o usuário digitar valores para sim, o programa deverá adicionar novos telefones para o usuário previamente cadastrado.

Menu *Cadastrar / Telefone* (1...2)

Ao acessar o menu para cadastrar telefones, o usuário deverá pesquisar qual é a pessoa a qual o telefone será cadastrado. O usuário deverá realizar a leitura de um número inteiro (*int*) para direcionar ao próximo menu. Os números de 1 a 2 direcionam para o outro menu indicado abaixo. O número 3 retorna ao menu anterior (*Menu Principal*). Qualquer outro número digitado, que não sejam números de 1 a 3, devem ser lidos novamente, até que se digite um número válido de menu.

1. Nome (Realiza a pesquisa pelo nome da pessoa)
1. IDPessoa (Realiza a pesquisa pelo ID da pessoa)
1. Retornar (Retorna ao Menu Principal)

Menu *Cadastrar / Telefone / Nome* (1...2...1)

Ao acessar o menu para pesquisar os telefones pelo \*nome, o usuário deverá realizar a leitura de um nome (*char[31]*) e comparar a aos existentes na agenda. Ao encontrar um nome que é idêntico ao que foi lido, o usuário deverá cadastrar os telefones para esta pessoa.

O usuário deve iniciar a digitação do campo do Telefone, seguindo as formatações e regras descritas na seção Validações. Ao final, é necessário perguntar ao usuário se deseja inserir um novo telefone, esperando a resposta "S" ou "s" para Sim e "N" ou "n" para Não. Neste caso, enquanto o usuário digitar valores para sim, o programa deverá adicionar novos telefones para o usuário previamente cadastrado.

Menu *Cadastrar / Telefone / IDPessoa* (1...2...2)

Ao acessar o menu para pesquisar os telefones pelo IDPessoa, o usuário deverá realizar a leitura de um IDPessoa (*int*) e comparar a aos existentes na agenda. Ao encontrar um IDPessoa que é idêntico ao que foi lido, o usuário deverá cadastrar os telefones para esta pessoa.

O usuário deve iniciar a digitação do campo do Telefone, seguindo as formatações e regras descritas na seção Validações. Ao final, é necessário perguntar ao usuário se deseja inserir um novo telefone, esperando a resposta "S" ou "s" para Sim e "N" ou "n" para Não. Neste caso, enquanto o usuário digitar valores para sim, o programa deverá adicionar novos telefones para o usuário previamente cadastrado.

Menu *Cadastrar / Telefone / Retornar* (1...2...3)

Ao acessar o menu "3 - Retornar", o usuário deverá retornar ao menu anterior, chamado Cadastrar.

Menu *Editar* (2)

Ao acessar o menu editar, o usuário deverá realizar a leitura de um número inteiro (*int*) para direcionar ao próximo menu. Os números de 1 a 2 direcionam para o outro menu indicado abaixo. O número 3 retorna ao menu anterior (*Menu Principal*). Qualquer outro número digitado, que não sejam números de 1 a 3, devem ser lidos novamente, até que se digite um número válido de menu.

1. Pessoa (Realiza a edição das informações de uma pessoa)
1. Telefone (Realiza a edição de um telefone, com base em uma pessoa selecionada)
1. Retornar (Retorna ao Menu Principal)

Menu *Editar / Pessoa* (2...1)

Ao acessar o menu para editar uma pessoa pelo nome, o usuário deverá pesquisar (por nome ou IDPessoa) qual é a pessoa que deverá ser editada. O usuário deverá realizar a leitura de um número inteiro (*int*) para direcionar ao próximo menu. Os números de 1 a 2 direcionam para o outro menu indicado abaixo. O número 3 retorna ao menu anterior (*Menu Principal*). Qualquer outro número digitado, que não sejam números de 1 a 3, devem ser lidos novamente, até que se digite um número válido de menu.

1. Nome (Realiza a pesquisa pelo nome da pessoa)
1. IDPessoa (Realiza a pesquisa pelo ID da pessoa)
1. Retornar (Retorna ao Menu Principal)

Menu *Editar / Pessoa / Nome* (2...1...1)

Ao acessar o menu para pesquisar as pessoas pelo \*nome, o usuário deverá realizar a leitura de um nome (*char[31]*) e comparar a aos existentes na agenda.

Ao encontrar um nome que é idêntico ao que foi lido, o usuário deverá editar somente o dado selecionado para esta pessoa. Para isto, deverá ser exibido o menu abaixo para a seleção de qual campo deverá ser alterado.

1. Nome
1. Data de Nascimento
1. CPF
1. E-mail
1. Retornar

Para os menus de 1 a 4, o campo selecionado deve ser alterado para a pessoa que teve o seu nome pesquisado anteriormente, respeitando as validações já

mencionadas. Já o menu "5 - Retornar", deverá voltar ao menu anterior *Editar / Pessoa / Nome* (2...1...1).

Caso a busca pelo nome não encontre uma pessoa na agenda, o programa deverá voltar ao menu anterior *Editar / Pessoa* (2...1).

Menu *Editar / Pessoa / IDPessoa* (2...1...2)

Ao acessar o menu para pesquisar as pessoas pelo \*IDPessoa, o usuário deverá realizar a leitura de um IDPessoa (*int*) e comparar a aos existentes na agenda.

Ao encontrar um IDPessoa que é idêntico ao que foi lido, o usuário deverá editar somente o dado selecionado para esta pessoa. Para isto, deverá ser exibido o menu abaixo para a seleção de qual campo deverá ser alterado.

1. Nome
1. Data de Nascimento
1. CPF
1. E-mail
1. Retornar

Para os menus de 1 a 4, o campo selecionado deve ser alterado para a pessoa que teve o seu nome pesquisado anteriormente, respeitando as validações já mencionadas. Já o menu "5 - Retornar", deverá voltar ao menu anterior *Editar / Pessoa / Nome* (2...1...1).

Caso a busca pelo nome não encontre uma pessoa na agenda, o programa deverá voltar ao menu anterior *Editar / Pessoa* (2...1).
