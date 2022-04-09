//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <set>
//#include <algorithm>
//using namespace std;
//
//int n, m;
//
////class DSU {
////public:
////    DSU(vector<int> const& represent)
////        : represent_(represent), size_(vector<int>(n, 1)) {}
////    int find_set(int key) {
////        if (key == represent_[key]) {
////            return key;
////        }
////        represent_[key] = find_set(represent_[key]);
////        return represent_[key];
////    }
////    void unite(int a, int b) {
////        a = find_set(a);
////        b = find_set(b);
////        if (a != b) {
////            if (size_[a] < size_[b]) {
////                swap(a, b);
////            }
////            represent_[b] = a;
////            size_[a] += size_[b];
////        }
////    }
////private:
////    vector<int> represent_;
////    vector<int> size_;
////};
//
//enum Checking_status {
//    NOT_CHECKED,
//    CHECKED
//};
//
//struct Edge {
//    long long begin, end, weight;
//};
//bool operator<(Edge const& lhs, Edge const& rhs) {
//    return lhs.weight < rhs.weight;
//}
//
//long long int total_weight = 0;
//long long chinese_mst(vector<vector<Edge>>& reversed_adj_list, vector<vector<Edge>>& adj_list, int num, int root);
//void dfs(vector<bool>& vertexes, vector<vector<Edge>> const& edges, int index);
//int main() {
//	ifstream fin("chinese.in");
//	ofstream fout("chinese.out");
//    
//    fin >> n >> m;
//    vector<vector<Edge>> adj_list(n);
//    vector<vector<Edge>> reversed_adj_list(n);
//    for (int i = 0; i < m; ++i) {
//        int first_vertex, second_vertex, weight;
//        fin >> first_vertex >> second_vertex >> weight;
//        adj_list[first_vertex - 1].push_back({ first_vertex - 1, second_vertex - 1, weight });
//        reversed_adj_list[second_vertex - 1].push_back({ first_vertex - 1, second_vertex - 1, weight });
//    }
//    vector<bool> visited(n);
//    dfs(visited, adj_list, 0);
//    if (any_of(visited.begin(), visited.end(), [&visited](bool a) { return a == false; })) {
//        fout << "NO";
//        return 0;
//    }
//    fout << "YES\n" << chinese_mst(reversed_adj_list, adj_list, n, 0);
//    //for (int i = 1; i < n; ++i) {
//    //    if (reversed_adj_list[i].empty()) {
//    //        fout << "NO";
//    //        return 0;
//    //    }
//    //    int min_weight = min_element(reversed_adj_list[i].begin(), reversed_adj_list[i].end())->weight;
//    //    for_each(reversed_adj_list[i].begin(), reversed_adj_list[i].end(), [&min_weight](Edge& e) { e.weight -= min_weight; });
//
//    //}
//    
//	return 0;
//}
//vector<int> dfs_exit_times(vector<Checking_status>& vertexes, vector<vector<Edge>> const& adj_list);
//void dfs_exit_times_visit(vector<Checking_status>& vertexes, vector<vector<Edge>> const& adj_list, \
//    int const& index, vector<int>& times_arr);
//void dfs_mark_components(vector<int>& vertexes, vector<vector<Edge>> const& adj_transposed, \
//    int index, int component);
//
//int condensation(vector<int>& vertexes, vector<vector<Edge>> const& adj_list, \
//    vector<vector<Edge>> const& adj_list_transposed) {
//    vector<Checking_status> vertexes_visited(n);
//    vector<int> sorted_order = dfs_exit_times(vertexes_visited, adj_list);
//    int component = -1;
//    for (int i = 0; i < vertexes.size(); ++i) {
//        if (vertexes[sorted_order[i]] == -1) {
//            ++component;
//            dfs_mark_components(vertexes, adj_list_transposed, sorted_order[i], component);
//        }
//    }
//    return component;
//}
//
//
//vector<int> dfs_exit_times(vector<Checking_status>& vertexes, vector<vector<Edge>> const& adj_list) {
//    vector<int> sorted_backwards;
//    for (int i = 0; i < n; ++i) {
//        if (vertexes[i] == NOT_CHECKED) {
//            dfs_exit_times_visit(vertexes, adj_list, i, sorted_backwards);
//        }
//    }
//    return vector<int>(sorted_backwards.rbegin(), sorted_backwards.rend());
//}
//
//
//void dfs_exit_times_visit(vector<Checking_status>& vertexes, vector<vector<Edge>> const& adj_list, \
//    int const& index, vector<int>& times_arr) {
//    vertexes[index] = CHECKED;
//
//    for (auto iter = adj_list[index].begin(); iter != adj_list[index].end(); ++iter) {
//        if (vertexes[iter->end] == NOT_CHECKED) {
//            dfs_exit_times_visit(vertexes, adj_list, iter->end, times_arr);
//        }
//    }
//
//    times_arr.push_back(index);
//}
//
//
//void dfs_mark_components(vector<int>& vertexes, vector<vector<Edge>> const& adj_transposed, \
//    int index, int component) {
//    vertexes[index] = component;
//    for (auto iter = adj_transposed[index].begin(); iter != adj_transposed[index].end(); ++iter) {
//        if (vertexes[iter->begin] == -1) {
//            dfs_mark_components(vertexes, adj_transposed, iter->begin, component);
//        }
//    }
//}
//
//
//void dfs(vector<bool> &vertexes, vector<vector<Edge>> const& edges, int index) {
//    vertexes[index] = true;
//    for (auto const& adj : edges[index]) {
//        if (vertexes[adj.end] == false) {
//            dfs(vertexes, edges, adj.end);
//        }
//    }
//}
//
//
//long long chinese_mst(vector<vector<Edge>> &reversed_adj_list, vector<vector<Edge>> &adj_list, int num, int root) {
//    long long res = 0;
//    vector<vector<Edge>> min_edges(num);
//    vector<Edge> min_incoming(num);
//    for (int i = 0; i < num; ++i) {
//        if (i != root) {
//            Edge min_edge = *min_element(reversed_adj_list[i].begin(), reversed_adj_list[i].end());
//            min_edges[min_edge.begin].push_back(min_edge);
//            min_incoming[min_edge.end] = min_edge;
//            res += min_edge.weight;
//        }
//    }
//    vector<bool> visited(num);
//    dfs(visited, min_edges, root);
//    if (all_of(visited.begin(), visited.end(), [](bool a) { return a == true; })) {
//        return res;
//    }
//    vector<int> vertexes(num, -1);
//    int component_number = condensation(vertexes, adj_list, reversed_adj_list) + 1;
//    //if (component_number == num) {
//    //    return 0;
//    //}
//    vector<vector<Edge>> new_reversed(component_number), new_adj(component_number);
//    for (int i = 0; i < num; ++i) {
//        for (auto const& edge : adj_list[i]) {
//            if (vertexes[i] != vertexes[edge.end]) {
//                new_adj[vertexes[i]].push_back({ vertexes[i], vertexes[edge.end], edge.weight - min_incoming[edge.end].weight });
//                new_reversed[vertexes[edge.end]].push_back({ vertexes[i], vertexes[edge.end], edge.weight - min_incoming[edge.end].weight });
//            }
//        }
//    }
//    res += chinese_mst(new_reversed, new_adj, component_number, vertexes[root]);
//    return res;
//}
