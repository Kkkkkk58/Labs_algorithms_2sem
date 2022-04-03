#include <fstream>
#include <vector>
#include <limits>
#include <cmath>
#include <iomanip>
using namespace std;

const double EPS = 1e-9;
long double total_weight = 0;
int n;

struct Point {
    int x = 0, y = 0;
};

class Heap {
public:
    explicit Heap(vector<double> const& vertexes)
        : vertexes_(vertexes), 
          heap_size_(vertexes_.size()), 
          positions_(vector<size_t>(heap_size_)) {
        for (size_t i = 0; i < heap_size_; ++i) {
            positions_[i] = i;
        }
        for (size_t i = 0; i < heap_size_ / 2; ++i) {
            heapify(i);
        }
    }

    void decrease_key(size_t pos, double new_value) {
        vertexes_[pos] = new_value;
        while (pos > 0 && vertexes_[(pos - 1) / 2] > vertexes_[pos]) {
            swap(positions_[pos], positions_[(pos - 1) / 2]);
            swap(vertexes_[(pos - 1) / 2], vertexes_[pos]);
            pos = (pos - 1) / 2;
        }
    }

    pair<double, size_t> extract_min() {
        double min_edge = vertexes_[0];
        size_t min_position = positions_[0];
        positions_[0] = positions_[heap_size_ - 1];
        vertexes_[0] = vertexes_[heap_size_ - 1];
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
    vector<double> vertexes_;
    size_t heap_size_;
    vector<size_t> positions_;

    void heapify(size_t index) {
        size_t left = 2 * index + 1;
        size_t right = left + 1;
        size_t least = index;
        if (left < heap_size_ && (vertexes_[left] - vertexes_[index]) < -EPS) {
            least = left;
        }
        if (right < heap_size_ && (vertexes_[right] - vertexes_[least]) < -EPS) {
            least = right;
        }
        if (least != index) {
            swap(vertexes_[index], vertexes_[least]);
            swap(positions_[index], positions_[least]);
            heapify(least);
        }
    }
};

void prim_mst(vector<vector<double>> const& matrix);


int main() {
    ifstream fin("spantree.in");
    ofstream fout("spantree.out");
    fin >> n;
    vector<vector<double>> matrix(n, vector<double>(n));
    vector<Point> vertexes(n);

    for (int i = 0; i < n; ++i) {
        int x, y;
        fin >> x >> y;
        vertexes[i] = {x, y};
        for (int j = i - 1; j >= 0; --j) {
            double distance = sqrt(pow(x - vertexes[j].x, 2) + pow(y - vertexes[j].y, 2));
            matrix[i][j] = distance;
            matrix[j][i] = distance;
        }   
    }

    prim_mst(matrix);
    fout << setprecision(10) << total_weight;

    return 0;
}


void prim_mst(vector<vector<double>> const& matrix) {
    vector<double> distances(n, numeric_limits<double>::max());
    distances[0] = 0;
    Heap queue(distances);

    while (!queue.empty()) {
        pair<double, size_t> curr_min = queue.extract_min();
        total_weight += curr_min.first;
        size_t curr_index = curr_min.second;

        for (size_t i = 0; i < queue.size(); ++i) {
            if (matrix[curr_index][queue.positions_[i]] - queue.vertexes_[i] < -EPS) {
                queue.decrease_key(i, matrix[curr_index][queue.positions_[i]]);
            }
        }
    }
}