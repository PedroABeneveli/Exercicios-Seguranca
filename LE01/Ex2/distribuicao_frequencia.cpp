#ifndef DISTR_FREQ
#define DISTR_FREQ

#include "imports.h"
#include "frequencia_digrafos.cpp"
#include "columnarTransposition.cpp"

using namespace std;

extern double freq_pt[26][26];

bool all_true(vector<bool> &list) {
    for (int i = 0 ; i < (int) list.size() ; i++) {
        if (!list[i])
            return false;
    }

    return true;
}

// tento ligar digrafos, e vejo as 26 chaves "mais provaveis", comecando de cada caracter
// a forma que esse algoritmo decide qual eh a prox chave mais provavel eh sempre pegando a maior soma de frequencias entre caracteres
// assim montando um caso especifico de grafo funcional
vector<pair<string, string>> distribuicao_frequencia(string cipher_text) {
    int tam_grupo = cipher_text.size()/26;
    double freq_para[26][26];
    
    for (int i = 0 ; i < 26 ; i++)
        for (int j = 0 ; j < 26 ; j++)
            freq_para[i][j] = 0.0;

    for (int i = 0 ; i < tam_grupo - (tam_grupo > 1 ? 1 : 0) ; i++) {
        for (int letra1 = 0 ; letra1 < 26 ; letra1++) {
            for (int letra2 = 0 ; letra2 < 26 ; letra2++) {
                if (letra1 == letra2) continue;

                freq_para[letra1][letra2] += freq_pt[cipher_text[i + letra1*tam_grupo]-'A'][cipher_text[i + letra2*tam_grupo]-'A'];
            }
        }
    }

    vector<bool> recebe(26, false), sai(26, false);
    vector<int> to(26, -1);
    while (!all_true(recebe)) {
        tuple<double, int, int> maior = {-1, -1, -1};      // a maior frequencia (de alguem para outro caracter que nao recebe)

        for (int letra1 = 0 ; letra1 < 26 ; letra1++) {
            if (sai[letra1]) continue;
            
            for (int letra2 = 0 ; letra2 < 26 ; letra2++) {
                if (letra1 == letra2 || recebe[letra2]) continue;

                maior = max(maior, make_tuple(freq_para[letra1][letra2], letra1, letra2));
            }
        }

        // ligamos os caracteres com maior frequencia que conseguimos
        to[get<1>(maior)] = get<2>(maior);
        sai[get<1>(maior)] = true;
        recebe[get<2>(maior)] = true;
    }

    vector<pair<string, string>> possiveis;
    for (int ini = 0 ; ini < 26 ; ini++) {
        string k = "";

        k.push_back('A' + ini);

        int letra = ini, falta = 25;
        vector<bool> na_chave(26, false);
        na_chave[ini] = true;

        while (falta > 0) {
            if (na_chave[to[letra]]) {
                pair<double, int> maior = {-1, -1};
                for (int letra2 = 0 ; letra2 < 26 ; letra2++) {
                    if (na_chave[letra2]) continue;

                    maior = max(maior, make_pair(freq_para[letra][letra2], letra2));
                }

                letra = maior.second;
            } else {
                letra = to[letra];
            }

            na_chave[letra] = true;
            k.push_back('A' + letra);
            falta--;
        }

        possiveis.push_back(make_pair(k, column_transposition_dec(cipher_text, k)));
    }

    return possiveis;
}

#endif