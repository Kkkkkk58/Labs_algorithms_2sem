#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const size_t INF = 1e9;

struct Edge {
    size_t end, weight;
};

class Heap {
public:
    explicit Heap(vector<size_t> const& distances)
        : distances_(distances),
        heap_size_(distances_.size()),
        positions_(vector<size_t>(heap_size_)) {
        for (size_t i = 0; i < heap_size_; ++i) {
            positions_[i] = i;
        }
        for (int i = heap_size_ / 2; i >= 0; --i) {
            heapify(i);
        }
    }

    void decrease_key(size_t pos, size_t new_value) {
        distances_[pos] = new_value;
        while (pos > 0 && distances_[(pos - 1) / 2] > distances_[pos]) {
            swap(positions_[pos], positions_[(pos - 1) / 2]);
            swap(distances_[(pos - 1) / 2], distances_[pos]);
            pos = (pos - 1) / 2;
        }
    }

    pair<size_t, size_t> extract_min() {
        size_t min_edge = distances_[0];
        size_t min_position = positions_[0];
        positions_[0] = positions_[heap_size_ - 1];
        distances_[0] = distances_[heap_size_ - 1];
        heap_size_ -= 1;
        heapify(0);
        return { min_edge, min_position };
    }

    size_t size() const {
        return heap_size_;
    }

    bool empty() const {
        return heap_size_ == 0;
    }
    ~Heap() = default;

    vector<size_t> distances_;
    size_t heap_size_;
    vector<size_t> positions_;

    void heapify(size_t index) {
        size_t left = 2 * index + 1;
        size_t right = left + 1;
        size_t least = index;
        if (left < heap_size_ && distances_[left] < distances_[index]) {
            least = left;
        }
        if (right < heap_size_ && distances_[right] < distances_[least]) {
            least = right;
        }
        if (least != index) {
            swap(distances_[index], distances_[least]);
            swap(positions_[index], positions_[least]);
            heapify(least);
        }
    }
};


typedef vector<vector<Edge>> Edges;
void dijkstra(vector<size_t>& distances, Edges const& adj_list);

size_t n, m;


int main() {
    ifstream fin("pathbgep.in");
    ofstream fout("pathbgep.out");
    fin >> n >> m;
    Edges adj_list(n);

    for (size_t i = 0; i < m; ++i) {
        size_t first_vertex, second_vertex, weight;
        fin >> first_vertex >> second_vertex >> weight;
        adj_list[first_vertex - 1].push_back({ second_vertex - 1, weight });
        adj_list[second_vertex - 1].push_back({ first_vertex - 1, weight });
    }

    vector<size_t> distances(n, INF);
    distances[0] = 0;

    dijkstra(distances, adj_list);
    for (size_t distance : distances) {
        fout << distance << " ";
    }

    return 0;
}


void dijkstra(vector<size_t>& distances, Edges const& adj_list) {
    Heap queue(distances);
    while (!queue.empty()) {
        pair<size_t, size_t> curr_vertex = queue.extract_min();

        for (auto const& adj : adj_list[curr_vertex.second]) {
            size_t curr_weight = curr_vertex.first + adj.weight;
            if (curr_weight < distances[adj.end]) {
                distances[adj.end] = curr_weight;
                size_t curr_index = find(queue.positions_.begin(), queue.positions_.begin() + queue.size(), \
                    adj.end) - queue.positions_.begin();
                queue.decrease_key(curr_index, curr_weight);
            }
        }
    }
}