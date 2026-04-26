CC = gcc

TARGET = distribuido_semaforo

SRC_DIR = src
INC_DIR = headers
OBJ_DIR = obj

#flags de compilação
CFLAGS = -I$(INC_DIR) -Wall -Wextra

#flags de linkedição, incluindo as bibliotecas necessárias para o projeto
LDFLAGS = -lpthread -lpigpio -lrt

# obtendo a lista de arquivos fonte
SRC = $(wildcard $(SRC_DIR)/*.c)

# gerando a lista de arquivos objeto a partir dos arquivos fonte
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# regra padrão para compilar o projeto
all: $(OBJ_DIR) $(TARGET)

$TARGET: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run: all
	sudo ./$(TARGET)

.PHONY: all clean run