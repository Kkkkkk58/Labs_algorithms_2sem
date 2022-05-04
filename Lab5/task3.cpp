#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
 
string lcs(string& first, string& second);
 

int main() {
    string first, second;
    cin >> first >> second;
    cout << lcs(first, second) << "\n";
    return 0;
}
 
 
string lcs(string& first, string& second) {
    short n = first.size() + 1, m = second.size() + 1;
    if (m > n) {
        swap(first, second);
        swap(n, m);
    }
    vector<vector<short>> largest_common_lengths(2, vector<short>(m));
    vector<vector<bool>> prev(n - 1, vector<bool>(m - 1));

    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 1; j < m; ++j) {
            if (first[i - 1] == second[j - 1]) {
                largest_common_lengths[i % 2][j] = largest_common_lengths[(i - 1) % 2][j - 1] + 1;
            }
            else {
                if (largest_common_lengths[(i - 1) % 2][j] > largest_common_lengths[i % 2][j - 1]) {
                    largest_common_lengths[i % 2][j] = largest_common_lengths[(i - 1) % 2][j];
                    prev[i - 1][j - 1] = 0;
                }
                else {
                    largest_common_lengths[i % 2][j] = largest_common_lengths[i % 2][j - 1];
                    prev[i - 1][j - 1] = 1;
                }
            }
        }
    }

    string ans;
    short i_index = n - 2, j_index = m - 2;
    while (i_index >= 0 && j_index >= 0) {
        if (first[i_index] == second[j_index]) {
            ans += first[i_index];
            --i_index;
            --j_index;
        }
        else if (prev[i_index][j_index] == 0) {
            --i_index;
        }
        else {
            --j_index;
        }
    }

    reverse(ans.begin(), ans.end());
    return ans;
}