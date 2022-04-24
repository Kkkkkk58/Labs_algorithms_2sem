#include <iostream>
#include <vector>
using namespace std;


constexpr unsigned long long MODULO = static_cast<unsigned long long>(1e9);
unsigned long long means_to_squat(vector<int> const& shirts_colours);


size_t n;
int main() {
    cin >> n;
    vector<int> shirts_colours(n);
    for (size_t i = 0; i < n; ++i) {
        cin >> shirts_colours[i];
    }
    cout << means_to_squat(shirts_colours);
    return 0;
}


unsigned long long means_to_squat(vector<int> const& shirts_colours) {
    vector<vector<unsigned long long>> sizes_of_palindroms(n, vector<unsigned long long>(n));
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i; j < n; ++j) {

            if (i == j) {
                sizes_of_palindroms[i][j] = 1;
                continue;
            }

            sizes_of_palindroms[i][j] = (sizes_of_palindroms[i + 1][j] + sizes_of_palindroms[i][j - 1]) % MODULO;
            if (shirts_colours[i] == shirts_colours[j]) {
                sizes_of_palindroms[i][j] = (sizes_of_palindroms[i][j] + 1) % MODULO;
            }

            else {
                if (sizes_of_palindroms[i + 1][j - 1] <= sizes_of_palindroms[i][j]) {
                    sizes_of_palindroms[i][j] = (sizes_of_palindroms[i][j] - sizes_of_palindroms[i + 1][j - 1]) % MODULO;
                }
                else {
                    sizes_of_palindroms[i][j] = (MODULO + sizes_of_palindroms[i][j] - sizes_of_palindroms[i + 1][j - 1]) % MODULO;
                }
            }
        }
    }
    
    return sizes_of_palindroms[0][n - 1];
}