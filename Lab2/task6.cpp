#include <fstream>
#include <vector>
using namespace std;

enum Vertex_status {
    LOSING = -1,
    UNDEFINED,
    WINNING
};

void dfs(vector<Vertex_status> &vertexes, vector<vector<int>> const &adj_list, int const &index);

int main() {
    ifstream fin("game.in");
    ofstream fout("game.out");

    int n, m, s;
    fin >> n >> m >> s;
    vector<vector<int>> adj_list(n, vector<int>());
    vector<Vertex_status> vertexes(n, LOSING);

    for (int i = 0; i < m; ++i) {
        int first_vertex, second_vertex;
        fin >> first_vertex >> second_vertex;
        adj_list[first_vertex - 1].push_back(second_vertex - 1);

        if (vertexes[first_vertex - 1] == LOSING) {
            vertexes[first_vertex - 1] = UNDEFINED;
        }

    }

    dfs(vertexes, adj_list, s - 1);

    if (vertexes[s - 1] == WINNING) {
        fout << "First player wins";
    }
    else {
        fout << "Second player wins";
    }
    return 0;
}


void dfs(vector<Vertex_status> &vertexes, vector<vector<int>> const &adj_list, int const &index) {
    for (auto iter = adj_list[index].begin(); iter != adj_list[index].end(); ++iter) {
        if (vertexes[*iter] == UNDEFINED) {
            dfs(vertexes, adj_list, *iter);
        }
        
        if (vertexes[*iter] == LOSING) {
            vertexes[index] = WINNING;
            break;
        }
        else {
            vertexes[index] = LOSING;
        }
    }
}