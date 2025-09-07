# Compilador
CC = gcc

# Flags de compilación
CFLAGS = -Iincs -Wall -g

# Archivos fuente
SRC = src/main.c src/repository.c src/staging.c src/file.c src/commit.c

# Archivos objeto
OBJ = $(SRC:.c=.o)

# Ejecutable final
TARGET = ugit

# Regla principal
all: $(TARGET)

# Cómo generar el ejecutable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Cómo generar archivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos compilados
clean:
	rm -f $(OBJ) $(TARGET)
