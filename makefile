a.out: client.o implementation.o
	gcc client.o implementation.o -lm
client.o: client.c
	gcc -c -Wall client.c
implementation.o: implementation.c
	gcc -c -Wall implementation.c
