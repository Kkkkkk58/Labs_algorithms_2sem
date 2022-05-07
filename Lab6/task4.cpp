#include <iostream>
#include <vector>
#include <string>
using namespace std;

void build_prefix(string const& text, vector<size_t> &prefix);
vector<vector<size_t>> kmp_automata_states(string const& pattern);

size_t n;
int main() {
    string pattern;
    cin >> n >> pattern;

    vector<vector<size_t>> states = kmp_automata_states(pattern);

    for (size_t i = 0; i < states.size(); ++i) {
        for (size_t state : states[i]) {
            cout << state << " ";
        }
        cout << "\n";
    }
    return 0;
}


vector<vector<size_t>> kmp_automata_states(string const& pattern) {
    vector<vector<size_t>> states(pattern.size() + 1, vector<size_t>(n));

    vector<size_t> pattern_prefix(pattern.size() + 1);
    build_prefix(pattern, pattern_prefix);

    for (size_t i = 0; i <= pattern.size(); ++i) {
        for (size_t j = 0; j < n; ++j) {

            if (('a' + j) == pattern[i]) {
                states[i][j] = i + 1;
            }
            
            else {
                states[i][j] = states[pattern_prefix[i]][j];
            }
        }
    }
    return states;
}


void build_prefix(string const& text, vector<size_t> &prefix) {
   if (text.size() == 1) {
       return;
   }

   size_t i = 1, j = 0;
   while (i < text.size()) {
       if (text[i] == text[j]) {
           prefix[i + 1] = j + 1;
           ++i;
           ++j;
       }

       else if (j != 0) {
           j = prefix[j];
       }
       
       else {
           prefix[i + 1] = 0;
           ++i;
       }
   }
}
