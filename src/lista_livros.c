#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lista_livros.h"

// Gerar id do livro
int gerarProximoId(ListaLivros *lista) {

    NoLivro *atual = lista->cabeca;
    int maiorId = 0;

    while (atual != NULL) {

        if (atual->livro.id > maiorId)
            maiorId = atual->livro.id;

        atual = atual->proximo;
    }
// Inicializa a lista
void inicializar_lista_livros(ListaLivros* lista) {
    lista->cabeca = NULL;
    lista->tamanho = 0;
}

// Insere um livro no início da lista
void inserir_livro(ListaLivros* lista, Livro livro) {
    NoLivro* novo = (NoLivro*) malloc(sizeof(NoLivro));
    if (novo == NULL) {
        printf("Erro: memoria insuficiente!\n");
        return;
    }

    novo->livro = livro;
    novo->proximo = lista->cabeca;
    lista->cabeca = novo;
    lista->tamanho++;

    printf("Livro '%s' cadastrado com sucesso!\n", livro.titulo);
}

// Remove um livro pelo ID
// Retorna 1 se removeu, 0 se não encontrou
int remover_livro(ListaLivros* lista, int id) {
    NoLivro* atual = lista->cabeca;
    NoLivro* anterior = NULL;

    while (atual != NULL) {
        if (atual->livro.id == id) {
            if (anterior == NULL) {
                lista->cabeca = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            lista->tamanho--;
            printf("Livro removido com sucesso!\n");
            return 1;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Livro com ID %d nao encontrado!\n", id);
    return 0;
}

// Busca livro pelo ID
// Retorna ponteiro para o livro ou NULL
Livro* buscar_livro_por_id(ListaLivros* lista, int id) {
    NoLivro* atual = lista->cabeca;

    while (atual != NULL) {
        if (atual->livro.id == id) {
            return &atual->livro;
        }
        atual = atual->proximo;
    }

    return NULL;
}

// Busca livro pelo título
// Retorna ponteiro para o livro ou NULL
Livro* buscar_livro_por_titulo(ListaLivros* lista, const char* titulo) {
    NoLivro* atual = lista->cabeca;

    while (atual != NULL) {
        if (strcmp(atual->livro.titulo, titulo) == 0) {
            return &atual->livro;
        }
        atual = atual->proximo;
    }

    return NULL;
}

// Lista todos os livros
void listar_livros(ListaLivros* lista) {
    if (lista->cabeca == NULL) {
        printf("Nenhum livro cadastrado!\n");
        return;
    }

    NoLivro* atual = lista->cabeca;
    printf("\n===== LISTA DE LIVROS (%d) =====\n", lista->tamanho);

    while (atual != NULL) {
        printf("---------------------------\n");
        printf("ID       : %d\n", atual->livro.id);
        printf("Titulo   : %s\n", atual->livro.titulo);
        printf("Autor    : %s\n", atual->livro.autor);
        printf("Ano      : %d\n", atual->livro.ano);
        printf("Paginas  : %d\n", atual->livro.paginas);
        printf("Status   : %s\n", atual->livro.disponivel ? "Disponivel" : "Emprestado");
        atual = atual->proximo;
    }

    printf("===========================\n\n");
}

// Atualiza disponibilidade do livro
// Retorna 1 se atualizou, 0 se não encontrou
int atualizar_disponibilidade(ListaLivros* lista, int id, int disponivel) {
    Livro* livro = buscar_livro_por_id(lista, id);

    if (livro == NULL) {
        printf("Livro com ID %d nao encontrado!\n", id);
        return 0;
    }

    livro->disponivel = disponivel;
    printf("Disponibilidade do livro '%s' atualizada!\n", livro->titulo);
    return 1;
}

// Libera toda a memória da lista
void destruir_lista_livros(ListaLivros* lista) {
    NoLivro* atual = lista->cabeca;

    while (atual != NULL) {
        NoLivro* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    lista->cabeca = NULL;
    lista->tamanho = 0;
}

// Salva os livros em arquivo .txt
void salvar_livros(ListaLivros* lista, const char* arquivo) {
    FILE* fp = fopen(arquivo, "w");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo '%s' para escrita!\n", arquivo);
        return;
    }

    NoLivro* atual = lista->cabeca;
    while (atual != NULL) {
        fprintf(fp, "%d|%s|%s|%d|%d|%d\n",
            atual->livro.id,
            atual->livro.titulo,
            atual->livro.autor,
            atual->livro.ano,
            atual->livro.paginas,
            atual->livro.disponivel
        );
        atual = atual->proximo;
    }

    fclose(fp);
    printf("Livros salvos em '%s' com sucesso!\n", arquivo);
}

// Carrega os livros de um arquivo .txt
void carregar_livros(ListaLivros* lista, const char* arquivo) {
    FILE* fp = fopen(arquivo, "r");
    if (fp == NULL) {
        printf("Arquivo '%s' nao encontrado. Iniciando lista vazia.\n", arquivo);
        return;
    }

    Livro livro;
    while (fscanf(fp, "%d|%99[^|]|%99[^|]|%d|%d|%d\n",
        &livro.id,
        livro.titulo,
        livro.autor,
        &livro.ano,
        &livro.paginas,
        &livro.disponivel) == 6)
    {
        inserir_livro(lista, livro);
    }

    fclose(fp);
    printf("Livros carregados de '%s' com sucesso!\n", arquivo);
}