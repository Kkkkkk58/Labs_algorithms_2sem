#include <fstream>
#include <vector>
#include <queue>
using namespace std;

enum Checking_status {
    NOT_CHECKED,
    CHECKED
};

void bfs(vector<vector<bool>> const &matrix, vector<pair<int, int>> &vertexes);


int main() {
    ifstream fin("pathbge1.in");
    ofstream fout("pathbge1.out");
    
    int n, m;
    fin >> n >> m;

    vector<vector<bool>> matrix(n, vector<bool>(n, 0));
    for (size_t i = 0; i < m; ++i) {
        int first_vertex, second_vertex;
        fin >> first_vertex >> second_vertex;
        matrix[first_vertex - 1][second_vertex - 1] = 1;
        matrix[second_vertex - 1][first_vertex - 1] = 1;
    }
    vector<pair<int, int>> vertexes(n);

    bfs(matrix, vertexes);
    for (size_t i = 0; i < n; ++i) {
        fout << vertexes[i].second << ' ';
    }

    return 0;
}


void bfs(vector<vector<bool>> const &matrix, vector<pair<int, int>> &vertexes) {
    vertexes[0].first = CHECKED;
    queue<int> vertexes_queue;
    vertexes_queue.push(0);

    while (vertexes_queue.size() != 0) {
        int check_index = vertexes_queue.front();
        vertexes_queue.pop();
        vertexes[check_index].first = CHECKED;

        for (size_t i = 0; i < matrix[0].size(); ++i) {
            if (matrix[check_index][i] == 1 && vertexes[i].first == NOT_CHECKED) {
                vertexes[i].first = CHECKED;
                vertexes[i].second = vertexes[check_index].second + 1; 
                vertexes_queue.push(i);
            }
        }

    }

}