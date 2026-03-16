#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lista_usuarios.h"


int gerarProximoIdUsuario(ListaUsuarios* lista) {
    int maiorId = 0;
    NoUsuario* atual = lista->cabeca;

    while (atual != NULL) {
        if (atual->usuario.id > maiorId) {
            maiorId = atual->usuario.id;
        }
        atual = atual->proximo;
    }

    return maiorId + 1;
}

void inicializar_lista_usuarios(ListaUsuarios* lista) {
    if (lista != NULL) {
        lista->cabeca = NULL;
        lista->tamanho = 0;
    }
}

void inserir_usuario(ListaUsuarios* lista, Usuario usuario) {
    NoUsuario* novo = (NoUsuario*)malloc(sizeof(NoUsuario));
    if (novo == NULL) return;

    novo->usuario = usuario;
    novo->proximo = lista->cabeca;
    lista->cabeca = novo;
    lista->tamanho++;
}

int remover_usuario(ListaUsuarios* lista, int id) {
    NoUsuario* atual = lista->cabeca;
    NoUsuario* anterior = NULL;

    while (atual != NULL && atual->usuario.id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Usuário com ID %d não encontrado!\n", id); 
        return 0;
    }

    if (anterior == NULL) {
        lista->cabeca = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    lista->tamanho--;
    printf("Usuário removido com sucesso!\n"); // ← aqui
    return 1;
}

Usuario* buscar_usuario_por_id(ListaUsuarios* lista, int id) {
    NoUsuario* atual = lista->cabeca;

    while (atual != NULL) {
        if (atual->usuario.id == id) {
            return &(atual->usuario);
        }
        atual = atual->proximo;
    }

    return NULL;
}

Usuario* buscar_usuario_por_nome(ListaUsuarios* lista, const char* nome) {
    NoUsuario* atual = lista->cabeca;

    while (atual != NULL) {
        if (strcmp(atual->usuario.nome, nome) == 0) {
            return &(atual->usuario);
        }
        atual = atual->proximo;
    }

    return NULL;
}

void listar_usuarios(ListaUsuarios* lista) {
    NoUsuario* atual = lista->cabeca;

    if (atual == NULL) {
        printf("Nenhum usuário cadastrado.\n");
        return;
    }

    printf("\n===== LISTA DE USUÁRIOS (%d) =====\n", lista->tamanho);
    while (atual != NULL) {
        printf("---------------------------\n");
        printf("ID: %d\n", atual->usuario.id);
        printf("Nome: %s\n", atual->usuario.nome);
        atual = atual->proximo;
    }
    printf("===================================\n\n");
}

void destruir_lista_usuarios(ListaUsuarios* lista) {
    if (lista == NULL) return;

    NoUsuario* atual = lista->cabeca;
    NoUsuario* proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    lista->cabeca = NULL;
    lista->tamanho = 0;
}

void salvar_usuarios(ListaUsuarios* lista, const char* arquivo) {
    FILE* f = fopen(arquivo, "w");
    if (f == NULL) return;

    NoUsuario* atual = lista->cabeca;
    while (atual != NULL) {
        fprintf(f, "%d|%s\n",
            atual->usuario.id,
            atual->usuario.nome
        );
        atual = atual->proximo;
    }

    fclose(f);
    printf("Usuários salvos em '%s' com sucesso!\n", arquivo);
}

void carregar_usuarios(ListaUsuarios* lista, const char* arquivo) {
    FILE* f = fopen(arquivo, "r");
    if (f == NULL) {
        printf("Arquivo '%s' não encontrado. Iniciando lista vazia.\n", arquivo);
        return;
    }

    Usuario u;
    while (fscanf(f, "%d|%99[^\n]\n", &u.id, u.nome) == 2) {
        inserir_usuario(lista, u);
    }

    fclose(f);
    printf("Usuários carregados de '%s' com sucesso!\n", arquivo);
}