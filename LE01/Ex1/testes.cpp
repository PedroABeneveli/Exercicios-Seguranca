#include "imports.h"
#include "shiftCipher.cpp"
#include "distribuicao_frequencia.cpp"
#include "brute_force.cpp"

using namespace std;

int main() {
    cout << "Digite:\n";
    cout << "1 para realizar uma encriptacao\n";
    cout << "2 para realizar uma decriptacao\n";
    cout << "3 para realizar uma quebra por forca bruta\n";
    cout << "4 para realizar uma quebra por analise de frequencia\n";

    int op, k;;
    string texto;
    cin >> op;

    if (op == 1) {
        cout << "Qual sera a chave utilizada? ";
        cin >> k;
        getline(cin, texto);    // para descartar o \n no final da linha
        cout << "Escreva o texto a ser encriptado na proxima linha:\n";
        getline(cin, texto);
        cout << "Texto cifrado:\n";
        cout << shift_cipher_enc(texto, k) << '\n';
    } else if (op == 2) {
        cout << "Qual sera a chave utilizada? ";
        cin >> k;
        getline(cin, texto);    // para descartar o \n no final da linha
        cout << "Escreva o texto a ser decriptado na proxima linha:\n";
        getline(cin, texto);
        cout << "Texto em claro:\n";
        cout << shift_cipher_dec(texto, k) << '\n';
    } else if (op == 3) {
        cout << "Digite o texto cifrado a ser quebrado na linha abaixo:\n";
        getline(cin, texto); // para descartar o \n no final da linha
        getline(cin, texto); 

        cout << '\n';
        vector<string> possiveis = brute_force_attack(texto);
        for (int k = 0 ; k < 26 ; k++) {
            cout << "Texto em claro com a chave " << k << ": " << possiveis[k] << '\n';
        }
    } else if (op == 4) {
        cout << "Digite o texto cifrado a ser quebrado na linha abaixo:\n";
        getline(cin, texto); // para descartar o \n no final da linha
        getline(cin, texto); 

        cout << '\n';
        vector<pair<int, string>> possiveis = distribuicao_frequencia(texto);
        for (pair<int, string> p : possiveis) {
            cout << "Texto em claro com a chave " << p.first << ": " << p.second << '\n';
        }
    } else {
        cout << "Operacao invalida\n";
    }

    return 0;
}