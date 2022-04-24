#include <iostream>
#include <vector>
using namespace std;

enum {
    NOT_INCLUDED,
    INCLUDED
};

size_t valid_max(vector<vector<size_t>> const& adj_list, size_t root);
void dfs(vector<vector<size_t>> const& adj_list, vector<vector<size_t>> &max_subtrees, size_t vertex);

size_t n;
int main() {
    cin >> n;
    vector<vector<size_t>> adj_list(n);
    size_t root = 0;

    for (size_t i = 0; i < n; ++i) {
        size_t parent;
        cin >> parent;
        if (parent != 0) {
            adj_list[parent - 1].push_back(i);
        }
        else {
            root = i;
        }
    }

    cout << valid_max(adj_list, root);
    return 0;
}


size_t valid_max(vector<vector<size_t>> const& adj_list, size_t root) {
    vector<vector<size_t>> max_subtrees(n, vector<size_t>(2));
    dfs(adj_list, max_subtrees, root);
    return max(max_subtrees[root][NOT_INCLUDED], max_subtrees[root][INCLUDED]);
}


void dfs(vector<vector<size_t>> const& adj_list, vector<vector<size_t>> &max_subtrees, size_t vertex) {
    for (size_t adj : adj_list[vertex]) {
        dfs(adj_list, max_subtrees, adj);

        max_subtrees[vertex][INCLUDED] += max_subtrees[adj][NOT_INCLUDED];
        max_subtrees[vertex][NOT_INCLUDED] += max(max_subtrees[adj][NOT_INCLUDED], \
                                                max_subtrees[adj][INCLUDED]);
    }
    
    max_subtrees[vertex][INCLUDED] += 1;
}