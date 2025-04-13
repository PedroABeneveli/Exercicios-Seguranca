#include <iostream>
#include <vector>

using namespace std;

// recebe como argumento o texto cifrado, unica informacao disponivel nesse ataque
// e retorna uma lista dos plain text possiveis, sendo que no indice i esta o plain text com a chave i
vector<string> brute_force_attack(string cipher_text) {
    vector<string> possibilities(26);

    for (int i = 0 ; i < 26 ; i++) {
        string plain_text = "";

        for (char c : cipher_text) {
            plain_text.push_back(c == ' ' ? ' ' : 'A' + (c-'A' - i + 26)%26);
        }

        possibilities[i] = plain_text;
    }

    return possibilities;
}