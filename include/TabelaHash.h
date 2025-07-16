#ifndef HASH_TABLE_H
#define HASH_TABLE_H

// Tabela Hash
#define TABLE_SIZE 97

// Estrutura do filme
struct Filme {
    int ID;
    char Titulo[51];
    char Genero[21];
    int AnoLancamento;
};

// Estrutura do nó da lista encadeada
struct Node {
    Filme filme;
    Node* next;
};

// Estrutura da Tabela Hash
struct TabelaHash {
    Node** vetorDeListas;
    int tamanho;
    int colisoes;
};

// Funções auxiliares
TabelaHash* criarTabela();
void liberarTabela(TabelaHash* tabela);
void inserirFilme(TabelaHash* tabela, Filme novoFilme);
void removerFilme(TabelaHash* tabela, int id);
Filme* buscarFilme(TabelaHash* tabela, int id);
void listarTodos(TabelaHash* tabela);
void salvarEmArquivo(TabelaHash* tabela, const char* nomeArquivo);
void carregarDeArquivo(TabelaHash* tabela, const char* nomeArquivo);

#endif