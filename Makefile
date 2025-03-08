########################################################
CC=gcc
CFLAGS= -g -Wall -ansi -pedantic
EJS = p2_e1a
########################################################
OBJECTSP2E1A = p2_e1a.o utils.o 
########################################################

all: $(EJS) clear

p2_e1a: $(OBJECTSP2E1A)
	$(CC) $(CFLAGS) -o p2_e1a $(OBJECTSP2E1A) -L. -lstack

p2_e1a.o: p2_e1a.c utils.h stack.h types.h
	$(CC) $(CFLAGS) -c p2_e1a.c

utils.o: utils.c utils.h stack.h types.h
	$(CC) $(CFLAGS) -c utils.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p2_e1a"
	./p2_e1a

runv:
	@echo ">>>>>>Running p2_e1a with valgrind"
	valgrind --leak-check=full ./p2_e1a