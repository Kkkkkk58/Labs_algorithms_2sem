#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

size_t max_gold_weight(size_t capacity, vector<size_t> const& weights);

size_t n;
int main() {
    ifstream fin("knapsack.in");
    ofstream fout("knapsack.out");
    
    size_t s;
    fin >> s >> n;
    vector<size_t> bars_weights(n);
    for (size_t i = 0; i < n; ++i) {
        fin >> bars_weights[i];
    }
    fout << max_gold_weight(s, bars_weights);
    return 0;
}



size_t max_gold_weight(size_t capacity, vector<size_t> const& weights) {
    vector<vector<size_t>> max_weights(n + 1, vector<size_t>(capacity + 1));

    for (size_t i = 1; i < n + 1; ++i) {
        for (size_t j = 1; j < capacity + 1; ++j) {
            if (j >= weights[i - 1]) {
                max_weights[i][j] = max(max_weights[i - 1][j], \
                max_weights[i - 1][j - weights[i - 1]] + weights[i - 1]);
            }
            else {
                max_weights[i][j] = max_weights[i - 1][j];
            }
        }
    }
    // for (size_t i = 0; i < n + 1; ++i) {
    //     for (size_t j = 0; j < capacity; ++j) {
    //         cout << max_weights[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    return max_weights[n][capacity];
}