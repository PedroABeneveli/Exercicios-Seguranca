#ifndef BRUTE_FORCE
#define BRUTE_FORCE

#include "imports.h"
#include "columnarTransposition.cpp"

using namespace std;

// recebe como argumento o texto cifrado, unica informacao disponivel nesse ataque
// e vai imprimindo um possivel plain text e a chave utilizada por aquele plain text apos retorno do usuario, afirmando se aquele texto realmente eh o plain text
// se o usuario digita "Y" (sem as aspas), o plain text esta correto ; caso contrario sera considerado como errado
// retorna o par (plain_text, key) que o usuario concordou
pair<string, string> brute_force(string cipher_text) {
    string poss_key = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string plain_text, user_ans;

    do {
        plain_text = column_transposition_dec(cipher_text, poss_key);

        cout << "Chave " << poss_key << ": "<< plain_text << '\n';
        cout << "Esta correto? (Digite Y se sim)\n";
        cin >> user_ans;
        if (user_ans == "Y")
            return make_pair(plain_text, poss_key);

    } while (next_permutation(poss_key.begin(), poss_key.end()));

    return {"Chave nao encontrada", ";-;"};
}

#endif