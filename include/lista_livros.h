#ifndef LISTA_LIVROS_H
#define LISTA_LIVROS_H

typedef struct Livro {
    int id;
    char titulo[100];
    char autor[100];
    int ano;
    int paginas;
    int disponivel; // 1 = disponivel, 0 = emprestado
} Livro;


typedef struct NoLivro {
    Livro livro;
    struct NoLivro* proximo;
} NoLivro;

typedef struct ListaLivros {
    NoLivro* cabeca;
    int tamanho;
} ListaLivros;


void inicializar_lista_livros(ListaLivros* lista);
void inserir_livro(ListaLivros* lista, Livro livro);
int remover_livro(ListaLivros* lista, int id);
Livro* buscar_livro_por_id(ListaLivros* lista, int id);
Livro* buscar_livro_por_titulo(ListaLivros* lista, const char* titulo);
void listar_livros(ListaLivros* lista);
int atualizar_disponibilidade(ListaLivros* lista, int id, int disponivel);
void destruir_lista_livros(ListaLivros* lista);
void salvar_livros(ListaLivros* lista, const char* arquivo);
void carregar_livros(ListaLivros* lista, const char* arquivo);
#endif 