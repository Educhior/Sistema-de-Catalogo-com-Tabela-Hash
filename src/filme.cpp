#include "filme.h"
#include <iostream>
#include <string.h>

using namespace std;

// Função auxiliar para verificar se um ID já existe na lista
bool idExiste(Node* head, int id) {
    Node* current = head;
    while (current != nullptr) {
        if (current->filme.ID == id) {
            return true; // ID encontrado
        }
        current = current->next;
    }
    return false; // ID não encontrado
}

Node* buildNode(Filme filme) {
    Node* newNode = new Node;
    newNode->filme = filme;
    newNode->next = nullptr;
    return newNode;
}

void inserirFilme(Node*& head, Filme novoFilme) {
    // Verifica se o ID do novo filme já existe
    if (idExiste(head, novoFilme.ID)) {
        cout << "Aviso: Ja existe um filme com o ID " << novoFilme.ID << ". Nao foi possivel adicionar." << endl;
        return;
    }

    Node* newNode = buildNode(novoFilme);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    cout << "Filme inserido com sucesso!" << endl;
}

void removerFilmeID(Node*& head, int id) {
    if (head == nullptr) {
        cout << "Lista vazia!" << endl;
        return;
    }

    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr && current->filme.ID != id) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Filme com ID " << id << " nao encontrado!" << endl;
        return;
    }

    if (previous == nullptr) {
        head = current->next; // Remove o primeiro nó
    } else {
        previous->next = current->next; // Remove o nó do meio ou final
    }

    delete current; // Libera a memória do nó removido
    cout << "Filme removido com sucesso!" << endl;
}

void removerFilmeAno(Node*& head, int ano) {
    if (head == nullptr) {
        cout << "Lista vazia!" << endl;
        return;
    }

    Node* current = head;
    Node* previous = nullptr;
    bool removido = false;

    while (current != nullptr) {
        if (current->filme.AnoLancamento == ano) {
            Node* toDelete = current;
            if (previous == nullptr) {
                head = current->next;
                current = head;
            } else {
                previous->next = current->next;
                current = current->next;
            }
            delete toDelete;
            removido = true;
            continue;
        } else {
            previous = current;
            current = current->next;
        }
    }

    if (removido) {
        cout << "Todos os filmes de " << ano << " foram removidos com sucesso!" << endl;
    } else {
        cout << "Nenhum filme de " << ano << " encontrado!" << endl;
    }
}

void printFilmes(Node* head) { //exibe as informações dos filmes
    if (head == nullptr) {
        cout << "Lista vazia!" << endl;
        return;
    }

    bool encontrouAlguma = false;
    Node* current;
    cout << endl;
    cout << "=======================================" << endl;
    cout << "        Filmes por Ano" << endl;
    cout << "=======================================" << endl;
    for (int i = 2000; i <= 2023; i++) { // Assumindo anos de 2000 a 2023
        current = head;
        bool anoHeaderImpresso = false;
        while (current != nullptr) {
            if (current->filme.AnoLancamento == i) {
                if(!anoHeaderImpresso){
                    cout << "--- Ano " << i << " ---" << endl;
                    anoHeaderImpresso = true;
                }
                encontrouAlguma = true;
                cout << "  ID: " << current->filme.ID << endl;
                cout << "  Titulo: " << current->filme.Titulo << endl;
                cout << "  Genero: " << current->filme.Genero << endl;
                cout << "  Ano de Lancamento: " << current->filme.AnoLancamento << endl;
                cout << "  -------------------------------------" << endl;
            }
            current = current->next;
        }
    }
     cout << "=======================================" << endl;
    if (!encontrouAlguma && head != nullptr) {
        cout << "Nenhum filme para exibir." << endl;
        cout << "=======================================" << endl;
    }
}

void buscarFilmes(Node* head, int ID) { //exibe as informações de um filme pelo ID
    if (head == nullptr) {
        cout << "Lista vazia!" << endl;
        return;
    }
    Node* current = head;
    bool encontrado = false; 

    while (current != nullptr) {
        if (current->filme.ID == ID) {
            cout << endl;
            cout << "=======================================" << endl;
            cout << "          Filme Encontrado" << endl;
            cout << "=======================================" << endl;
            cout << "ID: " << current->filme.ID << endl;
            cout << "Titulo: " << current->filme.Titulo << endl;
            cout << "Genero: " << current->filme.Genero << endl;
            cout << "Ano de Lancamento: " << current->filme.AnoLancamento << endl;
            cout << "=======================================" << endl;
            encontrado = true;
            break; 
        }
        current = current->next;
    }

    if (!encontrado) {
        cout << "Filme com ID " << ID << " nao encontrado!" << endl;
    }
}

void liberarLista(Node*& head) {
    Node* current = head;
    Node* nextNode = nullptr;
    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr; 
}
