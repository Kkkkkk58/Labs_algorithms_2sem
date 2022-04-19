#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const unsigned long long INF = 1e16;
long long dijkstra(vector<long long>& distances, vector<vector<int>> const& matrix, \
    size_t start, size_t finish);

size_t n;


int main() {
    ifstream fin("pathmgep.in");
    ofstream fout("pathmgep.out");
    size_t s, f;
    fin >> n >> s >> f;
    vector<vector<int>> matrix(n, vector<int>(n));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            fin >> matrix[i][j];
        }
    }

    vector<long long> distances(n, INF);
    fout << dijkstra(distances, matrix, s - 1, f - 1);
    return 0;
}


long long dijkstra(vector<long long>& distances, vector<vector<int>> const& matrix, \
    size_t start, size_t finish) {
    distances[start] = 0;
    vector<bool> used(n);

    for (size_t j = 0; j < n; ++j) {
        size_t min_index = n;
        long long min_weight = INF;

        for (size_t i = 0; i < n; ++i) {
            if (!used[i] && distances[i] < min_weight) {
                min_weight = distances[i];
                min_index = i;
            }
        }

        if (min_index == n || min_weight >= INF) {
            return -1;
        }
        if (min_index == finish) {
            return min_weight;
        }
        
        used[min_index] = true;
        for (size_t i = 0; i < n; ++i) {
            if (matrix[min_index][i] != -1 && min_weight + matrix[min_index][i] < distances[i]) {
                distances[i] = min_weight + matrix[min_index][i];
            }
        }
    }
    return -1;
}