#include <iostream>
#include <fstream>
#include <string.h>
#include "TabelaHash.h"

using namespace std;

// Função auxiliar para calcular o índice da tabela hash
static int hashFunction(int id, int tamanho) {
    return id % tamanho;
}


static bool idExisteNaLista(Node* head, int id) {
    Node* current = head;
    while (current != nullptr) {
        if (current->filme.ID == id) {
            return true; // ID encontrado
        }
        current = current->next;
    }
    return false; // ID não encontrado
}

static void liberarLista(Node*& head) {
    Node* current = head;
    Node* nextNode = nullptr;
    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}


TabelaHash* criarTabela() {
    TabelaHash* tabela = new TabelaHash;
    tabela->tamanho = TABLE_SIZE;
    tabela->colisoes = 0;

    // Aloca memória para o vetor de listas
    tabela->vetorDeListas = new Node*[TABLE_SIZE];

    for (int i = 0; i < TABLE_SIZE; i++) {
        tabela->vetorDeListas[i] = nullptr;
    }

    cout << "Tabela Hash criada com sucesso!" << endl;
    return tabela;
}

void liberarTabela(TabelaHash* tabela) {
    if (tabela == nullptr) return;

    for (int i = 0; i < tabela->tamanho; i++) {
        liberarLista(tabela->vetorDeListas[i]);
    }

    delete[] tabela->vetorDeListas;
    delete tabela;
    cout << "Tabela Hash liberada da memoria." << endl;
}

void inserirFilme(TabelaHash* tabela, Filme novoFilme) {
    if (tabela == nullptr) return;

    int indice = hashFunction(novoFilme.ID, tabela->tamanho);

    // Verifica se o ID já existe na lista encadeada do índice
    if (idExisteNaLista(tabela->vetorDeListas[indice], novoFilme.ID)) {
        cout << "ERRO: O ID " << novoFilme.ID << " ja existe. Insercao cancelada." << endl;
        return;
    }
    
    // Se já existe um filme nesse índice, incrementa o contador de colisões
    if (tabela->vetorDeListas[indice] != nullptr) {
        tabela->colisoes++;
    }

    // Cria o novo nó para o filme
    Node* newNode = new Node;
    newNode->filme = novoFilme;

    newNode->next = tabela->vetorDeListas[indice];
    tabela->vetorDeListas[indice] = newNode;
}

void removerFilme(TabelaHash* tabela, int id) {
    if (tabela == nullptr) return;

    int indice = hashFunction(id, tabela->tamanho);
    Node* head = tabela->vetorDeListas[indice];
    Node* current = head;
    Node* previous = nullptr;

    // Procura pelo nó com o ID correspondente
    while (current != nullptr && current->filme.ID != id) {
        previous = current;
        current = current->next;
    }

    // Se não encontrou o filme
    if (current == nullptr) {
        cout << "Filme com ID " << id << " nao encontrado para remocao." << endl;
        return;
    }

    // Se o nó a ser removido é o primeiro da lista
    if (previous == nullptr) {
        tabela->vetorDeListas[indice] = current->next;
    } else { // Se está no meio ou no fim
        previous->next = current->next;
    }

    delete current; // Libera a memória do nó
    cout << "Filme com ID " << id << " removido com sucesso." << endl;
}

Filme* buscarFilme(TabelaHash* tabela, int id) {
    if (tabela == nullptr) return nullptr;

    int indice = hashFunction(id, tabela->tamanho);
    Node* current = tabela->vetorDeListas[indice];

    // Percorre a lista no índice calculado
    while (current != nullptr) {
        if (current->filme.ID == id) {
            return &current->filme; // Retorna o endereço do filme encontrado
        }
        current = current->next;
    }

    return nullptr; // Retorna nulo se não encontrar
}

void listarTodos(TabelaHash* tabela) {
    if (tabela == nullptr) return;

    cout << "=======================================" << endl;
    std::cout << " LISTA DE TODOS OS FILMES NO CATALOGO " << endl;
    cout << "=======================================" << endl;
    for (int i = 0; i < tabela->tamanho; i++) {
        Node* current = tabela->vetorDeListas[i];
        if (current != nullptr) {
            cout << "\nIndice [" << i << "]:\n";
            cout << "----------------------------------------------------------------\n";
            while (current != nullptr) {
                cout << " | ID: " << current->filme.ID
                     << " | Titulo: " << current->filme.Titulo
                     << " | Genero: " << current->filme.Genero
                     << " | Ano: " << current->filme.AnoLancamento << endl;
                current = current->next;
            }
        }
    }
    cout << "=======================================" << endl;
    cout << "Total de colisoes na tabela: " << tabela->colisoes << std::endl;
}

void salvarEmArquivo(TabelaHash* tabela, const char* nomeArquivo) {
    if (tabela == nullptr) return;

    ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo '" << nomeArquivo << "' para escrita." << endl;
        return;
    }

    for (int i = 0; i < tabela->tamanho; i++) {
        Node* current = tabela->vetorDeListas[i];
        while (current != nullptr) {
            arquivo << current->filme.ID << "\t"
                    << current->filme.Titulo << "\t"
                    << current->filme.Genero << "\t"
                    << current->filme.AnoLancamento << "\n";
            current = current->next;
        }
    }

    arquivo.close();
    cout << "Catalogo salvo em '" << nomeArquivo << "' com sucesso." << endl;
}

void carregarDeArquivo(TabelaHash* tabela, const char* nomeArquivo) {
    if (tabela == nullptr) return;

    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cout << "Arquivo '" << nomeArquivo << "' nao encontrado. Nenhum filme carregado." << endl;
        return;
    }
    
    Filme filmeTemp;
    while (arquivo >> filmeTemp.ID) {
        arquivo.get(); // Consumir o caractere de tabulação
        arquivo.getline(filmeTemp.Titulo, 51, '\t');
        arquivo.getline(filmeTemp.Genero, 21, '\t');
        arquivo >> filmeTemp.AnoLancamento;

        inserirFilme(tabela, filmeTemp);
    }

    arquivo.close();
    cout << "Filmes carregados de '" << nomeArquivo << "' com sucesso." << endl;
}