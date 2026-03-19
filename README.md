# Sistema-de-Biblioteca


Projeto desenvolvido em linguagem C para gerenciamento de uma biblioteca, utilizando estruturas de dados (listas encadeadas) para armazenar **livros**, **usuários** e **empréstimos**.

---

## 🚀 Funcionalidades

### 📖 Livros

* Cadastrar livros
* Listar livros
* Buscar livro por ID
* Remover livro (somente se disponível)
* Controle de disponibilidade

### 👤 Usuários

* Cadastrar usuários
* Listar usuários
* Buscar por ID ou nome
* Remover usuário (somente se não possuir empréstimos ativos)

### 🔄 Empréstimos

* Registrar empréstimos
* Devolver livros
* Listar empréstimos
* Buscar empréstimo por ID

---

## 🗂️ Estrutura do Projeto

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

## ⚙️ Como compilar

### 🔹 Usando Makefile (recomendado)

```bash
make
```

Isso irá gerar o executável:

```
biblioteca
```

---

### 🔹 Compilação manual

```bash
gcc -Wall -Iinclude src/main.c src/lista_livros.c src/lista_usuarios.c src/lista_emprestimos.c -o biblioteca
```

---

## ▶️ Como executar

```bash
./biblioteca
```

---

## 💾 Persistência de Dados

Os dados são salvos automaticamente na pasta `data/`:

* `livros.txt`
* `usuarios.txt`
* `emprestimos.txt`

Caso a pasta não exista, o sistema a cria automaticamente.

---

## 🧠 Tecnologias e Conceitos Utilizados

* Linguagem C
* Listas encadeadas
* Alocação dinâmica de memória (`malloc` / `free`)
* Manipulação de arquivos (`fopen`, `fprintf`, `fscanf`)
* Modularização com `.h` e `.c`

---

## ⚠️ Regras do Sistema

* Um livro não pode ser removido se estiver emprestado
* Um usuário não pode ser removido se tiver empréstimos ativos
* IDs são gerados automaticamente
* Campos não aceitam o caractere `|` (usado como separador nos arquivos)

---

## 📌 Observações

* O sistema armazena apenas IDs nos empréstimos, buscando dinamicamente os dados de livros e usuários para exibição
* Isso evita duplicação de dados e mantém consistência

---




