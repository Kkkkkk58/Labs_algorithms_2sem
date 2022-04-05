#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

size_t n, m;

enum class Checking_status : bool {
	NOT_CHECKED = false,
	CHECKED = true
};

struct Edge {
	int begin, end, weight;
};
typedef vector<vector<Edge>> Edges;


void dfs_check(Edges const& adj_list, vector<Checking_status>& vertexes, size_t index);
void dfs_mark_components(vector<int>& vertexes, Edges const& adj_list, size_t index, size_t component);
vector<size_t> dfs_exit_times(Edges const& adj_list);
void dfs_exit_times_visit(Edges const& adj_list, vector<Checking_status>& vertexes, \
	vector<size_t>& sorted_backwards, size_t index);
Edges invert(Edges const& other);
int condensation(Edges& adj_list, vector<int>& vertexes);
long long chinese_mst(Edges const& adj_list, size_t num, size_t root);


int main() {
	ifstream fin("chinese.in");
	ofstream fout("chinese.out");
	fin >> n >> m;

	Edges adj_list(n);
	for (size_t i = 0; i < m; ++i) {
		int first_vertex, second_vertex, weight;
		fin >> first_vertex >> second_vertex >> weight;
		adj_list[first_vertex - 1].push_back({ first_vertex - 1, second_vertex - 1, weight });
	}

	vector<Checking_status> vertexes(n);
	dfs_check(adj_list, vertexes, 0);
	if (any_of(vertexes.begin(), vertexes.end(), \
		[&vertexes](Checking_status a) { return a == Checking_status::NOT_CHECKED; })) {
		fout << "NO";
		return 0;
	}

	fout << "YES\n" << chinese_mst(adj_list, n, 0);
	return 0;
}


void dfs_check(Edges const& adj_list, vector<Checking_status>& vertexes, size_t index) {
	vertexes[index] = Checking_status::CHECKED;
	for (auto const& adj : adj_list[index]) {
		if (vertexes[adj.end] == Checking_status::NOT_CHECKED) {
			dfs_check(adj_list, vertexes, adj.end);
		}
	}
}


long long chinese_mst(Edges const& adj_list, size_t num, size_t root) {
	long long res = 0;
	vector<int> min_edges(num, numeric_limits<int>::max());

	for (size_t i = 0; i < num; ++i) {
		for (auto const& edge : adj_list[i]) {
			min_edges[edge.end] = min(min_edges[edge.end], edge.weight);
		}
	}

	for (size_t i = 0; i < num; ++i) {
		if (i != root) {
			res += min_edges[i];
		}
	}

	Edges zero_edges(num);
	for (size_t i = 0; i < num; ++i) {
		for (auto const& edge : adj_list[i]) {
			if (edge.weight == min_edges[edge.end]) {
				zero_edges[i].push_back({ edge.begin, edge.end, 0 });
			}
		}
	}

	vector<Checking_status> accesible(num);
	dfs_check(zero_edges, accesible, root);
	if (all_of(accesible.begin(), accesible.end(), \
		[&accesible](Checking_status a) { return a == Checking_status::CHECKED; })) {
		return res;
	}

	vector<int> components(num, -1);
	size_t components_number = condensation(zero_edges, components);
	Edges new_adj_list(components_number);
	for (size_t i = 0; i < num; ++i) {
		for (auto const& edge : adj_list[i]) {
			if (components[edge.begin] != components[edge.end]) {
				new_adj_list[components[edge.begin]].push_back\
					({ components[edge.begin], components[edge.end], edge.weight - min_edges[edge.end] });
			}
		}
	}

	res += chinese_mst(new_adj_list, components_number, components[root]);
	return res;
}


int condensation(Edges& adj_list, vector<int>& vertexes) {
	int component = -1;
	Edges adj_transposed = invert(adj_list);
	vector<size_t> sorted_order = dfs_exit_times(adj_list);
	for (size_t i = 0; i < vertexes.size(); ++i) {
		if (vertexes[sorted_order[i]] == -1) {
			++component;
			dfs_mark_components(vertexes, adj_transposed, sorted_order[i], component);
		}
	}
	return component + 1;
}


Edges invert(Edges const& other) {
	size_t size = other.size();
	Edges transposed(size);
	for (size_t i = 0; i < size; ++i) {
		for (auto const& edge : other[i]) {
			transposed[edge.end].push_back({ edge.end, edge.begin, edge.weight });
		}
	}
	return transposed;
}


vector<size_t> dfs_exit_times(Edges const& adj_list) {
	vector<Checking_status> vertexes(adj_list.size());
	vector<size_t> sorted_backwards;
	for (size_t i = 0; i < adj_list.size(); ++i) {
		if (vertexes[i] == Checking_status::NOT_CHECKED) {
			dfs_exit_times_visit(adj_list, vertexes, sorted_backwards, i);
		}
	}
	return vector<size_t>(sorted_backwards.rbegin(), sorted_backwards.rend());
}


void dfs_exit_times_visit(Edges const& adj_list, vector<Checking_status>& vertexes, \
	vector<size_t>& sorted_backwards, size_t index) {
	vertexes[index] = Checking_status::CHECKED;
	for (auto const& adj : adj_list[index]) {
		if (vertexes[adj.end] == Checking_status::NOT_CHECKED) {
			dfs_exit_times_visit(adj_list, vertexes, sorted_backwards, adj.end);
		}
	}
	sorted_backwards.push_back(index);
}


void dfs_mark_components(vector<int>& vertexes, Edges const& adj_list, \
	size_t index, size_t component) {
	vertexes[index] = component;
	for (auto const& adj : adj_list[index]) {
		if (vertexes[adj.end] == -1) {
			dfs_mark_components(vertexes, adj_list, adj.end, component);
		}
	}
}