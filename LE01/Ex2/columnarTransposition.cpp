#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// recebe um texto composto por letras maiusculas e espacos em branco (plain text), e outra string de 26 letras maiusculas distintas, a chave
// retorna um texto composto apenas por letras maiusculas, o cipher text (espacos em branco sao ignorados)
string column_transposition_enc(string plain_text, string k) {
    string cipher_text = "";
    vector<char> letter_columns[26];
    int idx_no_space = 0;

    for (int i = 0 ; i < plain_text.size() ; i++) {
        if (plain_text[i] == ' ') continue;

        letter_columns[k[idx_no_space%k.size()]-'A'].push_back(plain_text[i]);
        idx_no_space++;
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
    int letters_per_column[26];
    int idx_text = cipher_text.size()-1, sz = cipher_text.size();

    for (int i = 0 ; i < 26 ; i++) {
        letters_per_column[k[i]-'A'] = sz/26 + (sz % 26 > i ? 1 : 0);
    }

    stack<char> letter_columns[26];
    for (int i = 25 ; i >= 0 ; i--) {
        for (int j = 0 ; j < letters_per_column[i] ; j++) {
            letter_columns[i].push(cipher_text[idx_text]);
            idx_text--;
        }
    }

    int curr_letter = 0;
    for (int i = 0 ; i < sz ; i++) {
        while (letter_columns[k[curr_letter]-'A'].empty()) curr_letter = (curr_letter + 1) % 26;

        plain_text.push_back(letter_columns[k[curr_letter]-'A'].top());
        letter_columns[k[curr_letter]-'A'].pop();
        curr_letter = (curr_letter + 1) % 26;
    }

    return plain_text;
}