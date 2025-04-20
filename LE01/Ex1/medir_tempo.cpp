#include <iostream>
#include <chrono>
#include "brute_force.cpp"
#include "distribuicao_frequencia.cpp"

using namespace std;

int main() {
    string cipher;

    getline(cin, cipher);

    auto t1 = chrono::high_resolution_clock::now();
    brute_force_attack(cipher);
    auto t2 = chrono::high_resolution_clock::now();

    auto ms_brute = chrono::duration_cast<chrono::milliseconds>(t2 - t1);

    t1 = chrono::high_resolution_clock::now();
    distribuicao_frequencia(cipher);
    t2 = chrono::high_resolution_clock::now();

    auto ms_freq = chrono::duration_cast<chrono::milliseconds>(t2 - t1);

    cout << "Tempo em milissegundos do brute force: " << ms_brute.count() << " ms\n";
    cout << "Tempo em milissegundos da analise de frequencia: " << ms_freq.count() << " ms\n";
}
