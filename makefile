all: progRGPD

progRGPD: main.o var.o
	gcc -o progRGPD main.o var.o 

main.o: Main.c 
	gcc -g -o main.o main.c -c

var.o: var.c
	gcc -o var.o var.c -c
	
clean:
	rm main.o var.o progRGPD.exe

run:
	mingw32-make all
	./progRGPD

