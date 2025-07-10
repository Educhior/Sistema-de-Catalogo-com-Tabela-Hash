#include <iostream>
#include <limits>
#include <string.h>
#include "TabelaHash.h"

#include <cstdlib>

using namespace std;

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void exibirMenu() {
    cout << "\n=======================================" << endl;
    cout << "      CATALOGO DE FILMES " << endl;
    cout << "=======================================" << endl;
    cout << "1. Inserir Filme" << endl;
    cout << "2. Buscar Filme por ID" << endl;
    cout << "3. Remover Filme por ID" << endl;
    cout << "4. Editar Filme por ID" << endl;
    cout << "5. Listar Todos os Filmes" << endl;
    cout << "6. Salvar Catalogo em Arquivo" << endl;
    cout << "7. Carregar Catalogo de Arquivo" << endl;
    cout << "0. Sair" << endl;
    cout << "=======================================" << endl;
    cout << "Escolha uma opcao: ";
}

int main() {
    TabelaHash* catalogo = criarTabela();
    int proximoID = 1;
    int opcao = -1;

    do {
        limparTela();
        
        exibirMenu();

        // Bloco de validação de entrada numérica
        while (!(cin >> opcao)) {
            cout << "Entrada invalida. Por favor, digite um numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcao) {
            case 1: { // Inserir Filme
                limparTela();
                Filme novoFilme;
                novoFilme.ID = proximoID;

                cout << "Digite o titulo do filme (max 50 caracteres): ";
                cin.getline(novoFilme.Titulo, 51);

                cout << "Digite o genero do filme (max 20 caracteres): ";
                cin.getline(novoFilme.Genero, 21);

                cout << "Digite o ano de lancamento: ";
                cin >> novoFilme.AnoLancamento;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                inserirFilme(catalogo, novoFilme);
                cout << "Filme cadastrado com ID " << proximoID << "." << endl;
                proximoID++; 

                cout << "\nPressione Enter para voltar ao menu...";
                cin.get();

                break;
            }
            case 2: { // Buscar Filme por ID
                limparTela();
                int id;
                cout << "Digite o ID do filme a ser buscado: ";
                cin >> id;

                Filme* filmeEncontrado = buscarFilme(catalogo, id);

                if (filmeEncontrado != nullptr) {
                    cout << "\n--- Filme Encontrado ---\n";
                    cout << "ID: " << filmeEncontrado->ID << endl;
                    cout << "Titulo: " << filmeEncontrado->Titulo << endl;
                    cout << "Genero: " << filmeEncontrado->Genero << endl;
                    cout << "Ano: " << filmeEncontrado->AnoLancamento << endl;
                } else {
                    cout << "Filme com ID " << id << " nao encontrado." << endl;
                }

                cout << "\nPressione Enter para voltar ao menu...";
                cin.get();

                break;
            }
            case 3: { // Remover Filme por ID
                limparTela();
                int id;
                cout << "Digite o ID do filme a ser removido: ";
                cin >> id;
                removerFilme(catalogo, id);
                break;
            }
            case 4: { // Editar um campo (que não seja a ID)
                limparTela();
                int id;
                cout << "Digite o ID do filme a ser editado: ";
                cin >> id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                Filme* filmeParaEditar = buscarFilme(catalogo, id);
                if (filmeParaEditar != nullptr) {
                    cout << "Editando o filme: '" << filmeParaEditar->Titulo << "'.\n";
                    cout << "Digite o novo titulo (max 50 caracteres): ";
                    cin.getline(filmeParaEditar->Titulo, 51);
                    cout << "Digite o novo genero (max 20 caracteres): ";
                    cin.getline(filmeParaEditar->Genero, 21);
                    cout << "Filme atualizado com sucesso!\n";
                } else {
                    cout << "Filme com ID " << id << " nao encontrado." << endl;
                }
                break;
            }
            case 5: { // Listar Todos os Filmes
                limparTela();
                listarTodos(catalogo);

                cout << "\nPressione Enter para voltar ao menu...";
                cin.get();
                break;
            }
            case 6: { // Salvar em Arquivo
                limparTela();
                salvarEmArquivo(catalogo, "filmes.txt");

                cout << "\nPressione Enter para voltar ao menu...";
                cin.get();
                break;
            }
            case 7: { // Carregar de Arquivo
                limparTela();
                liberarTabela(catalogo);
                catalogo = criarTabela();
                proximoID = 1;
                carregarDeArquivo(catalogo, "filmes.txt");
                cout << "Catalogo carregado com sucesso!" << endl;

                cout << "\nPressione Enter para voltar ao menu...";
                cin.get();
                break;
            }
            case 0: { // Sair
                cout << "Encerrando o programa..." << endl;
                liberarTabela(catalogo);
                break;
            }
            default: {
                limparTela();
                cout << "Opcao invalida! Tente novamente." << endl;
                cout << "\nPressione Enter para voltar ao menu...";
                cin.get();
                break;
            }
        }
    } while (opcao != 0);

    return 0;
}