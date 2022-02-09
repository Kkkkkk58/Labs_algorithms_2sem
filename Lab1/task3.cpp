#include <fstream>
#include <vector>


int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    
    int n, m;
    fin >> n >> m;
    std::vector<std::vector<bool>> matrix(n, std::vector<bool>(n, 0));
    bool contains_multi_edges = false;
    for (size_t i = 0; i < m; ++i) {
        int first_vertex, second_vertex;
        fin >> first_vertex >> second_vertex;
        if (matrix[second_vertex - 1][first_vertex - 1] == 1 ||
        matrix[first_vertex - 1][second_vertex - 1] == 1) {
            contains_multi_edges = true;
            break;
        }
        matrix[first_vertex - 1][second_vertex - 1] = 1;
    }

    if (contains_multi_edges) {
        fout << "YES";
    }
    else {
        fout << "NO";
    }

    return 0; 
}