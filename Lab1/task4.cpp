#include <fstream>
#include <vector>
#include <set>

int component_number;
void dfs(std::vector<std::pair<int, int>> &vertexes, std::vector<std::set<int>> const &adj_list);
void dfs_visit(std::vector<std::pair<int, int>> &vertexes,\
               std::vector<std::set<int>> const &adj_list, int index);

enum Checking_status {
    NOT_CHECKED,
    CHECKED
};


int main() {
    std::ifstream fin("components.in");
    std::ofstream fout("components.out");
    int n, m;
    fin >> n >> m;

    std::vector<std::set<int>> adj_list(n, std::set<int>());
    for (size_t i = 0; i < m; ++i) {
        int first_vertex, second_vertex;
        fin >> first_vertex >> second_vertex;
        adj_list[first_vertex - 1].insert(second_vertex - 1);
        adj_list[second_vertex - 1].insert(first_vertex - 1);
    }

    std::vector<std::pair<int, int>> vertexes(n);
    dfs(vertexes, adj_list);
    fout << component_number << '\n'; 
    for (size_t i = 0; i < n; ++i) {
        fout << vertexes[i].second << ' ';
    }

    return 0;
}


void dfs(std::vector<std::pair<int, int>> &vertexes, std::vector<std::set<int>> const &adj_list) {

    for (size_t i = 0; i < vertexes.size(); ++i) {
        if (vertexes[i].first == NOT_CHECKED) {
            ++component_number;
            dfs_visit(vertexes, adj_list, i);
        }
    }

}


void dfs_visit(std::vector<std::pair<int, int>> &vertexes,\
               std::vector<std::set<int>> const &adj_list, int index) {

    vertexes[index].first = CHECKED;
    vertexes[index].second = component_number;
    for (std::set<int>::iterator adj = adj_list[index].begin();
         adj != adj_list[index].end(); ++adj) {

        if (vertexes[*adj].first == NOT_CHECKED) {
            dfs_visit(vertexes, adj_list, *adj);
        }

    }

}