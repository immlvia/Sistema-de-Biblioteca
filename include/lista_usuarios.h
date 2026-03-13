#ifndef LISTA_USUARIOS_H
#define LISTA_USUARIOS_H

typedef struct Usuario {

    int id;
    char nome[100];

} Usuario;

typedef struct NoUsuario {

    Usuario usuario;
    struct NoUsuario* proximo;

} NoUsuario;

typedef struct ListaUsuarios {

    NoUsuario* cabeca;
    int tamanho;
    
} ListaUsuarios;

void inicializar_lista_usuarios(ListaUsuarios* lista);
void inserir_usuario(ListaUsuarios* lista, Usuario usuario);
int remover_usuario(ListaUsuarios* lista, int id);
Usuario* buscar_usuario_por_id(ListaUsuarios* lista, int id);
Usuario* buscar_usuario_por_nome(ListaUsuarios* lista, const char* nome);
void listar_usuarios(ListaUsuarios* lista);
void destruir_lista_usuarios(ListaUsuarios* lista);
void salvar_usuarios(ListaUsuarios* lista, const char* arquivo);
void carregar_usuarios(ListaUsuarios* lista, const char* arquivo);

#endif 