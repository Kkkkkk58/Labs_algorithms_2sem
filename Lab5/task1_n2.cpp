#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

vector<int> find_lis(vector<int> const& data);

size_t n;
int main() {
    cin >> n;
    
    vector<int> data(n);
    for (size_t i = 0; i < n; ++i) {
        cin >> data[i];
    }

    vector<int> lis = find_lis(data);
    cout << lis.size() << "\n";
    for (auto value: lis) {
        cout << value << " ";
    }

    return 0;
}


vector<int> find_lis(vector<int> const& data) {
    vector<int> lis_lengths(n, 1);
    vector<int> prev(n, -1);

    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (data[i] > data[j] && lis_lengths[j] + 1 > lis_lengths[i]) {
                lis_lengths[i] = lis_lengths[j] + 1;
                prev[i] = j;
            }
        }
    }

    size_t max_length_index = max_element(lis_lengths.begin(), lis_lengths.end()) - lis_lengths.begin();
    size_t lis_size = lis_lengths[max_length_index];  
    vector<int> ans(lis_size);
    for (int curr_element = max_length_index, i = lis_size - 1; curr_element != -1; \
    curr_element = prev[curr_element], --i) {
        ans[i] = data[curr_element];
    }
    return ans;
}