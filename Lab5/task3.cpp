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
    size_t n = first.size() + 1, m = second.size() + 1;
    if (m > n) {
        swap(first, second);
        swap(n, m);
    }
    vector<vector<int>> largest_common_lengths(2, vector<int>(m));
    vector<vector<pair<int, int>>> prev(n, vector<pair<int, int>>(m, { -1, -1 }));

    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 1; j < m; ++j) {
            if (first[i - 1] == second[j - 1]) {
                largest_common_lengths[i % 2][j] = largest_common_lengths[(i - 1) % 2][j - 1] + 1;
                //prev[i % 2][j] = prev[(i - 1) % 2][j - 1] + first[i - 1];
                prev[i][j] = { i - 1, j - 1 };
            }
            else {
                if (largest_common_lengths[(i - 1) % 2][j] > largest_common_lengths[i % 2][j - 1]) {
                    largest_common_lengths[i % 2][j] = largest_common_lengths[(i - 1) % 2][j];
                    //prev[i % 2][j] = prev[(i - 1) % 2][j];
                    prev[i][j] = { i - 1, j };
                }
                else {
                    largest_common_lengths[i % 2][j] = largest_common_lengths[i % 2][j - 1];
                    //prev[i % 2][j] = prev[i % 2][j - 1];
                    prev[i][j] = { i, j - 1 };
                }
            }
        }
    }
    string ans;
    pair<int, int> indexes = { n - 1, m - 1 };
    while (indexes.first != 0 && indexes.second != 0) {
        if (pair{ prev[indexes.first][indexes.second].first + 1, \
            prev[indexes.first][indexes.second].second + 1 } == indexes) {
            ans += first[indexes.first - 1];
        }
        indexes = { prev[indexes.first][indexes.second] };
    }

    reverse(ans.begin(), ans.end());
    return ans;
    //return prev[1][m - 1];
}