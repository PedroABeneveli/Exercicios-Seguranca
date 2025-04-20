#include <iostream>
#include <vector>
#include <queue>
#include "frequencia_digrafos.cpp"
#include "columnarTransposition.cpp"

using namespace std;

extern double freq_pt[26][26];

// tento ligar digrafos, e vejo as 26 chaves "mais provaveis", comecando de cada caracter
// a forma que esse algoritmo decide qual eh a prox chave mais provavel eh vendo qual letra nao utilizada possui a maior soma de frequencias
void distribuicao_frequencia(string cipher_text) {
    int tam_grupo = cipher_text.size()/26;
    double freq_para[26][26];
    
    for (int i = 0 ; i < 26 ; i++)
        for (int j = 0 ; j < 26 ; j++)
            freq_para[i][j] = 0.0;

    for (int i = 0 ; i < tam_grupo - (tam_grupo > 1 ? 1 : 0) ; i++) {
        for (int letra1 = 0 ; letra1 < 26 ; letra1++) {
            double freq_acc = 0.0;
            for (int letra2 = 0 ; letra2 < 26 ; letra2++) {
                if (letra1 == letra2) continue;

                //cout << letra1*tam_grupo << ' ' << i << " vai ler na pos " << i+letra1*tam_grupo << " a freq " << freq_pt[cipher_text[i + letra1*tam_grupo]-'A'][cipher_text[i + letra2*tam_grupo]-'A'] << endl;
                //freq_para[letra1][letra2] += freq_pt[cipher_text[i + letra1*tam_grupo]-'A'][cipher_text[i + letra2*tam_grupo]-'A'];
                //freq_acc += freq_pt[cipher_text[i + letra1*tam_grupo]-'A'][cipher_text[i + letra2*tam_grupo]-'A'];

                double aux = freq_pt[cipher_text[i + letra1*tam_grupo]-'A'][cipher_text[i + letra2*tam_grupo]-'A'];
                freq_para[letra1][letra2] += (aux >= 10 ? 5 : (aux >= 5 ? 3 : (aux < 1 ? 0 : 1)));
            }

            /*
            if (freq_acc == 0) freq_acc = 1;

            for (int letra2 = 0 ; letra2 < 26 ; letra2++) {
                if (letra1 == letra2) continue;

                freq_para[letra1][letra2] *= freq_pt[cipher_text[i + letra1*tam_grupo]-'A'][cipher_text[i + letra2*tam_grupo]-'A'] / freq_acc;
            }*/
        }
    }

    cout.precision(16);
    for (int i = 0 ; i < 26 ; i++) {
        for (int j = 0 ; j < 26 ; j++)
            cout << fixed << string(1, i+'A') << " -> " << string(1, j+'A') << " = " << freq_para[i][j] << endl; // freq_para[i][j] = 0.0;
    }

    for (int ini = 0 ; ini < 26 ; ini++) {
        vector<bool> na_chave(26, false);
        string k = "";
        int letra = ini;

        na_chave[letra] = true;
        k.push_back(letra + 'A');
        while ((int) k.size() < 26) {
            pair<double, int> maior = make_pair(-1, -1);
            for (int l = 0 ; l < 26 ; l++) {
                if (!na_chave[l])
                    maior = max(maior, make_pair(freq_para[letra][l], l));
            }

            letra = maior.second;
            na_chave[letra] = true;
            k.push_back(letra + 'A');
        }

        cout << "Chave " << k << ": " << column_transposition_dec(cipher_text, k) << "\n\n";
    }
}

int main() {
    string s;
    cin >> s;
    init_freq();
    distribuicao_frequencia(s);
}