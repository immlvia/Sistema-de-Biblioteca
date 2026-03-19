# Sistema-de-Biblioteca

O Sistema de Biblioteca é uma aplicação desenvolvida em linguagem C que permite o gerenciamento de livros, usuários e empréstimos. O sistema utiliza listas encadeadas para armazenar dados em memória e arquivos `.txt` para persistência, possibilitando o controle de cadastros, empréstimos e devoluções de forma simples e eficiente.

---

## Instalação e Configuração

### Pré-requisitos

* Compilador C (gcc recomendado)
* Sistema operacional Linux, macOS ou Windows (com terminal compatível)
* Make (opcional, mas recomendado)

---

## Passos para instalação

### Clone o repositório

```bash
git clone <URL-do-repositorio>
cd Sistema-de-Biblioteca
```

---

### Compile o projeto

#### Usando Makefile (recomendado)

```bash
make
```

#### Compilação manual

```bash
gcc -Wall -Iinclude src/main.c src/lista_livros.c src/lista_usuarios.c src/lista_emprestimos.c -o biblioteca
```

---

## Executando o projeto

### Inicie o sistema

```bash
./biblioteca
```

---

## Persistência de dados

O sistema utiliza arquivos `.txt` localizados na pasta `data/`:

* `livros.txt`
* `usuarios.txt`
* `emprestimos.txt`

Caso a pasta não exista, ela será criada automaticamente ao executar o sistema.

---

## Para encerrar a aplicação

Pressione:

```bash
CTRL + C
```

ou selecione a opção de sair no menu principal.

---

## Executando em próximas sessões

Sempre que quiser executar o sistema novamente:

```bash
cd caminho/para/Sistema-de-Biblioteca
./biblioteca
```

---

## Funcionalidades

### Livros

* Cadastro de livros
* Listagem de livros
* Busca por ID
* Remoção (apenas se disponível)

### Usuários

* Cadastro de usuários
* Listagem
* Busca por ID ou nome
* Remoção (apenas sem empréstimos ativos)

### Empréstimos

* Registro de empréstimos
* Devolução de livros
* Listagem de empréstimos
* Busca por ID

---

## Regras do Sistema

* Um livro não pode ser removido se estiver emprestado
* Um usuário não pode ser removido se possuir empréstimos ativos
* IDs são gerados automaticamente
* O caractere `|` não pode ser utilizado nos campos de entrada

---

## Estrutura do Projeto

```
Sistema-de-Biblioteca/
│
├── src/
│   ├── main.c
│   ├── lista_livros.c
│   ├── lista_usuarios.c
│   └── lista_emprestimos.c
│
├── include/
│   ├── lista_livros.h
│   ├── lista_usuarios.h
│   └── lista_emprestimos.h
│
├── data/
│   ├── livros.txt
│   ├── usuarios.txt
│   └── emprestimos.txt
│
├── Makefile
└── README.md
```

---

## Ferramentas para Desenvolvedores

O projeto foi desenvolvido utilizando:

* Linguagem C
* Listas encadeadas
* Alocação dinâmica de memória (`malloc` e `free`)
* Manipulação de arquivos (`fopen`, `fprintf`, `fscanf`)

---

## Observações

O sistema armazena apenas os IDs nos registros de empréstimos, utilizando buscas nas listas de livros e usuários para exibir informações completas (nome e título). Essa abordagem evita redundância e mantém a consistência dos dados.

---

