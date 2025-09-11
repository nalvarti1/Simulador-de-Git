# Compilador y flags de compilacion
CC = gcc

# Flags de compilacion
CFLAGS = -Iincs -Wall -g

# Archivos fuente 
SRC = src/main.c src/repository.c src/staging.c src/file.c src/commit.c

# Archivos objeto generados a partir de los archivos fuente 
OBJ = $(SRC:.c=.o)

# Ejecutable final
TARGET = ugit

# Regla principal
all: $(TARGET)

# Como generar el ejecutable a partir de los archivos objeto 
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Como generar archivos objeto a partir de archivos fuente .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos compilados y ejecutable
clean:
	rm -f $(OBJ) $(TARGET)
