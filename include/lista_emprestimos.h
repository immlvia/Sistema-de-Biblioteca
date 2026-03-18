#ifndef LISTA_EMPRESTIMOS_H
#define LISTA_EMPRESTIMOS_H

typedef struct Emprestimo {
    int id;
    int id_livro;
    int id_usuario;
    char data_emprestimo[11]; 
    char data_devolucao[11];  
} Emprestimo;

typedef struct NoEmprestimo {
    Emprestimo emprestimo;
    struct NoEmprestimo* proximo;
} NoEmprestimo;

typedef struct ListaEmprestimos {
    NoEmprestimo* head;
    int tamanho;
} ListaEmprestimos;

int gerarProximoIdEmprestimo(ListaEmprestimos* lista);
void inicializar_lista_emprestimos(ListaEmprestimos* lista);
void inserir_emprestimo(ListaEmprestimos* lista, Emprestimo emprestimo);
int remover_emprestimo(ListaEmprestimos* lista, int id);
Emprestimo* buscar_emprestimo_por_id(ListaEmprestimos* lista, int id);
Emprestimo* buscar_emprestimo_por_usuario(ListaEmprestimos* lista, int id_usuario);
Emprestimo* buscar_emprestimo_por_livro(ListaEmprestimos* lista, int id_livro);
void listar_emprestimos(ListaEmprestimos* lista);
void destruir_lista_emprestimos(ListaEmprestimos* lista);
void salvar_emprestimos(ListaEmprestimos* lista, const char* arquivo);
void carregar_emprestimos(ListaEmprestimos* lista, const char* arquivo);
#endif 