#include <fstream>
#include <vector>
using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    
    int n, m;
    fin >> n >> m;
    vector<vector<bool>> matrix(n, vector<bool>(n, 0));
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