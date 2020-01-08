all: prog

prog: main.o auditorias.o colaboradores.o menu.o vulnerabilidades.o savearray.o
	gcc -g -o prog main.o auditorias.o colaboradores.o menu.o vulnerabilidades.o savearray.o

main.o: main.c header.h
	gcc -g -o main.o main.c -c

auditorias.o: auditorias.c header.h
	gcc -g -o auditorias.o auditorias.c -c

colaboradores.o: colaboradores.c header.h
	gcc -g -o colaboradores.o colaboradores.c -c

menu.o: menu.c header.h
	gcc -g -o menu.o menu.c -c

vulnerabilidades.o: vulnerabilidades.c header.h
	gcc -g -o vulnerabilidades.o vulnerabilidades.c -c

savearray.o: savearray.c header.h
	gcc -g -o savearray.o savearray.c -c

clean:
	del /Q /S *.o *~ prog

run:
	mingw32-make clean
	mingw32-make all
	./prog

