#include <stdio.h>
#include "../include/lista_livros.h"
#include "../include/lista_usuarios.h"
#include "../include/lista_emprestimos.h"


Livro l;
void menuLivros(ListaLivros *lista){
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
        scanf(" %[^\n]", l.titulo);

        printf("Autor: ");
        scanf(" %[^\n]", l.autor);

        printf("Paginas: ");
        scanf("%d", &l.paginas);

        printf("Ano: ");
        scanf("%d", &l.ano);
        l.disponivel = 1;

        inserir_livro(lista, l);

        break;
    case 2:
        listar_livros(lista);
        break;
        
    case 3:{
         int id;

         printf("Digite o ID do livro: ");
         scanf("%d", &id);

         Livro *l = buscar_livro_por_id(lista, id);

        if (l)
            printf("Livro: %s (%d)\n", l->titulo, l->ano);
        else
             printf("Livro nao encontrado\n");

        break;}

    case 4:
        int id;

        printf("ID do livro para remover: ");
        scanf("%d", &id);

        remover_livro(lista, id);
        break;

    
    }
}while(opcao != 0);

};

void menuUsuario(ListaUsuarios *lista)
{

    int opcao;
    
    do {
        printf("\n===== MENU USUARIOS =====\n");
        printf("1 - Cadastrar usuario\n");
        printf("2 - Listar usuarios\n");
        printf("3 - Buscar usuario por ID\n");
        printf("4 - Buscar usuario por nome\n");
        printf("5 - Remover usuario\n");
        printf("0 - Voltar\n");
        printf("Digite a opção desejada\n");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                Usuario novoUsuario;
                printf("Digite o ID do usuario: ");
                scanf("%d", &novoUsuario.id);
                
                printf("Digite o nome do usuario: ");
                scanf(" %[^\n]", novoUsuario.nome); 
                
                inserir_usuario(lista, novoUsuario);
                break;
            }
            case 2:
                printf("\n--- Lista de Usuarios ---\n");
                listar_usuarios(lista);
                break;
                
            case 3: {
                int idBusca;
                printf("Digite o ID do usuario: ");
                scanf("%d", &idBusca);
                
                Usuario *encontrado = buscar_usuario_por_id(lista, idBusca);
                if (encontrado != NULL) {
                    printf("\nUsuario encontrado!\n");
                    printf("ID: %d | Nome: %s\n", encontrado->id, encontrado->nome);
                } else {
                    printf("\nErro: Usuario com ID %d nao encontrado.\n", idBusca);
                }
                break;
            }
            case 4: {
                char nomeBusca[100];
                printf("Digite o nome do usuario: ");
                scanf(" %[^\n]", nomeBusca);
                
                Usuario *encontrado = buscar_usuario_por_nome(lista, nomeBusca);
                if (encontrado != NULL) {
                    printf("\nUsuario encontrado!\n");
                    printf("ID: %d | Nome: %s\n", encontrado->id, encontrado->nome);
                } else {
                    printf("\nErro: Usuario com nome '%s' nao encontrado.\n", nomeBusca);
                }
                break;
            }
            case 5: {
                int idRemover;
                printf("Digite o ID do usuario a ser removido: ");
                scanf("%d", &idRemover);
                
                if (remover_usuario(lista, idRemover)) {
                    printf("Usuario removido com sucesso!\n");
                } else {
                    printf("Erro: Usuario com ID %d nao encontrado.\n", idRemover);
                }
                break;
            }
            case 0:
                printf("\nA voltar ao menu principal...\n");
                break;
                
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

};
void menuEmprestimos(ListaLivros *livros, ListaUsuarios *usuarios, ListaEmprestimos *emprestimos)
{

};
int main() {
    ListaLivros livros;
    ListaUsuarios usuarios;
    ListaEmprestimos emprestimos;

    inicializar_lista_livros(&livros);
    inicializar_lista_usuarios(&usuarios);
    inicializar_lista_emprestimos(&emprestimos);

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
            menuLivros(&livros);
            break;
        case 2:
            menuUsuario(&usuarios);
            break;
        case 3:
            menuEmprestimos(&livros,&usuarios,&emprestimos);
            break;
        default:
            break;
        }


    }while(opcao != 0);
}

   