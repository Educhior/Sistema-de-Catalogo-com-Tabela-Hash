#ifndef FILME_H
#define FILME_H

struct Filme {
    int ID;
    char Titulo[51];
    char Genero[21];
    int AnoLancamento;
};

struct Node {
    Filme filme;
    Node* next;
};

// Declarações das funções
bool idExiste(Node* head, int id);
Node* buildNode(Filme filme);
void inserirFilme(Node*& head, Filme novoFilme);
void removerFilmeID(Node*& head, int id);
void removerFilmeAno(Node*& head, int ano);
void printFilmes(Node* head);
void buscarFilmes(Node* head, int ID);
void liberarLista(Node*& head);

#endif
