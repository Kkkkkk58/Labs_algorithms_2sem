#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
long long int total_weight;


class DSU {
public:
    DSU(vector<int> const& represent)  
        : represent_(represent), size_(vector<int>(n, 1)) {}
    int find_set(int key) {
        if (key == represent_[key]) {
            return key;
        }
        represent_[key] = find_set(represent_[key]);
        return represent_[key];
    }
    void unite(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (size_[a] < size_[b]) {
                swap(a, b);
            }
            represent_[b] = a;
            size_[a] += size_[b];
        }
    }
private:
    vector<int> represent_;
    vector<int> size_;
};


struct Edge {
    int begin, end, weight;
};
bool operator<(Edge const& lhs, Edge const& rhs) {
    return lhs.weight < rhs.weight;
}
void kruskal_mst(vector<Edge>& edges, vector<int>& vertexes);

int main() {
    std::ifstream fin("spantree3.in");
    std::ofstream fout("spantree3.out");
    
    fin >> n >> m;
    vector<Edge> edges(m);
    vector<int> vertexes(n);
    for (int i = 0; i < m; ++i) {
        int first_vertex, second_vertex, weight;
        fin >> first_vertex >> second_vertex >> weight;
        edges[i] = { first_vertex - 1, second_vertex - 1, weight };
        if (i < n) {
            vertexes[i] = i;
        }
    }
    if (m < n) {
        for (int i = m; i < n; ++i) {
            vertexes[i] = i;
        }
    }
    kruskal_mst(edges, vertexes);
    fout << total_weight;
    return 0;
}


void kruskal_mst(vector<Edge> &edges, vector<int> &vertexes) {
    DSU dsu(vertexes);
    sort(edges.begin(), edges.end());
    int edges_count = 0;
    for (auto const& edge : edges) {
        if (dsu.find_set(edge.begin) != dsu.find_set(edge.end)) {
            dsu.unite(edge.begin, edge.end);
            total_weight += edge.weight;
            ++edges_count;
        }
        if (edges_count == n - 1) {
            break;
        }
    }
}