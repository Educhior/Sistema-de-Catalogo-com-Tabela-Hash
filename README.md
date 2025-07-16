# Sistema de Catálogo de Filmes

Sistema de gerenciamento de filmes implementado em C++ utilizando lista ligada.

## Estrutura do Projeto

```
Sistema-de-Catalogo-com-Tabela-Hash/
├── include/
│   └── filme.h      # Arquivo de cabeçalho com estruturas e declarações
├── src/
│   ├── main.cpp     # Arquivo principal com menu e interface
│   └── filme.cpp    # Implementação das funções
├── obj/             # Diretório para arquivos objeto
├── Makefile         # Arquivo para compilação
└── README.md        # Documentação do projeto
```

## Arquivos

- **`src/main.cpp`**: Contém a função principal (`main`) e o menu interativo para o usuário.
- **`include/filme.h`**: Define as estruturas de dados (`Filme`, `Node`) e declara os protótipos das funções utilizadas no projeto.
- **`src/filme.cpp`**: Contém a implementação das funções para manipular a lista de filmes (inserir, remover, buscar, etc.).
- **`Makefile`**: Automatiza o processo de compilação, execução e limpeza do projeto

## Funcionalidades

1. **Inserir Filme**: Adiciona um novo filme ao catálogo
2. **Remover Filme por ID**: Remove um filme específico pelo ID
3. **Remover Filme por Ano**: Remove todos os filmes de um ano específico
4. **Exibir Filmes**: Lista todos os filmes organizados por ano
5. **Buscar Filme por ID**: Busca e exibe informações de um filme específico

## Compilação e Execução

### Usando o Makefile

```bash
# Compilar o projeto
make

# Compilar e executar
make run

# Limpar arquivos compilados
make clean
```

### Compilação Manual

```bash
# Compilar
g++ -Wall -Wextra -std=c++11 -Iinclude -o catalogo src/main.cpp src/filme.cpp

# Executar
./catalogo
```

## Estruturas de Dados

### Filme
```cpp
struct Filme {
    int ID;
    char Titulo[51];
    char Genero[21];
    int AnoLancamento;
};
```

### Node
```cpp
struct Node {
    Filme filme;
    Node* next;
};
```

## Funções Principais

- `inserirFilme()`: Adiciona um filme à lista
- `removerFilmeID()`: Remove filme por ID
- `removerFilmeAno()`: Remove filmes por ano
- `printFilmes()`: Exibe todos os filmes
- `buscarFilmes()`: Busca filme por ID
- `liberarLista()`: Libera memória da lista