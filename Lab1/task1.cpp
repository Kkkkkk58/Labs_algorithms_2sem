#include <fstream>
#include <vector>
using namespace std;


int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    
    int n, m;
    fin >> n >> m;
    vector<vector<bool>> matrix(n, vector<bool>(n, 0));

    for (size_t i = 0; i < m; ++i) {
        int first_vertex, second_vertex;
        fin >> first_vertex >> second_vertex;
        matrix[first_vertex - 1][second_vertex - 1] = 1;
    }

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            fout << matrix[i][j] << ' ';
        }
        fout << '\n';
    }

    return 0;
}

