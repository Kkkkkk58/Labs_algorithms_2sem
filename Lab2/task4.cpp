#include <fstream>
#include <vector>
#include <set>
using namespace std;


enum Checking_status {
    NOT_CHECKED,
    CHECKED
};

void condensation(vector<int> &vertexes, vector<set<int>> const& adj_list, \
                    vector<set<int>> const& adj_list_transposed);
vector<int> dfs_exit_times(vector<Checking_status> &vertexes, vector<set<int>> const &adj_list);
void dfs_exit_times_visit(vector<Checking_status> &vertexes, vector<set<int>> const &adj_list, \
                            int const &index, vector<int> & times_arr);
void dfs_mark_components(vector<int> &vertexes, vector<set<int>> const &adj_transposed, \
                            int const &index);

int n, m, component = 0;


int main() {
    ifstream fin("cond.in");
    ofstream fout("cond.out");
    
    fin >> n >> m;
    vector<set<int>> adj_list(n, set<int>());
    vector<set<int>> adj_list_transposed(n, set<int>());

    for (int i = 0; i < m; ++i) {
        int first_vertex, second_vertex;
        fin >> first_vertex >> second_vertex;
        adj_list[first_vertex - 1].insert(second_vertex - 1);
        adj_list_transposed[second_vertex - 1].insert(first_vertex - 1);
    }

    vector<int> vertexes(n);
    condensation(vertexes, adj_list, adj_list_transposed);

    fout << component << "\n";
    for (int const &vertex : vertexes) {
        fout << vertex << " ";
    }
    return 0;   
}


void condensation(vector<int> &vertexes, vector<set<int>> const& adj_list, \
vector<set<int>> const& adj_list_transposed) {
    vector<Checking_status> vertexes_visited(n);
    vector<int> sorted_order = dfs_exit_times(vertexes_visited, adj_list);

    for (int i = 0; i < n; ++i) {
        if (vertexes[sorted_order[i]] == 0) {
            ++component;
            dfs_mark_components(vertexes, adj_list_transposed, sorted_order[i]);
        }
    }
}


vector<int> dfs_exit_times(vector<Checking_status> &vertexes, vector<set<int>> const &adj_list) {
    vector<int> sorted_backwards;
    for (int i = 0; i < n; ++i) {
        if (vertexes[i] == NOT_CHECKED) {
            dfs_exit_times_visit(vertexes, adj_list, i, sorted_backwards);
        }
    }
    return vector<int>(sorted_backwards.rbegin(), sorted_backwards.rend());
}


void dfs_exit_times_visit(vector<Checking_status> &vertexes, vector<set<int>> const &adj_list, \
int const &index, vector<int> & times_arr) {
    vertexes[index] = CHECKED;

    for (auto iter = adj_list[index].begin(); iter != adj_list[index].end(); ++iter) {
        if (vertexes[*iter] == NOT_CHECKED) {
            dfs_exit_times_visit(vertexes, adj_list, *iter, times_arr);
        }
    }
    
    times_arr.push_back(index);
}


void dfs_mark_components(vector<int> &vertexes, vector<set<int>> const &adj_transposed, \
int const &index) {
    vertexes[index] = component;
    for (auto iter = adj_transposed[index].begin(); iter != adj_transposed[index].end(); ++iter) {
        if (vertexes[*iter] == 0) {
            dfs_mark_components(vertexes, adj_transposed, *iter);
        }
    }
}
