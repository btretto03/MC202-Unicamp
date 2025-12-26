# Variáveis usadas para compilar os programas.
CFLAGS = -std=c99 -Wall -Werror -Wvla -g # flags de compilação
LDFLAGS = -lm                            # flags de linkagem

# Marca essas duas receitas como alvos especiais, que
# não precisam existir como arquivos.
.PHONY: all clean

# `make all` compila todos os programas.
all: xou swift primos

# `make clean` remove os arquivos gerados pela compilação.
clean:
	rm -f xou swift primos

# As regras de compilação para cada programa.
# A sintaxe `$(VAR)` substitui o valor da variável VAR no comando.
xou: xou.c
	gcc $(CFLAGS) xou.c -o xou $(LDFLAGS)

swift: swift.c
	gcc $(CFLAGS) swift.c -o swift $(LDFLAGS)

primos: primos.c
	gcc $(CFLAGS) primos.c -o primos $(LDFLAGS)