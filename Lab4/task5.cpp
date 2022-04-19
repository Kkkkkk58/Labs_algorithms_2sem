//#include <fstream>
//#include <vector>
//#include <iostream>
//using namespace std;
//constexpr unsigned int INF = static_cast<unsigned int>(1e9 + 1);
//size_t n;
//
//struct Edge {
//    size_t begin, end;
//    int weight;
//};
//
//vector<size_t> bellman_ford(vector<Edge> const& edges, vector<int>& distances, size_t start);
//
//
//int main() {
//    ifstream fin("negcycle.in");
//    ofstream fout("negcycle.out");
//
//    fin >> n;
//    vector<Edge> edges;
//
//    for (size_t i = 0; i < n; ++i) {
//        for (size_t j = 0; j < n; ++j) {
//            int value;
//            fin >> value;
//            if (i == j && value < 0) {
//                fout << "YES\n" << 2 << "\n" << i + 1 << " " << j + 1;
//                return 0;
//            }
//            if (value != 1e9) {
//                edges.push_back({ i, j, value });
//            }
//        }
//    }
//
//    vector<int> distances(n, INF);
//    vector<size_t> cycle = bellman_ford(edges, distances, 0);
//
//    if (cycle.empty()) {
//        fout << "NO";
//    }
//    else {
//        fout << "YES\n" << cycle.size() << "\n";
//        for (auto it = cycle.rbegin(); it != cycle.rend(); ++it) {
//            fout << *it << " ";
//        }
//    }
//    return 0;
//}
//
//
//vector<size_t> bellman_ford(vector<Edge> const& edges, vector<int>& distances, size_t start) {
//    distances[start] = 0;
//    vector<size_t> predecessors(n, -INF);
//
//    for (size_t i = 0; i < n - 1; ++i) {
//        bool is_changing = false;
//
//        for (auto const& edge : edges) {
//            if (distances[edge.end] > distances[edge.begin] + edge.weight) {
//                distances[edge.end] = distances[edge.begin] + edge.weight;
//                predecessors[edge.end] = edge.begin;
//                is_changing = true;
//            }
//        }
//        if (!is_changing) {
//            return vector<size_t>();
//        }
//    }
//
//    for (auto const& edge : edges) {
//        if (distances[edge.end] > distances[edge.begin] + edge.weight) {
//            vector<size_t> cycle;
//            int curr_elem = edge.end;
//            for (size_t i = 0; i < n; ++i) {
//                curr_elem = predecessors[curr_elem];
//            }
//            for (size_t i = curr_elem; i != curr_elem || cycle.empty(); i = predecessors[i]) {
//                cycle.push_back(i + 1);
//            }
//            cycle.push_back(curr_elem + 1);
//            return cycle;
//        }
//    }
//
//    return vector<size_t>();
//
//}
