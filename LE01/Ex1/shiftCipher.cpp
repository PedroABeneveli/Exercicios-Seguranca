#include <iostream>

using namespace std;

// a funcao recebe uma string composta por caracteres de letra maiuscula e espaco, o plain text
// e retorna uma string composta por letras maiusculas e espaco, o cipher text
string shift_cipher_enc(string plain_text, int k) {
    string cipher_text = "";

    for (char c : plain_text) {
        cipher_text.push_back(c == ' ' ? ' ' : 'A' + ((c-'A'+k)%26));
    }

    return cipher_text;
}

// a funcao recebe uma string composta por caracteres de letra maiuscula e espaco, o cipher text
// e retorna uma string composta por letras maiusculas e espaco, o plain text
string shift_cipher_dec(string cipher_text, int k) {
    string plain_text = "";

    for (char c : cipher_text) {
        plain_text.push_back(c == ' ' ? ' ' : 'A' + (c-'A'-k + 26)%26);
    }

    return plain_text;
}