all: dictionary

dictionary: main.o Errorhandler.o stdIO.o fileIO.o Hashtable.o 
	gcc main.o ErrorHandlers.o stdIO.o fileIO.o Hashtable.o -lm -o dictionary

main.o: main.c
	gcc -c main.c

Errorhandler.o: ErrorHandlers.h ErrorHandlers.c
	gcc -c ErrorHandlers.h ErrorHandlers.c

stdIO.o: stdIO.h stdIO.c
	gcc -c stdIO.h stdIO.c

fileIO.o: fileIO.h fileIO.c
	gcc -c fileIO.h fileIO.c

Hashtable.o: Hashtable.h Hashtable.c
	gcc -c Hashtable.h Hashtable.c

clean:
	rm -rf *.o dictionary
