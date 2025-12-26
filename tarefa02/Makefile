
CFLAGS = -std=c99 -Wall -Werror -Wvla -g 
LDFLAGS = -lm                            

.PHONY: all clean

all: drama cpf auau

clean:
	rm -f xou swift primos


drama: drama.c
	gcc $(CFLAGS) drama.c -o drama $(LDFLAGS)

cpf: cpf.c
	gcc $(CFLAGS) cpf.c -o cpf $(LDFLAGS)

auau: auau.c
	gcc $(CFLAGS) auau.c -o auau $(LDFLAGS)
