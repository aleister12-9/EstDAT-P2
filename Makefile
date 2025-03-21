########################################################
CC=gcc
CFLAGS= -g -Wall -ansi -pedantic
EJS = p2_e1a p2_e1b p2_e2 p2_e1a_bis p2_e1b_bis p2_e2_bis
########################################################
OBJECTSP2E1A_BIS = p2_e1a.o utils.o file_utils.o vertex.o graph.o stack.o
OBJECTSP2E1B_BIS = p2_e1b.o utils.o file_utils.o vertex.o graph.o stack.o
OBJECTSP2E2_BIS = p2_e2.o utils.o vertex.o file_utils.o graph.o stack.o

OBJECTSP2E1A = p2_e1a.o utils.o file_utils.o vertex.o graph.o
OBJECTSP2E1B = p2_e1b.o utils.o file_utils.o vertex.o graph.o
OBJECTSP2E2 = p2_e2.o utils.o vertex.o file_utils.o graph.o
########################################################

all: $(EJS) clear

# Ejecutables
p2_e1a: $(OBJECTSP2E1A)
	$(CC) $(CFLAGS) -o p2_e1a $(OBJECTSP2E1A) -L. -lstack

p2_e1b: $(OBJECTSP2E1B)
	$(CC) $(CFLAGS) -o p2_e1b $(OBJECTSP2E1B) -L. -lstack

p2_e2: $(OBJECTSP2E2)
	$(CC) $(CFLAGS) -o p2_e2 $(OBJECTSP2E2) -L. -lstack

p2_e1a_bis: $(OBJECTSP2E1A_BIS)
	$(CC) $(CFLAGS) -o p2_e1a_bis $(OBJECTSP2E1A_BIS)

p2_e1b_bis: $(OBJECTSP2E1B_BIS)
	$(CC) $(CFLAGS) -o p2_e1b_bis $(OBJECTSP2E1B_BIS)

p2_e2_bis: $(OBJECTSP2E2_BIS)
	$(CC) $(CFLAGS) -o p2_e2_bis $(OBJECTSP2E2_BIS)

# Reglas
p2_e2.o: p2_e2.c utils.h stack.h types.h vertex.h file_utils.h graph.h
	$(CC) $(CFLAGS) -c p2_e2.c

p2_e1b.o: p2_e1b.c utils.h stack.h types.h vertex.h
	$(CC) $(CFLAGS) -c p2_e1b.c

p2_e1a.o: p2_e1a.c utils.h stack.h types.h vertex.h
	$(CC) $(CFLAGS) -c p2_e1a.c

utils.o: utils.c utils.h stack.h types.h
	$(CC) $(CFLAGS) -c utils.c

file_utils.o: file_utils.c file_utils.h types.h
	$(CC) $(CFLAGS) -c file_utils.c

vertex.o: vertex.c vertex.h types.h
	$(CC) $(CFLAGS) -c vertex.c

graph.o: graph.c graph.h vertex.h types.h
	$(CC) $(CFLAGS) -c graph.c

stack.o: stack.c stack.h types.h
	$(CC) $(CFLAGS) -c stack.c

# Reglas de limpieza
clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

# Reglas para ejecutar los programas
run_e1a:
	@echo ">>>>>>Running p2_e1a"
	./p2_e1a grades1.txt grades2.txt

run_e1b:
	@echo ">>>>>>Running p2_e1b"
	./p2_e1b cities1.txt cities2.txt

run_e2:
	@echo ">>>>>> Running p2_e2 with g2.txt"
	./p2_e2 g2.txt 100 700

run_e1a_bis:
	@echo ">>>>>>Running p2_e1a_bis"
	./p2_e1a_bis grades1.txt grades2.txt

run_e1b_bis:
	@echo ">>>>>>Running p2_e1b_bis"
	./p2_e1b_bis cities1.txt cities2.txt

run_e2_bis:
	@echo ">>>>>> Running p2_e2_bis with g2.txt"
	./p2_e2_bis g2.txt 100 700

runv_e1a:
	@echo ">>>>>>Running p2_e1a with valgrind"
	valgrind --leak-check=full ./p2_e1a grades1.txt grades2.txt

runv_e1b:
	@echo ">>>>>>Running p2_e1b with valgrind"
	valgrind --leak-check=full ./p2_e1b cities1.txt cities2.txt

runv_e2:
	@echo ">>>>>>Running p2_e2 with valgrind"
	valgrind --leak-check=full ./p2_e2 g2.txt 100 700

runv_e1a_bis:
	@echo ">>>>>>Running p2_e1a_bis with valgrind"
	valgrind --leak-check=full ./p2_e1a_bis grades1.txt grades2.txt

runv_e1b_bis:
	@echo ">>>>>>Running p2_e1b_bis with valgrind"
	valgrind --leak-check=full ./p2_e1b_bis cities1.txt cities2.txt

runv_e2_bis:
	@echo ">>>>>>Running p2_e2_bis with valgrind"
	valgrind --leak-check=full ./p2_e2_bis g2.txt 100 700