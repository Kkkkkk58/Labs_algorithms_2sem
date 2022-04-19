#include <fstream>
#include <vector>
using namespace std;

const long long INF = static_cast<long long>(6e18 + 1);
size_t n, m;

struct Edge {
    size_t end;
    long long weight;
};


void bellman_ford(vector<vector<Edge>> const& adj_list, vector<long long> &distances, size_t start);
void mark_negative(vector<vector<Edge>> const& adj_list, vector<long long>& distances, size_t pos);


int main() {
    ifstream fin("path.in");
    ofstream fout("path.out");
    size_t s;
    fin >> n >> m >> s;
    vector<vector<Edge>> adj_list(n);

    for (size_t i = 0; i < m; ++i) {
        size_t first_vertex, second_vertex;
        long long weight;
        fin >> first_vertex >> second_vertex >> weight;
        adj_list[first_vertex - 1].push_back({ second_vertex - 1, weight });
    }

    vector<long long> distances(n, INF);
    bellman_ford(adj_list, distances, s - 1);

    for (auto distance : distances) {
        if (distance == INF) {
            fout << "*\n";
        }
        else if (distance == -INF) {
            fout << "-\n";
        }
        else {
            fout << distance << "\n";
        }
    }
    return 0;
}


void bellman_ford(vector<vector<Edge>> const& adj_list, vector<long long> &distances, size_t start) {
    distances[start] = 0;

    for (size_t i = 0; i < n - 1; ++i) {
        bool is_changing = false;
        for (size_t edge_start = 0; edge_start < n; ++edge_start) {
            for (auto const& edge : adj_list[edge_start]) {
                if (distances[edge_start] != INF && \
                    distances[edge.end] > distances[edge_start] + edge.weight) {
                    distances[edge.end] = max(-INF, distances[edge_start] + edge.weight);
                    is_changing = true;
                }
            }
        }

        if (!is_changing) {
            return;
        }
    }

    for (size_t edge_start = 0; edge_start < n; ++edge_start) {
        for (auto const& edge : adj_list[edge_start]) {
            if (distances[edge_start] != INF && \
                distances[edge.end] > distances[edge_start] + edge.weight) {
                size_t curr_elem = edge.end;
                for (auto const& cycle_element : adj_list[curr_elem]) {
                    if (distances[cycle_element.end] != -INF) {
                        mark_negative(adj_list, distances, cycle_element.end);
                    }
                }
            }
        }
    }

}


void mark_negative(vector<vector<Edge>> const& adj_list, vector<long long>& distances, size_t pos) {
    distances[pos] = -INF;
    for (auto const& edge : adj_list[pos]) {
        if (distances[edge.end] != -INF) {
            mark_negative(adj_list, distances, edge.end);
        }
    }
}