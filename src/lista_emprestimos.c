#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lista_emprestimos.h"
#include "../include/lista_livros.h"
#include "../include/lista_usuarios.h"

int gerarProximoIdEmprestimo(ListaEmprestimos* lista) {
    int maiorId = 0;
    NoEmprestimo* atual = lista->head;
    while (atual != NULL) {
        if (atual->emprestimo.id > maiorId)
            maiorId = atual->emprestimo.id;
        atual = atual->proximo;
    }
    return maiorId + 1;
}

// Inicializa a lista
void inicializar_lista_emprestimos(ListaEmprestimos* lista){
    lista->head = NULL;
    lista->tamanho = 0;
}

// Insere um empréstimo no início da lista
void inserir_emprestimo(ListaEmprestimos* lista, Emprestimo emprestimo) {
    NoEmprestimo* novo = (NoEmprestimo*) malloc(sizeof(NoEmprestimo));
    if (novo == NULL) {
        printf("Erro: memória insuficiente!\n");
        return;
    }

    novo->emprestimo = emprestimo;
    novo->proximo = lista->head;
    lista->head = novo;
    lista->tamanho++;
}

// Remove um empréstimo pelo ID
// Retorna 1 se removeu, 0 se não encontrou
int remover_emprestimo(ListaEmprestimos* lista, int id) {
    NoEmprestimo* atual = lista->head;
    NoEmprestimo* anterior = NULL;

    while (atual != NULL) {
        if (atual->emprestimo.id == id) {
            if (anterior == NULL) {
                lista->head = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            lista->tamanho--;
            return 1;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Empréstimo com ID %d não encontrado!\n", id);
    return 0;
}

// Busca empréstimo pelo ID
// Retorna ponteiro para o empréstimo ou NULL
Emprestimo* buscar_emprestimo_por_id(ListaEmprestimos* lista, int id) {
    NoEmprestimo* atual = lista->head;

    while (atual != NULL) {
        if (atual->emprestimo.id == id) {
            return &atual->emprestimo;
        }
        atual = atual->proximo;
    }

    return NULL;
}

// Busca o primeiro empréstimo ativo de um usuário
// Retorna ponteiro para o empréstimo ou NULL
Emprestimo* buscar_emprestimo_por_usuario(ListaEmprestimos* lista, int id_usuario) {
    NoEmprestimo* atual = lista->head;

    while (atual != NULL) {
        if (atual->emprestimo.id_usuario == id_usuario) {
            return &atual->emprestimo;
        }
        atual = atual->proximo;
    }

    return NULL;
}

// Busca o empréstimo ativo de um livro
// Retorna ponteiro para o empréstimo ou NULL
Emprestimo* buscar_emprestimo_por_livro(ListaEmprestimos* lista, int id_livro) {
    NoEmprestimo* atual = lista->head;

    while (atual != NULL) {
        if (atual->emprestimo.id_livro == id_livro) {
            return &atual->emprestimo;
        }
        atual = atual->proximo;
    }

    return NULL;
}

// Lista todos os empréstimos
void listar_emprestimos(ListaEmprestimos* lista, ListaLivros* livros, ListaUsuarios* usuarios) {
    if (lista->head == NULL) {
        printf("Nenhum empréstimo registrado!\n");
        return;
    }

    NoEmprestimo* atual = lista->head;
    printf("\n===== LISTA DE EMPRESTIMOS (%d) =====\n", lista->tamanho);

    while (atual != NULL) {
        printf("---------------------------\n");
        printf("ID: %d\n", atual->emprestimo.id);
        Livro* livro = buscar_livro_por_id(livros, atual->emprestimo.id_livro);
        Usuario* usuario = buscar_usuario_por_id(usuarios, atual->emprestimo.id_usuario);

        if (livro != NULL)
            printf("Livro: %s\n", livro->titulo);
        else
            printf("Livro: Não encontrado\n");

        if (usuario != NULL)
            printf("Usuário: %s\n", usuario->nome);
        else
            printf("Usuário: Não encontrado\n");
        printf("Emprestimo: %s\n", atual->emprestimo.data_emprestimo);
        printf("Devolucao: %s\n", atual->emprestimo.data_devolucao);
        atual = atual->proximo;
    }

    printf("=====================================\n\n");
}

// Libera toda a memória da lista
void destruir_lista_emprestimos(ListaEmprestimos* lista) {
    NoEmprestimo* atual = lista->head;

    while (atual != NULL) {
        NoEmprestimo* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    lista->head = NULL;
    lista->tamanho = 0;
}

// Salva os empréstimos em arquivo .txt
void salvar_emprestimos(ListaEmprestimos* lista, const char* arquivo) {
    FILE* fp = fopen(arquivo, "w");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo '%s' para escrita!\n", arquivo);
        return;
    }

    NoEmprestimo* atual = lista->head;
    while (atual != NULL) {
        fprintf(fp, "%d|%d|%d|%s|%s\n",
            atual->emprestimo.id,
            atual->emprestimo.id_livro,
            atual->emprestimo.id_usuario,
            atual->emprestimo.data_emprestimo,
            atual->emprestimo.data_devolucao
        );
        atual = atual->proximo;
    }

    fclose(fp);
    printf("Empréstimos salvos em '%s' com sucesso!\n", arquivo);
}

// Carrega os empréstimos de um arquivo .txt
void carregar_emprestimos(ListaEmprestimos* lista, const char* arquivo) {
    FILE* fp = fopen(arquivo, "r");
    if (fp == NULL) {
        printf("Arquivo '%s' não encontrado. Iniciando lista vazia.\n", arquivo);
        return;
    }

    Emprestimo emprestimo;
    while (fscanf(fp, "%d|%d|%d|%10[^|]|%10[^\n]\n",
        &emprestimo.id,
        &emprestimo.id_livro,
        &emprestimo.id_usuario,
        emprestimo.data_emprestimo,
        emprestimo.data_devolucao) == 5)
    {
        inserir_emprestimo(lista, emprestimo);
    }

    fclose(fp);
    printf("Emprestimos carregados de '%s' com sucesso!\n", arquivo);
}