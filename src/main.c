#include <stdio.h>
#include "../include/lista_livros.h"
#include "../include/lista_usuarios.h"
#include "../include/lista_emprestimos.h"
void menuLivros(livro){
    int opcao;
    int id=0;
do{
    printf("\n===== MENU LIVROS =====\n");
    printf("1 - Cadastrar livro\n");
    printf("2 - Listar livros\n");
    printf("3 - Buscar livro\n");
    printf("4 - Remover livro\n");
    printf("0 - Voltar\n");
    printf("Digite a opção desejada\n");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        l.id = gerarProximoId(lista);

        printf("Titulo: ");
        scanf(" %[^\n]", l.nome);

        printf("Autor: ");
        scanf(" %[^\n]", l.autor);

        printf("Paginas: ");
        scanf("%d", &l.paginas);

        printf("Ano: ");
        scanf("%d", &l.ano);
        
        break;
    case 2:
        listarLivros(lista);
        break;
        
    case 3:
         int id;

         printf("Digite o ID do livro: ");
         scanf("%d", &id);

         Livro *l = buscarLivro(lista, id);

        if (l)
            printf("Livro: %s (%d)\n", l->titulo, l->ano);
        else
             printf("Livro nao encontrado\n");

        break;

    case 4:
        int id;

        printf("ID do livro para remover: ");
        scanf("%d", &id);

        removerLivro(lista, id);
        break;

    
    }
}while(opcao != 0);

};

void menuUsuario(usuarios){

};
void menuEmprestimos(livros,usuarios,emprestimos){

};
int main() {
    ListaLivros *livros = inicializarListaLivros();
    ListaUsuarios *usuarios = inicializarListaUsuarios();
    ListaEmprestimos *emprestimos = inicializarListaEmprestimos(); 
    int opcao;

    do{ 
        printf("===== SISTEMA DE BIBLIOTECA =====\n");
        printf("1 - Livros\n");
        printf("2 - Usuarios\n");
        printf("3 - Emprestimos\n");
        printf("0 - Sair\n");
        printf("Digite a opção desejada\n");
        scanf("%d",&opcao);
        switch (opcao)
        {
        case 1:
            menuLivros(livros);
            break;
        case 2:
            menuUsuarios(usuarios);
            break;
        case 3:
            menuEmprestimos(livros,usuarios,emprestimos);
            break;
        default:
            break;
        }


    }while(opcao != 0);
}

   