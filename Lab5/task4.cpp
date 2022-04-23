#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

int knight_paths_count(int i, int j, vector<vector<int>> &paths);
int n, m;

int main() {
    ifstream fin("knight2.in");
    ofstream fout("knight2.out");

    fin >> n >> m;
    vector<vector<int>> paths(n, vector<int>(m, -1));
    
    paths[0][0] = 1;
    fout << knight_paths_count(n - 1, m - 1, paths) << "\n";
    return 0;
}


int knight_paths_count(int i, int j, vector<vector<int>> &paths) {
    if (i < 0 || j < 0 || i >= n || j >= m) {
        return 0;
    }
    else if (paths[i][j] == -1) {
        paths[i][j] = knight_paths_count(i - 2, j - 1, paths) + knight_paths_count(i - 1, j - 2, paths)\
        + knight_paths_count(i + 1, j - 2, paths) + knight_paths_count(i - 2, j + 1, paths);
    } 
    return paths[i][j];
}


