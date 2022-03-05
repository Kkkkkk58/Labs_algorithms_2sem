#include <fstream>
#include <vector>
#include <stack>
#include <set>
using namespace std;
 
enum Vertex_colour {
    WHITE,
    GRAY,
    BLACK
};

void topological_print(vector<Vertex_colour> &vertexes, vector<set<int>> const &adj_list, \
                        ofstream &output); 
stack<int> dfs(vector<Vertex_colour> &vertexes, vector<set<int>> const &adj_list);
void dfs_visit(vector<Vertex_colour> &vertexes, vector<set<int>> const &adj_list, \
                int const &index, stack<int> &sorted_vertexes); 
 
bool has_cycle = 0;
int n, m;
 
int main() {
    ifstream fin("topsort.in");
    ofstream fout("topsort.out");
    fin >> n >> m;
    vector<set<int>> adj_list(n, set<int>());
 
    for (int i = 0; i < m; ++i) {
        int first_vertex, second_vertex;
        fin >> first_vertex >> second_vertex;
        adj_list[first_vertex - 1].insert(second_vertex - 1);
    }
     
    vector<Vertex_colour> vertexes(n);
    topological_print(vertexes, adj_list, fout);
    return 0;
}
 
 
void topological_print(vector<Vertex_colour> &vertexes, vector<set<int>> const &adj_list, \
ofstream &output) {
    stack<int> sorted_vertexes = dfs(vertexes, adj_list);
    if (has_cycle) {
        output << -1;
    }
    else {
        while (!sorted_vertexes.empty()) {
            output << sorted_vertexes.top() + 1 << " ";
            sorted_vertexes.pop();
        } 
    }
}
 
stack<int> dfs(vector<Vertex_colour> &vertexes, vector<set<int>> const &adj_list) {
    stack<int> sorted_vertexes;
    for (int i = 0; i < n; ++i) {
        if (vertexes[i] == WHITE) {
            dfs_visit(vertexes, adj_list, i, sorted_vertexes);
            if (has_cycle) {
                return stack<int>();
            }
        }
    }
    return sorted_vertexes;
}
 
void dfs_visit(vector<Vertex_colour> &vertexes, vector<set<int>> const &adj_list, \
int const &index, stack<int> &sorted_vertexes) {
    vertexes[index] = GRAY;
    for (auto iter = adj_list[index].begin(); iter != adj_list[index].end(); ++iter) {
        if (vertexes[*iter] == WHITE) {
            dfs_visit(vertexes, adj_list, *iter, sorted_vertexes);
        }
        else if (vertexes[*iter] == GRAY) {
            has_cycle = 1;
            return;
        }
        if (has_cycle) {
            return;
        }
    } 
    vertexes[index] = BLACK;
    sorted_vertexes.push(index);
}