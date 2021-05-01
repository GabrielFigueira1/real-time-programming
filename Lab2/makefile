# Nome arquivo pos compilacao
PRJ=$(shell basename $(CURDIR))

# Compilador
CC=gcc 

# Lista com os arquivos .c
SRC=$(wildcard ./src/*.c)

# Lista com os arquivos .h
INCLUDE=$(wildcard ./include/*.h)

# Arquivos object
OBJ=$(subst .c,.o,$(subst src,objects,$(SRC)))

# Compilar todos os arquivos .c e .h
all: $(PRJ)

$(PRJ): $(OBJ)
	$(CC) $^ -o $@

./objects/%.o: ./src/%.c ./include/%.h
	$(CC) -c -Wall -Iinclude $< -o $@
	
./objects/main.o: ./src/main.c $(INCLUDE)
	$(CC) -c -Wall -Iinclude $< -o $@

# Remover arquivos .o
clean:
	rm  ./objects/*.o $(PRJ)
