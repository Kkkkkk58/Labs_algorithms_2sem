#include <fstream>
#include <vector>
#include <limits>
using namespace std;

void floyd_warshall(vector<vector<size_t>> &matrix);
size_t n, m;
const size_t INF = 1e7;


int main() {
    ifstream fin("pathsg.in");
    ofstream fout("pathsg.out");
    fin >> n >> m;

    vector<vector<size_t>> matrix(n, vector<size_t>(n, INF));
    for (size_t i = 0; i < m; ++i) {
        size_t first_vertex, second_vertex, weight;
        fin >> first_vertex >> second_vertex >> weight;
        matrix[first_vertex - 1][second_vertex - 1] = weight; 
    }
    for (size_t i = 0; i < n; ++i) {
        matrix[i][i] = 0;
    }
    
    floyd_warshall(matrix);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            fout << matrix[i][j] << " ";
        }
        fout << "\n";
    }
    return 0;
}


void floyd_warshall(vector<vector<size_t>> &matrix) {
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            for (size_t k = 0; k < n; ++k) {
                matrix[j][k] = min(matrix[j][k], matrix[j][i] + matrix[i][k]);
            }
        }
    }
}