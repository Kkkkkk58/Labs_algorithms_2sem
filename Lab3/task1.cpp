#include <fstream>
#include <vector>
using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n, m;
    fin >> n >> m;

    std::vector<int> vertices_degrees(n);
    for (int i = 0; i < m; ++i) {
        int first_vertex, second_vertex;
        fin >> first_vertex >> second_vertex;
        vertices_degrees[first_vertex - 1] += 1;
        vertices_degrees[second_vertex - 1] += 1;
    }
    
    for (int i = 0; i < n; ++i) {
        fout << vertices_degrees[i] << " ";
    }
    return 0;
}