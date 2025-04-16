#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// alfabeto ordenado pela frequencia de cada letra na lingua portuguesa
vector<char> mais_freq_pt = {'A', 'E', 'O', 'S', 'R', 'I', 'D', 'C', 'N', 'T', 'M', 'U', 'P', 'L', 'V', 'G', 'F', 'B', 'Q', 'H', 'Z', 'J', 'X', 'K', 'Y', 'W'};

string shift_cipher_dec(string cipher_text, int k) {
    string plain_text = "";

    for (char c : cipher_text) {
        plain_text.push_back(c == ' ' ? ' ' : 'A' + (c-'A'-k + 26)%26);
    }

    return plain_text;
}

// ideia:
//  - primeiro contamos a frequencia das letras no texto cifrado
//  - depois comparamos a frequencia das letras individuais e tentamos ligar as mais frequentes do texto com as mais frequentes da tabela
//  - por fim, vemos qual as 5 chaves mais provaveis e retornamos um vetor delas, com o plaintext correspondente
vector<pair<int, string>> distribuicao_frequencia(string cipher_text) {
    vector<int> freq(26, 0);

    for (int i = 0 ; i < (int) cipher_text.size() ; i++) {
        freq[cipher_text[i] - 'A']++;
    }

    vector<pair<int, char>> freq_ordenada;
    for (int i = 0 ; i < 26 ; i++) {
        if (freq[i] != 0)
            freq_ordenada.push_back({freq[i], 'A'+i});
    }

    sort(freq_ordenada.begin(), freq_ordenada.end(), greater<pair<int, int>>());

    vector<int> possibilidades(26, 0);
    for (int i = 0 ; i < (int) freq_ordenada.size() ; i++) {
        if (i-1 >= 0)
            possibilidades[(freq_ordenada[i].second - mais_freq_pt[i-1] + 26) % 26]++;

        possibilidades[(freq_ordenada[i].second - mais_freq_pt[i] + 26) % 26]++;

        if (i+1 < 26)
            possibilidades[(freq_ordenada[i].second - mais_freq_pt[i+1] + 26) % 26]++;
    }

    vector<pair<int, int>> maior_poss;
    for (int k = 0 ; k < 26 ; k++) {
        if (possibilidades[k] != 0)
            maior_poss.push_back({possibilidades[k], k});
    }

    sort(maior_poss.begin(), maior_poss.end(), greater<pair<int, int>>());

    vector<pair<int, string>> result;
    for (int i = 0 ; i < min(5, (int) maior_poss.size()) ; i++) {
        result.push_back({maior_poss[i].second, shift_cipher_dec(cipher_text, maior_poss[i].second)});
    }

    return result;
}

int main() {
    string s;
    cin >> s;

    auto x = distribuicao_frequencia(s);
    for (auto p : x) {
        cout << p.first << ": " << p.second << '\n';
    }
}