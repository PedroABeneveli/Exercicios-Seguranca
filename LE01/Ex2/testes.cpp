#include "imports.h"
#include "columnarTransposition.cpp"
#include "keyGenerator.cpp"
#include "brute_force.cpp"
#include "distribuicao_frequencia.cpp"

using namespace std;

int main() {
    cout << "Digite:\n";
    cout << "1 para realizar uma encriptacao\n";
    cout << "2 para realizar uma decriptacao\n";
    cout << "3 para gerar uma chave aleatoriamente\n";
    cout << "4 para realizar uma quebra por forca bruta\n";
    cout << "5 para realizar uma quebra por analise de frequencia\n";

    int op;
    string texto, k;
    cin >> op;

    if (op == 1) {
        cout << "Qual sera a chave utilizada? ";
        cin >> k;
        getline(cin, texto);    // para descartar o \n no final da linha
        cout << "Escreva o texto a ser encriptado na proxima linha:\n";
        getline(cin, texto);
        cout << "Texto cifrado:\n";
        cout << column_transposition_enc(texto, k) << '\n';
    } else if (op == 2) {
        cout << "Qual sera a chave utilizada? ";
        cin >> k;
        getline(cin, texto);    // para descartar o \n no final da linha
        cout << "Escreva o texto a ser decriptado na proxima linha:\n";
        getline(cin, texto);
        cout << "Texto em claro:\n";
        cout << column_transposition_dec(texto, k) << '\n';
    } else if (op == 3) {
        cout << "Chave: " << key_generator() << '\n';
    } else if (op == 4) {
        cout << "Digite o texto cifrado a ser quebrado na linha abaixo:\n";
        getline(cin, texto); // para descartar o \n no final da linha
        getline(cin, texto); 

        cout << '\n';
        pair<string, string> chave = brute_force(texto);
        cout << "Chave: " << chave.second << '\n';
        cout << "Texto em claro:\n" << chave.first << '\n';
    } else if (op == 5) {
        init_freq();
        cout << "Digite o texto cifrado a ser quebrado na linha abaixo:\n";
        getline(cin, texto); // para descartar o \n no final da linha
        getline(cin, texto); 

        cout << '\n';
        vector<pair<string, string>> possiveis = distribuicao_frequencia(texto);
        for (pair<string, string> p : possiveis) {
            cout << "Texto em claro com a chave " << p.first << ": " << p.second << "\n\n";
        }
    } else {
        cout << "Operacao invalida\n";
    }

    return 0;
}