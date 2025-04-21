#ifndef KEY_GEN
#define KEY_GEN

#include "imports.h"

using namespace std;

// geracao de uma chave pseudo-randomica para a transposicao de colunas implementada
string key_generator() {
    mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
    string key = "";
    priority_queue<pair<int, int>> queue;

    for (int letter = 0 ; letter < 26 ; letter++) {
        int priority = uniform_int_distribution<int>(1, 2e9)(rng);

        queue.push({priority, letter});
    }

    while (!queue.empty()) {
        key.push_back(queue.top().second + 'A');
        queue.pop();
    }

    return key;
}

#endif