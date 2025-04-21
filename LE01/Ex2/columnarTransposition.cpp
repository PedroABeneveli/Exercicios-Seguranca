#ifndef COLUMN_TRANSP
#define COLUMN_TRANSP

#include "imports.h"

using namespace std;

// recebe um texto composto por letras maiusculas e espacos em branco (plain text), e outra string de 26 letras maiusculas distintas, a chave
// retorna um texto composto apenas por letras maiusculas, o cipher text (espacos em branco sao ignorados)
string column_transposition_enc(string plain_text, string k) {
    mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
    string cipher_text = "", sem_espaco = "";
    vector<char> letter_columns[26];

    for (int i = 0 ; i < (int) plain_text.size() ; i++) {
        if (plain_text[i] == ' ') continue;

        sem_espaco.push_back(plain_text[i]);
    }

    // padding adicionando caracteres pseudo-aleatorios
    while (((int) sem_espaco.size()) % 26 != 0) {
        int letra = uniform_int_distribution<int>(0, 25)(rng);

        sem_espaco.push_back(letra + 'A');
    }

    for (int i = 0 ; i < (int) sem_espaco.size() ; i++) {
        letter_columns[k[i%k.size()]-'A'].push_back(sem_espaco[i]);
    }

    for (int i = 0 ; i < 26 ; i++) {
        for (char c : letter_columns[i])
            cipher_text.push_back(c);
    }

    return cipher_text;
}

// recebe um texto composto por letras maiusculas, o cipher text, e uma string de 26 letras maiusculas distintas, a chave
// retorna um texto composto por letras maiusculas, o plain text (sem espacos em branco)
string column_transposition_dec(string cipher_text, string k) {
    string plain_text = "";
    int group_size = cipher_text.size() / k.size();
    int idx_text = cipher_text.size()-1;

    stack<char> letter_columns[26];
    for (int i = 25 ; i >= 0 ; i--) {
        for (int j = 0 ; j < group_size ; j++) {
            letter_columns[i].push(cipher_text[idx_text]);
            idx_text--;
        }
    }

    int curr_letter = 0;
    for (int i = 0 ; i < (int) cipher_text.size() ; i++) {
        while (letter_columns[k[curr_letter]-'A'].empty()) curr_letter = (curr_letter + 1) % k.size();

        plain_text.push_back(letter_columns[k[curr_letter]-'A'].top());
        letter_columns[k[curr_letter]-'A'].pop();
        curr_letter = (curr_letter + 1) % k.size();
    }

    return plain_text;
}

#endif