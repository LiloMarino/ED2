# Nome do projeto
PROJETO = ted

# Lista de arquivos fontes
FONTES = main.c grafos.c dotgrafos.c Bibliotecas/learquivo.c Bibliotecas/geradores.c Bibliotecas/utilities.c Bibliotecas/listadupla.c

# Lista de arquivos de cabeçalho correspondentes aos arquivos fontes
HEADERS = $(filter-out main.h, $(FONTES:.c=.h))

# Nome do arquivo zip
ZIP_FILE = muriloa.zip

# Pasta de saída
OUTPUT = output/
LOGS = logs/

# Cria a pasta de saída se ela não existir
$(shell mkdir -p $(OUTPUT) $(OUTPUT)Bibliotecas)
$(shell mkdir -p $(LOGS))

# Arquivos objeto na pasta de saída
OBJETOS = $(addprefix $(OUTPUT), $(FONTES:.c=.o))

# Compilador e opções de compilação
CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -fstack-protector-all -Werror=implicit-function-declaration -g

# Regra padrão
all: $(OUTPUT)$(PROJETO)

# Regra para compilar o projeto
$(OUTPUT)$(PROJETO): $(OBJETOS)
	$(CC) $(OBJETOS) -o $@ -lm

# Regra para criar os arquivos objeto
$(OUTPUT)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP

# Inclui as dependências dos arquivos objeto
-include $(OBJETOS:.o=.d)

# Regra para limpar os arquivos objeto e o executável
clean:
	rm -rf $(OUTPUT) $(PROJETO)
	rm -rf $(LOGS)

# Regra para executar o programa
run: all
	cd $(OUTPUT) && ./$(PROJETO)

# Regra para executar o programa com o Valgrind
valgrind: all
	cd $(OUTPUT) && valgrind --leak-check=full --show-leak-kinds=all ./$(PROJETO)

# Comando para criar o arquivo zip
zip: $(FONTES) $(HEADERS)
	zip $(ZIP_FILE) $(FONTES) $(HEADERS) makefile

finish: all valgrind zip clean