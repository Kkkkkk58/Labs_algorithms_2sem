#include <fstream>
#include <vector>
#include <set>
using namespace std;

enum Checking_status {
    NOT_CHECKED,
    CHECKED
};

vector<int> topological_sort(vector<set<int>> const &adj_list);
void dfs(vector<Checking_status> &visited_vertexes, vector<set<int>> const &adj_list, \
            vector<int> &ordered_backwards, int const &index);

int n, m;

int main() {
    ifstream fin("hamiltonian.in");
    ofstream fout("hamiltonian.out");
    
    fin >> n >> m;
    vector<set<int>> adj_list(n, set<int>());
    for (int i = 0; i < m; ++i) {
        int first_vertex, second_vertex;
        fin >> first_vertex >> second_vertex;
        adj_list[first_vertex - 1].insert(second_vertex - 1);
    }

    vector<int> ordered_vertexes = topological_sort(adj_list);

    bool contains_hamiltonian_path = true;
    int curr_vertex = ordered_vertexes[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        int prev_vertex = ordered_vertexes[i];
        if (adj_list[prev_vertex].find(curr_vertex) == adj_list[prev_vertex].end()) {
            contains_hamiltonian_path = false;
            break;
        }
        curr_vertex = prev_vertex;
    }

    if (contains_hamiltonian_path) {
        fout << "YES";
    }
    else {
        fout << "NO";
    }

    return 0;
}


vector<int> topological_sort(vector<set<int>> const &adj_list) {
    vector<Checking_status> visited_vertexes(n);
    vector<int> ordered_backwards;
    for (int i = 0; i < n; ++i) {
        if (visited_vertexes[i] == NOT_CHECKED) {
            dfs(visited_vertexes, adj_list, ordered_backwards, i);
        } 
    }
    return vector<int>(ordered_backwards.rbegin(), ordered_backwards.rend());
}


void dfs(vector<Checking_status> &visited_vertexes, vector<set<int>> const &adj_list, \
vector<int> &ordered_backwards, int const &index) {
    visited_vertexes[index] = CHECKED;
    for (auto iter = adj_list[index].begin(); iter != adj_list[index].end(); ++iter) {
        if (visited_vertexes[*iter] == NOT_CHECKED) {
            dfs(visited_vertexes, adj_list, ordered_backwards, *iter);
        }
    }
    ordered_backwards.push_back(index);
}