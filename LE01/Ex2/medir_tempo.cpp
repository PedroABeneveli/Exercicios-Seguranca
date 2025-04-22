#include <iostream>
#include <chrono>
#include "brute_force.cpp"
#include "distribuicao_frequencia.cpp"

using namespace std;

// recebe a chave tambem para que ele pare automaticamente
pair<string, string> brute_force_mod(string cipher_text, string k) {
    string poss_key = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string plain_text, user_ans;

    do {
        plain_text = column_transposition_dec(cipher_text, poss_key);

        if (poss_key == k)
            return make_pair(plain_text, poss_key);

    } while (next_permutation(poss_key.begin(), poss_key.end()));

    return {"Chave nao encontrada", ";-;"};
}

int main() {
    string cipher;

    getline(cin, cipher);

    auto t1 = chrono::high_resolution_clock::now();
    brute_force_mod(cipher, "ABCDEFGHIJKLMNOPQRSTYUZVXW");
    auto t2 = chrono::high_resolution_clock::now();

    auto ms_brute = chrono::duration_cast<chrono::milliseconds>(t2 - t1);

    t1 = chrono::high_resolution_clock::now();
    distribuicao_frequencia(cipher);
    t2 = chrono::high_resolution_clock::now();

    auto ms_freq = chrono::duration_cast<chrono::milliseconds>(t2 - t1);

    cout << "Tempo em milissegundos do brute force: " << ms_brute.count() << " ms\n";
    cout << "Tempo em milissegundos da analise de frequencia: " << ms_freq.count() << " ms\n";
}