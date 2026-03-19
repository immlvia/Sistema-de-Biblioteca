#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lista_usuarios.h"

//Calcula o próximo ID disponível para um novo usuário
int gerarProximoIdUsuario(ListaUsuarios* lista) {
    int maiorId = 0;
    // Ponteiro 'atual' aponta para o início da lista para percorrê-la
    NoUsuario* atual = lista->head;

    while (atual != NULL) {
        // Estrutura de decisão: Se o ID do usuário atual for maior que 'maiorId', atualiza o valor
        if (atual->usuario.id > maiorId) {
            maiorId = atual->usuario.id;
        }
        // Move o ponteiro para o próximo nó da lista
        atual = atual->proximo;
    }

    return maiorId + 1;
}

// Prepara a lista para ser usada, definindo-a como vazia
void inicializar_lista_usuarios(ListaUsuarios* lista) {
    if (lista != NULL) {
        lista->head = NULL;
        lista->tamanho = 0;
    }
}

//Adiciona um novo usuário no início da lista
void inserir_usuario(ListaUsuarios* lista, Usuario usuario) {
    NoUsuario* novo = (NoUsuario*)malloc(sizeof(NoUsuario));
    if (novo == NULL) return;

    novo->usuario = usuario;     // Guarda os dados no novo nó
    novo->proximo = lista->head; // O próximo do novo nó passa a ser o antigo início da lista
    lista->head = novo;
    lista->tamanho++;
}

// Remove um usuário específico da lista baseado no seu ID
int remover_usuario(ListaUsuarios* lista, int id) {
    NoUsuario* atual = lista->head;
    NoUsuario* anterior = NULL;

    // Percorre a lista enquanto não chegar ao fim E o ID não for o procurado
    while (atual != NULL && atual->usuario.id != id) {
        anterior = atual;       // Guarda a posição atual
        atual = atual->proximo; // Avança para o próximo
    }

    if (atual == NULL) {
        printf("Usuário com ID %d não encontrado!\n", id); 
        return 0;
    }

    if (anterior == NULL) {
        lista->head = atual->proximo; 
    } else {
        // Reconecta a lista pulando o nó 'atual'
        anterior->proximo = atual->proximo;
    }

    free(atual); // Libera a memória que o ponteiro 'atual' estava ocupando
    lista->tamanho--;
    printf("Usuário removido com sucesso!\n");
    return 1;
}

// Retorna o ponteiro de um usuário se encontrar o ID na lista
Usuario* buscar_usuario_por_id(ListaUsuarios* lista, int id) {
    NoUsuario* atual = lista->head;

    // Loop para varrer todos os nós
    while (atual != NULL) {
        if (atual->usuario.id == id) {
            return &(atual->usuario);
        }
        atual = atual->proximo;
    }

    return NULL;
}

// Retorna o ponteiro de um usuário se encontrar o nome na lista
Usuario* buscar_usuario_por_nome(ListaUsuarios* lista, const char* nome) {
    NoUsuario* atual = lista->head;

    while (atual != NULL) {
        // strcmp compara duas strings. Retorna 0 se forem exatamente iguais
        if (strcmp(atual->usuario.nome, nome) == 0) {
            return &(atual->usuario);
        }
        atual = atual->proximo;
    }

    return NULL; // Não encontrado
}

// Exibe todos os usuários cadastrados
void listar_usuarios(ListaUsuarios* lista) {
    NoUsuario* atual = lista->head;

    // Se o início for nulo, a lista está vazia
    if (atual == NULL) {
        printf("Nenhum usuário cadastrado.\n");
        return;
    }

    printf("\n===== LISTA DE USUÁRIOS (%d) =====\n", lista->tamanho);
    // Percorre até o fim imprimindo os dados acessados pelo ponteiro 'atual'
    while (atual != NULL) {
        printf("---------------------------\n");
        printf("ID: %d\n", atual->usuario.id);
        printf("Nome: %s\n", atual->usuario.nome);
        atual = atual->proximo;
    }
    printf("===================================\n\n");
}

// Apaga a lista inteira e libera toda a memória
void destruir_lista_usuarios(ListaUsuarios* lista) {
    if (lista == NULL) return;

    NoUsuario* atual = lista->head;
    NoUsuario* proximo;

    // Caminha pela lista guardando o próximo, apagando o atual e avançando
    while (atual != NULL) {
        proximo = atual->proximo; // Salva o endereço do próximo antes de apagar o atual
        free(atual);              
        atual = proximo;          
    }

    lista->head = NULL;
    lista->tamanho = 0;
}

//Salva os dados de todos os usuários em um arquivo de texto
void salvar_usuarios(ListaUsuarios* lista, const char* arquivo) {
    // 'fopen' cria um ponteiro de arquivo em modo de escrita ("w")
    FILE* f = fopen(arquivo, "w");
    if (f == NULL) return;

    NoUsuario* atual = lista->head;
    // Grava os dados formato "ID|Nome" linha por linha
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

// Lê um arquivo de texto e recria a lista de usuários na memória
void carregar_usuarios(ListaUsuarios* lista, const char* arquivo) {
    // 'fopen' cria um ponteiro de arquivo em modo de leitura ("r")
    FILE* f = fopen(arquivo, "r");
    if (f == NULL) {
        printf("Arquivo '%s' não encontrado. Iniciando lista vazia.\n", arquivo);
        return;
    }

    Usuario u;
    // Lê o arquivo extraindo o ID e o Nome delimitados pelo pipe '|'
    while (fscanf(f, "%d|%99[^\n]\n", &u.id, u.nome) == 2) {
        inserir_usuario(lista, u);
    }

    fclose(f);
    printf("Usuários carregados de '%s' com sucesso!\n", arquivo);
}