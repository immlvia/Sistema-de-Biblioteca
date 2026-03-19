#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include "../include/lista_livros.h"
#include "../include/lista_usuarios.h"
#include "../include/lista_emprestimos.h"

// Limpa o buffer do teclado após entrada inválida
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Lê inteiro com validação para evitar loop infinito
int lerInteiro(const char *mensagem) {
    int valor;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%d", &valor) == 1) {
            limparBuffer();
            return valor;
        }
        printf("Entrada inválida! Digite um número.\n");
        limparBuffer();
    }
}

// Verifica se string contém o caractere '|'
int contemPipe(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '|') return 1;
    }
    return 0;
}

int apenasLetras(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!((str[i] >= 'a' && str[i] <= 'z') ||
              (str[i] >= 'A' && str[i] <= 'Z') ||
               str[i] == ' '))
            return 0;
    }
    return 1;
}

// Cria a pasta data/ automaticamente se não existir
void criarPastaData() {
    struct stat st = {0};
    if (stat("data", &st) == -1) {
        mkdir("data", 0700);
    }
}

// Menu de Livros
void menuLivros(ListaLivros *lista) {
    int opcao;

    do {
        printf("\n===== MENU LIVROS =====\n");
        printf("1 - Cadastrar livro\n");
        printf("2 - Listar livros\n");
        printf("3 - Buscar livro por ID\n");
        printf("4 - Remover livro\n");
        printf("0 - Voltar\n");
        opcao = lerInteiro("Digite a opção desejada: ");

        switch (opcao) {
            case 1: {
                Livro l;
                l.id = gerarProximoId(lista);

                do {
                    printf("Titulo: ");
                    scanf(" %[^\n]", l.titulo);
                    if (contemPipe(l.titulo))
                        printf("Erro: titulo não pode conter o caractere '|'!\n");
                } while (contemPipe(l.titulo));

                do {
                    printf("Autor: ");
                    scanf(" %[^\n]", l.autor);
                    if (contemPipe(l.autor))
                        printf("Erro: autor não pode conter o caractere '|'!\n");
                } while (contemPipe(l.autor));

                l.paginas    = lerInteiro("Paginas: ");
                l.ano        = lerInteiro("Ano: ");
                l.disponivel = 1;

                inserir_livro(lista, l);
                printf("Livro '%s' cadastrado com sucesso!\n", l.titulo);
                break;
            }
            case 2:
                listar_livros(lista);
                break;

            case 3: {
                int id = lerInteiro("Digite o ID do livro: ");

                Livro *encontrado = buscar_livro_por_id(lista, id);
                if (encontrado != NULL) {
                    printf("\n---------------------------\n");
                    printf("ID: %d\n", encontrado->id);
                    printf("Titulo: %s\n", encontrado->titulo);
                    printf("Autor: %s\n", encontrado->autor);
                    printf("Ano: %d\n", encontrado->ano);
                    printf("Pagina: %d\n", encontrado->paginas);
                    printf("Status: %s\n", encontrado->disponivel ? "Disponivel" : "Emprestado");
                    printf("---------------------------\n");
                } else {
                    printf("Livro com ID %d não encontrado!\n", id);
                }
                break;
            }
            case 4: {
                int id = lerInteiro("ID do livro para remover: ");

                Livro *livro = buscar_livro_por_id(lista, id);
                if (livro == NULL) {
                    printf("Livro com ID %d não encontrado!\n", id);
                    break;
                }
                if (livro->disponivel == 0) {
                    printf("Erro: Livro '%s' está emprestado e não pode ser removido!\n", livro->titulo);
                    break;
                }
                remover_livro(lista, id);
                break;
            }
            case 0:
                printf("Voltando ao menu principal...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Menu de Usuarios
void menuUsuario(ListaUsuarios *lista, ListaEmprestimos *emprestimos) {
    int opcao;
 
    do {
        printf("\n===== MENU USUARIOS =====\n");
        printf("1 - Cadastrar usuario\n");
        printf("2 - Listar usuarios\n");
        printf("3 - Buscar usuario por ID\n");
        printf("4 - Buscar usuario por nome\n");
        printf("5 - Remover usuario\n");
        printf("0 - Voltar\n");
        opcao = lerInteiro("Digite a opcao desejada: ");
 
        switch (opcao) {
            case 1: {
                Usuario novoUsuario;
                novoUsuario.id = gerarProximoIdUsuario(lista);
 
                // Valida nome
                do {
                    printf("Nome: ");
                    scanf(" %[^\n]", novoUsuario.nome);
                    if (contemPipe(novoUsuario.nome))
                        printf("Erro: nome não pode conter '|'!\n");
                    else if (!apenasLetras(novoUsuario.nome))
                        printf("Erro: nome não pode conter números ou simbolos!\n");
                } while (contemPipe(novoUsuario.nome) || !apenasLetras(novoUsuario.nome));
 
                inserir_usuario(lista, novoUsuario);
                printf("Usuario cadastrado com ID %d!\n", novoUsuario.id);
                break;
            }
            case 2:
                listar_usuarios(lista);
                break;
 
            case 3: {
                int id = lerInteiro("Digite o ID do usuário: ");
 
                Usuario *encontrado = buscar_usuario_por_id(lista, id);
                if (encontrado != NULL) {
                    printf("\n---------------------------\n");
                    printf("ID: %d\n", encontrado->id);
                    printf("Nome: %s\n", encontrado->nome);
                    printf("---------------------------\n");
                } else {
                    printf("Usuario com ID %d não encontrado!\n", id);
                }
                break;
            }
            case 4: {
                char nome[100];
                printf("Digite o nome do usuario: ");
                scanf(" %[^\n]", nome);
 
                Usuario *encontrado = buscar_usuario_por_nome(lista, nome);
                if (encontrado != NULL) {
                    printf("\n---------------------------\n");
                    printf("ID: %d\n", encontrado->id);
                    printf("Nome: %s\n", encontrado->nome);
                    printf("---------------------------\n");
                } else {
                    printf("Usuário '%s' não encontrado!\n", nome);
                }
                break;
            }
            case 5: {
                int id = lerInteiro("ID do usuário para remover: ");
 
                Emprestimo *emp = buscar_emprestimo_por_usuario(emprestimos, id);
                if (emp != NULL) {
                    printf("Erro: Usuário possui empréstimo ativo e não pode ser removido!\n");
                    break;
                }
                remover_usuario(lista, id);
                break;
            }
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
 
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Menu de Emprestimos
void menuEmprestimos(ListaLivros *livros, ListaUsuarios *usuarios, ListaEmprestimos *emprestimos) {
    int opcao;

    do {
        printf("\n===== MENU EMPRESTIMOS =====\n");
        printf("1 - Registrar empréstimo\n");
        printf("2 - Devolver livro\n");
        printf("3 - Listar empréstimos\n");
        printf("4 - Buscar empréstimo por ID\n");
        printf("0 - Voltar\n");
        opcao = lerInteiro("Digite a opção desejada: ");

        switch (opcao) {
            // Registrar empréstimo
            case 1: {
                Emprestimo novo;

                novo.id_livro = lerInteiro("ID do livro: ");
                Livro *livro = buscar_livro_por_id(livros, novo.id_livro);
                if (livro == NULL) {
                    printf("Erro: Livro com ID %d não encontrado!\n", novo.id_livro);
                    break;
                }
                if (livro->disponivel == 0) {
                    printf("Erro: Livro '%s' já está emprestado!\n", livro->titulo);
                    break;
                }
                // Verifica se o usuário existe
                novo.id_usuario = lerInteiro("ID do usuário: ");
                Usuario *usuario = buscar_usuario_por_id(usuarios, novo.id_usuario);
                if (usuario == NULL) {
                    printf("Erro: Usuário com ID %d não encontrado!\n", novo.id_usuario);
                    break;
                }

                printf("Data de empréstimo (DD/MM/AAAA): ");
                scanf(" %[^\n]", novo.data_emprestimo);

                calcular_data_devolucao(novo.data_emprestimo, novo.data_devolucao);

                printf("Data de devolução automática: %s\n", novo.data_devolucao);

                novo.id = gerarProximoIdEmprestimo(emprestimos);

                inserir_emprestimo(emprestimos, novo);
                atualizar_disponibilidade(livros, novo.id_livro, 0);

                printf("Emprestimo registrado! '%s' emprestado para '%s'.\n",
                    livro->titulo, usuario->nome);
                break;
            }
            // Devolver livro
            case 2: {
                int id = lerInteiro("ID do emprestimo para devolver: ");

                Emprestimo *emp = buscar_emprestimo_por_id(emprestimos, id);
                if (emp == NULL) {
                    printf("Erro: Empréstimo com ID %d não encontrado!\n", id);
                    break;
                }

                int idLivro = emp->id_livro;
                remover_emprestimo(emprestimos, id);
                atualizar_disponibilidade(livros, idLivro, 1);

                printf("Livro devolvido com sucesso!\n");
                break;
            }
            // Listar empréstimos
            case 3:
                listar_emprestimos(emprestimos, livros, usuarios);
                break;

            // Buscar empréstimo por ID 
            case 4: {
                int id = lerInteiro("ID do usuário: ");
                listar_emprestimos_por_usuario(emprestimos, id, livros, usuarios);
                break;
            
            }
            // Voltar
            case 0:
                printf("Voltando ao menu principal...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Main
int main() {
    criarPastaData();

    ListaLivros livros;
    ListaUsuarios usuarios;
    ListaEmprestimos emprestimos;

    inicializar_lista_livros(&livros);
    inicializar_lista_usuarios(&usuarios);
    inicializar_lista_emprestimos(&emprestimos);

    carregar_livros(&livros, "data/livros.txt");
    carregar_usuarios(&usuarios, "data/usuarios.txt");
    carregar_emprestimos(&emprestimos, "data/emprestimos.txt");

    int opcao;

    do {
        printf("\n===== SISTEMA DE BIBLIOTECA =====\n");
        printf("1 - Livros\n");
        printf("2 - Usuarios\n");
        printf("3 - Empréstimos\n");
        printf("0 - Sair\n");
        opcao = lerInteiro("Digite a opção desejada: ");

        switch (opcao) {
            case 1:
                menuLivros(&livros);
                break;
            case 2:
                menuUsuario(&usuarios, &emprestimos);
                break;
            case 3:
                menuEmprestimos(&livros, &usuarios, &emprestimos);
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    salvar_livros(&livros, "data/livros.txt");
    salvar_usuarios(&usuarios, "data/usuarios.txt");
    salvar_emprestimos(&emprestimos, "data/emprestimos.txt");

    destruir_lista_livros(&livros);
    destruir_lista_usuarios(&usuarios);
    destruir_lista_emprestimos(&emprestimos);

    return 0;
}