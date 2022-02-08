#include <fstream>
#include <vector>

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    
    int n, m;
    fin >> n >> m;
    std::vector<std::vector<bool>> matrix(n, std::vector<bool>(n, 0));

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

