#include <fstream>
#include <vector>
#include <set>
using namespace std;

enum Colours {
    TRANSPARENT, 
    RED,
    BLUE
};

void dfs(vector<Colours> &vertexes, vector<set<int>> const &adj_list);
void dfs_visit(vector<Colours> &vertexes, vector<set<int>> const &adj_list, \
                int const &index);

int n, m;
bool is_bipartite = true;

int main() {
    ifstream fin("bipartite.in");
    ofstream fout("bipartite.out");
    
    fin >> n >> m;
    vector<set<int>> adj_list(n, set<int>());

    for (int i = 0; i < m; ++i) {
        int first_vertex, second_vertex;
        fin >> first_vertex >> second_vertex;
        if (first_vertex == second_vertex) {
            fout << "NO";
            return 0;
        }
        adj_list[first_vertex - 1].insert(second_vertex - 1);
        adj_list[second_vertex - 1].insert(first_vertex - 1);
    }

    vector<Colours> vertexes(n, TRANSPARENT);
    dfs(vertexes, adj_list);

    if (is_bipartite) {
        fout << "YES";
    }
    else {
        fout << "NO";
    }
    return 0;
}


void dfs(vector<Colours> &vertexes, vector<set<int>> const &adj_list) {
    for (int i = 0; i < n; ++i) {
        if (vertexes[i] == TRANSPARENT) {
            vertexes[i] = RED;
            dfs_visit(vertexes, adj_list, i);
            if (!is_bipartite) {
                return;
            }
        }
    }
}


void dfs_visit(vector<Colours> &vertexes, vector<set<int>> const &adj_list, \
int const &index) {
    for (auto iter = adj_list[index].begin(); iter != adj_list[index].end(); ++iter) {
        if (vertexes[*iter] == TRANSPARENT) {
            if (vertexes[index] == RED) {
                vertexes[*iter] = BLUE;
            }
            else {
                vertexes[*iter] = RED;
            }
            dfs_visit(vertexes, adj_list, *iter);
        }

        else if (vertexes[*iter] == vertexes[index]) {
            is_bipartite = false;
            return;
        }

        if (!is_bipartite) {
            return;
        }
    }
}