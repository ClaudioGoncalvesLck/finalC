all: TP02

TP02: main.o funcoes.o
	gcc -g -o TP02 main.o funcoes.o

main.o: main.c header.h
	gcc -g -o main.o main.c -c -w -Wall -ansi -pedantic

funcoes.o: funcoes.c header.h
	gcc -g -o funcoes.o funcoes.c -c -w -Wall -ansi -pedantic -std=c99

clean:
	del /Q /S *.o *~ TP02