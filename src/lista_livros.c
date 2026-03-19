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
    NoLivro* atual = lista->head; // coloca o ponteiro no começo da biblioteca
    NoLivro* anterior = NULL; // o ponteiro anterior começa com NULL, pois não passamos por nenhum nó

    while (atual != NULL) {
        if (atual->livro.id == id) { // compara se o ID do nó atual é igual ao id que o usuário digitou
            // caso 1: o livro a ser removido é o primeiro da lista
            if (anterior == NULL) {   
                lista->head = atual->proximo; // o head pula o primeiro e passa a apontar para o segundo nó 
            // caso 2: se o id estiver no meio ou final da lista
            } else {
                anterior->proximo = atual->proximo; // o nó anterior pula o atual e faz o elo com o próximo da lista
            }
            free(atual); // devolve a memória para o sistema
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
    NoLivro* atual = lista->head; // coloca o ponteiro atual no começo da biblioteca

    while (atual != NULL) {
        // se encontrar o id do livro igual ao que o usuário digitou
        if (atual->livro.id == id) {
            return &atual->livro; // retorna o endereço de memória
        }
        atual = atual->proximo; // se não encontrou, atualizo com o endereço do próximo nó
    }

    return NULL; // se não tiver achado retorna nulo
}

// Lista todos os livros
void listar_livros(ListaLivros* lista) {
    // verifica se a lista está vazia antes de tentar percorrer
    if (lista->head == NULL) {
        printf("Nenhum livro cadastrado!\n");
        return;
    }

    NoLivro* atual = lista->head; // coloca o ponteiro atual no começo da biblioteca
    printf("\n===== LISTA DE LIVROS (%d) =====\n", lista->tamanho);
    
    // enquanto o ponteiro não atingir o final da lista
    while (atual != NULL) {
        printf("---------------------------\n");
        printf("ID: %d\n", atual->livro.id);
        printf("Titulo: %s\n", atual->livro.titulo);
        printf("Autor: %s\n", atual->livro.autor);
        printf("Ano: %d\n", atual->livro.ano);
        printf("Paginas: %d\n", atual->livro.paginas);
        printf("Status: %s\n", atual->livro.disponivel ? "Disponivel" : "Emprestado"); // converte valor booleano em texto
        atual = atual->proximo; // aponta pro endereço do próximo nó da lista
    }

    printf("===========================\n\n");
}

// Atualiza disponibilidade do livro
int atualizar_disponibilidade(ListaLivros* lista, int id, int disponivel) {
    // busca o endereço de memória do livro específico na biblioteca
    Livro* livro = buscar_livro_por_id(lista, id);

    if (livro == NULL) {
        printf("Livro com ID %d não encontrado!\n", id);
        return 0;
    }
    // acessa o endereço do livro e atualiza o campo disponivel com o novo valor
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
    // abre um arquivo do tipo ponteiro com W para escrever nossos dados no arquivo .txt
    FILE* fp = fopen(arquivo, "w");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo '%s' para escrita!\n", arquivo);
        return;
    }
    // coloca o ponteiro atual no começo da biblioteca
    NoLivro* atual = lista->head;
    while (atual != NULL) {
        // usa o fprintf para escrever no arquivo
        fprintf(fp, "%d|%s|%s|%d|%d|%d\n",
            atual->livro.id,
            atual->livro.titulo,
            atual->livro.autor,
            atual->livro.ano,
            atual->livro.paginas,
            atual->livro.disponivel
        );
        // move o ponteiro para o próximo nó da lista
        atual = atual->proximo;
    }
    // fecha o arquivo
    fclose(fp);
    printf("Livros salvos em '%s' com sucesso!\n", arquivo);
}

// Carrega os livros de um arquivo .txt
void carregar_livros(ListaLivros* lista, const char* arquivo) {
    // abre o arquivo para leitura com o R
    FILE* fp = fopen(arquivo, "r");
    if (fp == NULL) {
        printf("Arquivo '%s' não encontrado. Iniciando lista vazia.\n", arquivo);
        return;
    }
    // cria uma struct local
    Livro livro;
    // lê os campos 
    while (fscanf(fp, "%d|%99[^|]|%99[^|]|%d|%d|%d\n",
        &livro.id,
        livro.titulo,
        livro.autor,
        &livro.ano,
        &livro.paginas,
        &livro.disponivel) == 6) // verefica se os seis campos estão todos lá
    {
        //usa a função inserir para colocar tudo na memória RAM de novo
        inserir_livro(lista, livro);
    }
    // fecha o arquivo
    fclose(fp);
    printf("Livros carregados de '%s' com sucesso!\n", arquivo);
} 