#include "include/filme.h"
#include <iostream>
#include <limits>
#include <string.h>

using namespace std;

int main() {
    Node* listaFilmes = nullptr;
    int opcao;

    do {
        cout << endl;
        cout << "=======================================" << endl;
        cout << "            Menu de Filmes" << endl;
        cout << "=======================================" << endl;
        cout << "1. Inserir Filme" << endl;
        cout << "2. Remover Filme por ID" << endl;
        cout << "3. Remover Filme por Ano" << endl;
        cout << "4. Exibir Filmes (Por ano)" << endl;
        cout << "5. Buscar Filme por ID" << endl;
        cout << "0. Sair" << endl;
        cout << "=======================================" << endl;
        cout << "Escolha uma opcao: ";

        while (!(cin >> opcao)) { 
            cout << "Entrada invalida. Por favor, digite um numero: ";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpar o buffer após ler a opção

        switch (opcao) {
            case 1: {
                Filme novoFilme;
                cout << "Digite o ID do filme: ";
                while (!(cin >> novoFilme.ID)) {
                    cout << "ID invalido. Por favor, digite um numero inteiro: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Digite o titulo do filme (max 50 caracteres): ";
                cin.getline(novoFilme.Titulo, 51);
                if (strlen(novoFilme.Titulo) == 0) {
                    cout << "Titulo nao pode ser vazio. Filme nao inserido." << endl;
                    break;
                }

                cout << "Digite o genero do filme (max 20 caracteres): ";
                cin.getline(novoFilme.Genero, 21);
                if (strlen(novoFilme.Genero) == 0) {
                    cout << "Genero nao pode ser vazio. Filme nao inserido." << endl;
                    break;
                }

                cout << "Digite o ano de lancamento do filme: ";
                while (!(cin >> novoFilme.AnoLancamento)) {
                    cout << "Ano invalido. Por favor, digite um numero inteiro: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                inserirFilme(listaFilmes, novoFilme);
                break;
            }
            case 2: {
                int id;
                if (listaFilmes == nullptr) {
                    cout << "Lista vazia! Nao ha filmes para remover." << endl;
                    break;
                }
                cout << "Digite o ID do filme a ser removido: ";
                while (!(cin >> id)) {
                    cout << "ID invalido. Por favor, digite um numero inteiro: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                removerFilmeID(listaFilmes, id);
                break;
            }
            case 3: {
                int ano;
                if (listaFilmes == nullptr) {
                    cout << "Lista vazia! Nao ha filmes para remover." << endl;
                    break;
                }
                cout << "Digite o ano do filme a ser removido: ";
                while (!(cin >> ano)) {
                    cout << "Ano invalido. Por favor, digite um numero inteiro: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                removerFilmeAno(listaFilmes, ano);
                break;
            }
            case 4:
                printFilmes(listaFilmes);
                break;
            case 5: {
                int id;
                if (listaFilmes == nullptr) {
                    cout << "Lista vazia! Nao ha filmes para buscar." << endl;
                    break;
                }
                cout << "Digite o ID do filme a ser buscado: ";
                while (!(cin >> id)) {
                    cout << "ID invalido. Por favor, digite um numero inteiro: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                buscarFilmes(listaFilmes, id);
                break;
            }
            case 0:
                cout << "Saindo..." << endl;
                liberarLista(listaFilmes);
                cout << "Memoria liberada. Programa encerrado." << endl;
                break;
            default:
                cout << "Opcao invalida! Tente novamente." << endl;
        }
    } while (opcao != 0);

    return 0; 
}