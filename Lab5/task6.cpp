#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

enum {
    NOT_INCLUDED,
    INCLUDED
};

int valid_max_sum(vector<vector<size_t>> const& adj_list, vector<int> const& numbers, size_t root);
void dfs(vector<vector<size_t>> const& adj_list, vector<int> const& numbers, \
vector<vector<int>> &max_subtrees, size_t index);

size_t n;
int main() {
    ifstream fin("selectw.in");
    ofstream fout("selectw.out");
    fin >> n;
    vector<vector<size_t>> adj_list(n);
    vector<int> numbers(n);
    size_t root = 0;
    for (size_t i = 0; i < n; ++i) {
        size_t parent;
        int number;
        fin >> parent >> number;
        if (parent != 0) {
            adj_list[parent - 1].push_back(i);
        }
        else {
            root = i;
        }
        numbers[i] = number;
    }
    fout << valid_max_sum(adj_list, numbers, root);
    return 0;
}


int valid_max_sum(vector<vector<size_t>> const& adj_list, vector<int> const& numbers, size_t root) {
    vector<vector<int>> max_subtrees(n, vector<int>(2));
    dfs(adj_list, numbers, max_subtrees, root);
    return max(max_subtrees[root][INCLUDED], max_subtrees[root][NOT_INCLUDED]);
}


void dfs(vector<vector<size_t>> const& adj_list, vector<int> const& numbers, \
vector<vector<int>> &max_subtrees, size_t index) {
    for (size_t adj : adj_list[index]) {
        dfs(adj_list, numbers, max_subtrees, adj);
        max_subtrees[index][INCLUDED] += max_subtrees[adj][NOT_INCLUDED];
        max_subtrees[index][NOT_INCLUDED] += max(max_subtrees[adj][INCLUDED],\
                                                max_subtrees[adj][NOT_INCLUDED]);         
    }

    max_subtrees[index][INCLUDED] += numbers[index];
}