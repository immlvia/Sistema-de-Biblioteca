#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lista_livros.h"

// Gerar id do livro
int gerarProximoId(ListaLivros *lista) {

    NoLivro *atual = lista->head; // coloca ponteiro no começo da biblioteca
    int maiorId = 0; 

    while (atual != NULL) {
        // compara se o ID do nó atual é maior que o valor armazenado em maiorId
        if (atual->livro.id > maiorId) 
        maiorId = atual->livro.id; // atualiza a variável com o novo maior valor

        atual = atual->proximo; // passa pro próximo nó da lista
    }
    return maiorId + 1; // soma +1 para criar um id único
}
// Inicializa a lista
void inicializar_lista_livros(ListaLivros* lista) {
    lista->head = NULL; // garante que a lista comece vazia e não tenha nenhum lixo na mémoria 
    lista->tamanho = 0; // inicia o contador de elementos com 0
}

// Insere um livro no início da lista
void inserir_livro(ListaLivros* lista, Livro livro) {
    NoLivro* novo = (NoLivro*) malloc(sizeof(NoLivro)); // usa malloc para alocar dinanicamente espaço na memória ram
    if (novo == NULL) {
        printf("Erro: memória insuficiente!\n");
        return;
    }

    novo->livro = livro; // colocamos os dados da struct Livro para dentro do novo nó
    novo->proximo = lista->head; // o novo nó aponta para o atual início da lista (faz o elo)
    lista->head = novo; // o head passa a ser o novo nó que alocamos
    lista->tamanho++; 
}

// Remove um livro pelo ID
// Retorna 1 se removeu, 0 se não encontrou
int remover_livro(ListaLivros* lista, int id) {
    NoLivro* atual = lista->head;
    NoLivro* anterior = NULL;

    while (atual != NULL) {
        if (atual->livro.id == id) {
            if (anterior == NULL) {
                lista->head = atual->proximo;
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

    printf("Livro com ID %d não encontrado!\n", id);
    return 0;
}

// Busca livro pelo ID
// Retorna ponteiro para o livro ou NULL
Livro* buscar_livro_por_id(ListaLivros* lista, int id) {
    NoLivro* atual = lista->head;

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
    NoLivro* atual = lista->head;

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
    if (lista->head == NULL) {
        printf("Nenhum livro cadastrado!\n");
        return;
    }

    NoLivro* atual = lista->head;
    printf("\n===== LISTA DE LIVROS (%d) =====\n", lista->tamanho);

    while (atual != NULL) {
        printf("---------------------------\n");
        printf("ID: %d\n", atual->livro.id);
        printf("Titulo: %s\n", atual->livro.titulo);
        printf("Autor: %s\n", atual->livro.autor);
        printf("Ano: %d\n", atual->livro.ano);
        printf("Paginas: %d\n", atual->livro.paginas);
        printf("Status: %s\n", atual->livro.disponivel ? "Disponivel" : "Emprestado");
        atual = atual->proximo;
    }

    printf("===========================\n\n");
}

// Atualiza disponibilidade do livro
int atualizar_disponibilidade(ListaLivros* lista, int id, int disponivel) {
    Livro* livro = buscar_livro_por_id(lista, id);

    if (livro == NULL) {
        printf("Livro com ID %d não encontrado!\n", id);
        return 0;
    }

    livro->disponivel = disponivel;
    return 1;
}

// Libera toda a memória da lista
void destruir_lista_livros(ListaLivros* lista) {
    NoLivro* atual = lista->head;

    while (atual != NULL) {
        NoLivro* proximo = atual->proximo; // anota endereço do próximo livro com variável temporária (pra não perder o acesso do restante da biblioteca)
        free(atual); // quando o endereço tiver guardado, faz o free
        atual = proximo; // vai pro próximo ponteiro que deixamos guardado
    }

    lista->head = NULL;
    lista->tamanho = 0;
}

// Salva os livros em arquivo .txt
void salvar_livros(ListaLivros* lista, const char* arquivo) {
    FILE* fp = fopen(arquivo, "w");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo '%s' para escrita!\n", arquivo);
        return;
    }

    NoLivro* atual = lista->head;
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
        printf("Arquivo '%s' não encontrado. Iniciando lista vazia.\n", arquivo);
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