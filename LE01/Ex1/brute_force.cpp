#ifndef BRUTE_FORCE
#define BRUTE_FORCE

#include "imports.h"
#include "shiftCipher.cpp"

using namespace std;

// recebe como argumento o texto cifrado, unica informacao disponivel nesse ataque
// e retorna uma lista dos plain text possiveis, sendo que no indice i esta o plain text com a chave i
vector<string> brute_force_attack(string cipher_text) {
    vector<string> possibilities(26);

    for (int i = 0 ; i < 26 ; i++) {
        possibilities[i] = shift_cipher_dec(cipher_text, i);
    }

    return possibilities;
}

#endif