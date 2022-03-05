#include <fstream>
#include <vector>
#include <set>
using namespace std;

enum Vertex_colour {
    WHITE,
    GRAY,
    BLACK
};

void dfs(vector<pair<Vertex_colour, int>> &vertexes, vector<set<int>> const &adj_list);
void dfs_visit(vector<pair<Vertex_colour, int>> &vertexes, vector<set<int>> const &adj_list, \
                int const &index);
void print_path(vector<pair<Vertex_colour, int>> const &vertexes, int const &cycle_index, \
                ofstream &fout);

bool has_cycle = 0;
int n, m, cycle_index;

int main() {
    ifstream fin("cycle.in");
    ofstream fout("cycle.out");
    fin >> n >> m;

    vector<set<int>> adj_list(n, set<int>());
    for (int i = 0; i < m; ++i) {
        int first_vertex, second_vertex;
        fin >> first_vertex >> second_vertex;
        adj_list[first_vertex - 1].insert(second_vertex - 1);
    }

    vector<pair<Vertex_colour, int>> vertexes(n);
    dfs(vertexes, adj_list);

    if (has_cycle) {
        fout << "YES\n";
        print_path(vertexes, cycle_index, fout);
    }
    else {
        fout << "NO";
    }
    
    return 0;
}


void dfs(vector<pair<Vertex_colour, int>> &vertexes, vector<set<int>> const &adj_list) {
    for (int i = 0; i < n; ++i) {
        if (vertexes[i].first == WHITE) {
            dfs_visit(vertexes, adj_list, i);
        }
        if (has_cycle) {
            return;
        }
    }
}


void dfs_visit(vector<pair<Vertex_colour, int>> &vertexes, vector<set<int>> const &adj_list, int const &index) {
    vertexes[index].first = GRAY;
    for (auto iter = adj_list[index].begin(); iter != adj_list[index].end(); ++iter) {
        if (vertexes[*iter].first == WHITE) {
            vertexes[*iter].second = index;
            dfs_visit(vertexes, adj_list, *iter);
        }
        else if (vertexes[*iter].first == GRAY) {
            vertexes[*iter].second = index;
            has_cycle = 1;
            cycle_index = index;
            return;
        }
        if (has_cycle) {
            return;
        }
    }

    vertexes[index].first = BLACK;
}


void print_path(vector<pair<Vertex_colour, int>> const &vertexes, int const &cycle_index,
ofstream &fout) {
    int curr_index = vertexes[cycle_index].second;
    vector<int> path_reversed;
    path_reversed.push_back(cycle_index + 1);
    while (curr_index != cycle_index) {
        path_reversed.push_back(curr_index + 1);
        curr_index = vertexes[curr_index].second;
    }
    for (auto iter = path_reversed.rbegin(); iter != path_reversed.rend(); ++iter) {
        fout << *iter << " ";
    }
}