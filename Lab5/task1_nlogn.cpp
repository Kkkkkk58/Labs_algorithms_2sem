#include <iostream>
#include <limits>
#include <vector>
using namespace std;

constexpr int INF = numeric_limits<int>::max();

size_t binsearch(vector<int>& lis, int value, size_t curr_len);
vector<int> find_lis(vector<int> const& data, size_t& curr_len);

size_t n;
int main() {
 
    cin >> n;
    vector<int> data(n);
    size_t curr_len = 0;

    for (size_t i = 0; i < n; ++i) {
        cin >> data[i];
    }

    vector<int> lis = find_lis(data, curr_len);
    cout << curr_len << "\n";

    for (auto value : lis) {
        cout << value << " ";
    }
    return 0;
}

vector<int> find_lis(vector<int> const& data, size_t& curr_len) {

    vector<int> lis_min_elements(n, INF);
    vector<int> prev(n, -1);
    vector<int> indexes(n, -1);

    for (size_t i = 0; i < n; ++i) {
        size_t position = binsearch(lis_min_elements, data[i], curr_len);
        lis_min_elements[position] = data[i];
        indexes[position] = i;

        if (position > 0) {
            prev[i] = indexes[position - 1];
        }
        if (position >= curr_len) {
            ++curr_len;
        }
    }
    
    vector<int> ans(curr_len);
    for (int curr_index = indexes[curr_len - 1], i = curr_len - 1; curr_index != -1; curr_index = prev[curr_index], --i) {
        ans[i] = data[curr_index];
    }
    return ans;
}


size_t binsearch(vector<int>& lis, int value, size_t curr_len) {
    int left = 0, right = curr_len;
    size_t position = 0;
    while (left < right) {
        position = (left + right) / 2;
        if (lis[position] == value) {
            return position;
        }
        else if (lis[position] > value) {
            right = position;
        }
        else {
            left = position + 1;
        }
    }
    if (lis[position] > value) {
        return position;
    }
    return position + 1;
}