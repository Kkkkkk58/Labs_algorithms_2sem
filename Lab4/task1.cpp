#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const unsigned long long INF = 1e16;

class Heap {
public:
    explicit Heap(vector<long long> const& distances)
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

    void decrease_key(size_t pos, long long new_value) {
        distances_[pos] = new_value;
        while (pos > 0 && distances_[(pos - 1) / 2] > distances_[pos]) {
            swap(positions_[pos], positions_[(pos - 1) / 2]);
            swap(distances_[(pos - 1) / 2], distances_[pos]);
            pos = (pos - 1) / 2;
        }
    }

    pair<long long, size_t> extract_min() {
        long long min_edge = distances_[0];
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
    
    vector<long long> distances_;
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

long long dijkstra(vector<long long> const& distances, vector<vector<int>> const& matrix, \
size_t start, size_t finish);

size_t n;


int main() {
    ifstream fin("pathmgep.in");
    ofstream fout("pathmgep.out");
    size_t s, f;
    fin >> n >> s >> f;
    vector<vector<int>> matrix(n, vector<int>(n));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            fin >> matrix[i][j]; 
        }
    }
    vector<long long> distances(n, INF);
    distances[s - 1] = 0;

    fout << dijkstra(distances, matrix, s - 1, f - 1);
    return 0;    
}


long long dijkstra(vector<long long> const& distances, vector<vector<int>> const& matrix, \
size_t start, size_t finish) {
    Heap queue(distances);

    while (!queue.empty()) {
        pair<long long, size_t> curr_vertex = queue.extract_min();
        size_t index = curr_vertex.second;
        long long weight = curr_vertex.first;

        if (weight >= INF) {
            return -1;
        }   
        if (index == finish) {
            return weight;
        }

        for (size_t i = 0; i < queue.size(); ++i) {
            if (matrix[index][queue.positions_[i]] != -1 && \
                weight + matrix[index][queue.positions_[i]] < queue.distances_[i]) {
                queue.decrease_key(i, weight + matrix[index][queue.positions_[i]]);
            }
        }
    }
    return -1;
}