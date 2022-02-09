#include <fstream>
#include <vector>
#include <set>
using namespace std;

int component_number;
void dfs(vector<pair<int, int>> &vertexes, vector<set<int>> const &adj_list);
void dfs_visit(vector<pair<int, int>> &vertexes,\
               vector<set<int>> const &adj_list, int index);

enum Checking_status {
    NOT_CHECKED,
    CHECKED
};


int main() {
    ifstream fin("components.in");
    ofstream fout("components.out");
    int n, m;
    fin >> n >> m;

    vector<set<int>> adj_list(n, set<int>());
    for (size_t i = 0; i < m; ++i) {
        int first_vertex, second_vertex;
        fin >> first_vertex >> second_vertex;
        adj_list[first_vertex - 1].insert(second_vertex - 1);
        adj_list[second_vertex - 1].insert(first_vertex - 1);
    }

    vector<pair<int, int>> vertexes(n);
    dfs(vertexes, adj_list);
    fout << component_number << '\n'; 
    for (size_t i = 0; i < n; ++i) {
        fout << vertexes[i].second << ' ';
    }

    return 0;
}


void dfs(vector<pair<int, int>> &vertexes, vector<set<int>> const &adj_list) {

    for (size_t i = 0; i < vertexes.size(); ++i) {
        if (vertexes[i].first == NOT_CHECKED) {
            ++component_number;
            dfs_visit(vertexes, adj_list, i);
        }
    }

}


void dfs_visit(vector<pair<int, int>> &vertexes,\
               vector<set<int>> const &adj_list, int index) {

    vertexes[index].first = CHECKED;
    vertexes[index].second = component_number;
    for (set<int>::iterator adj = adj_list[index].begin();
         adj != adj_list[index].end(); ++adj) {

        if (vertexes[*adj].first == NOT_CHECKED) {
            dfs_visit(vertexes, adj_list, *adj);
        }

    }

}