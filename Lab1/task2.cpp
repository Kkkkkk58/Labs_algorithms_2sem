#include <fstream>
#include <vector>
using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    
    int n;
    fin >> n;
    vector<vector<bool>> matrix(n, vector<bool>(n));
    bool is_correct = true;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0 ; j < n; ++j) {
            bool connection;
            fin >> connection;
            if (i == j && connection) {
                is_correct = false;
                break;
            }
            matrix[i][j] = connection;
        }
    }

    if (is_correct) {
        for (size_t i = 0; i < n - 1; ++i) {
            for (size_t j = i + 1; j < n; ++j) {
                if (matrix[i][j] != matrix[j][i]) {
                    is_correct = false;
                    break;
                }
            }
        }
    }

    if (is_correct) {
        fout << "YES";
    }
    else {
        fout << "NO";
    }

    return 0;
}