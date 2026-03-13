CC = gcc
CFLAGS = -Wall -Iinclude
SRC = src/main.c src/lista_livros.c src/lista_usuarios.c src/lista_emprestimos.c
OUT = biblioteca

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)