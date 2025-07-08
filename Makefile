# Makefile para o Sistema de Catálogo de Filmes

# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -Wextra -std=c++11 -Iinclude

# Nome do executável
TARGET = catalogo

# Diretórios
SRCDIR = src
OBJDIR = obj
INCDIR = include

# Arquivos fonte
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Arquivos objeto
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

# Regra padrão
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Regra para criar arquivos objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar arquivos compilados
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Regra para executar o programa
run: all
	./$(TARGET)

# Regras phony
.PHONY: all clean run
