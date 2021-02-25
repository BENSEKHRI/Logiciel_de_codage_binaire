FICHIERS = codage.o fichier.o prog.o main.o
CFLAGS = -ansi

all: $(FICHIERS)
	gcc -g $(FICHIERS) -o codage

main.o: main.c prog.h
	gcc -c $(CFLAGS) main.c -o main.o
prog.o: prog.c prog.h
	gcc -c $(CFLAGS) prog.c -o prog.o
fichier.o: fichier.c fichier.h
	gcc -c $(CFLAGS) fichier.c -o fichier.o
codage.o: codage.c codage.h
	gcc -c $(CFLAGS) codage.c -o codage.o

clean:
	rm codage $(FICHIERS)
