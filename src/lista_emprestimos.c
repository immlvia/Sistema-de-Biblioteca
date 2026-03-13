#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lista_emprestimos.h"

// Inicializa a lista
void inicializar_lista_emprestimos(ListaEmprestimos* lista) {
    lista->cabeca = NULL;
    lista->tamanho = 0;
}

// Insere um empréstimo no início da lista
void inserir_emprestimo(ListaEmprestimos* lista, Emprestimo emprestimo) {
    NoEmprestimo* novo = (NoEmprestimo*) malloc(sizeof(NoEmprestimo));
    if (novo == NULL) {
        printf("Erro: memoria insuficiente!\n");
        return;
    }

    novo->emprestimo = emprestimo;
    novo->proximo = lista->cabeca;
    lista->cabeca = novo;
    lista->tamanho++;

    printf("Emprestimo ID %d registrado com sucesso!\n", emprestimo.id);
}

// Remove um empréstimo pelo ID
// Retorna 1 se removeu, 0 se não encontrou
int remover_emprestimo(ListaEmprestimos* lista, int id) {
    NoEmprestimo* atual = lista->cabeca;
    NoEmprestimo* anterior = NULL;

    while (atual != NULL) {
        if (atual->emprestimo.id == id) {
            if (anterior == NULL) {
                lista->cabeca = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            lista->tamanho--;
            printf("Emprestimo ID %d removido com sucesso!\n", id);
            return 1;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Emprestimo com ID %d nao encontrado!\n", id);
    return 0;
}

// Busca empréstimo pelo ID
// Retorna ponteiro para o empréstimo ou NULL
Emprestimo* buscar_emprestimo_por_id(ListaEmprestimos* lista, int id) {
    NoEmprestimo* atual = lista->cabeca;

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
    NoEmprestimo* atual = lista->cabeca;

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
    NoEmprestimo* atual = lista->cabeca;

    while (atual != NULL) {
        if (atual->emprestimo.id_livro == id_livro) {
            return &atual->emprestimo;
        }
        atual = atual->proximo;
    }

    return NULL;
}

// Lista todos os empréstimos
void listar_emprestimos(ListaEmprestimos* lista) {
    if (lista->cabeca == NULL) {
        printf("Nenhum emprestimo registrado!\n");
        return;
    }

    NoEmprestimo* atual = lista->cabeca;
    printf("\n===== LISTA DE EMPRESTIMOS (%d) =====\n", lista->tamanho);

    while (atual != NULL) {
        printf("---------------------------\n");
        printf("ID           : %d\n", atual->emprestimo.id);
        printf("ID Livro     : %d\n", atual->emprestimo.id_livro);
        printf("ID Usuario   : %d\n", atual->emprestimo.id_usuario);
        printf("Emprestimo   : %s\n", atual->emprestimo.data_emprestimo);
        printf("Devolucao    : %s\n", atual->emprestimo.data_devolucao);
        atual = atual->proximo;
    }

    printf("=====================================\n\n");
}

// Libera toda a memória da lista
void destruir_lista_emprestimos(ListaEmprestimos* lista) {
    NoEmprestimo* atual = lista->cabeca;

    while (atual != NULL) {
        NoEmprestimo* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    lista->cabeca = NULL;
    lista->tamanho = 0;
}

// Salva os empréstimos em arquivo .txt
void salvar_emprestimos(ListaEmprestimos* lista, const char* arquivo) {
    FILE* fp = fopen(arquivo, "w");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo '%s' para escrita!\n", arquivo);
        return;
    }

    NoEmprestimo* atual = lista->cabeca;
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
    printf("Emprestimos salvos em '%s' com sucesso!\n", arquivo);
}

// Carrega os empréstimos de um arquivo .txt
void carregar_emprestimos(ListaEmprestimos* lista, const char* arquivo) {
    FILE* fp = fopen(arquivo, "r");
    if (fp == NULL) {
        printf("Arquivo '%s' nao encontrado. Iniciando lista vazia.\n", arquivo);
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