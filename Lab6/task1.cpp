#include <fstream>
#include <vector>
#include <string>
using namespace std;

vector<size_t> naive_string_matcher(string const& text, string const& pattern);


int main() {
    ifstream fin("search1.in");
    ofstream fout("search1.out");
    string p, t;
    fin >> p >> t;
    vector<size_t> match_indexes = naive_string_matcher(t, p);
    fout << match_indexes.size() << "\n";
    for (size_t index : match_indexes) {
        fout << index << " ";
    }
    return 0;
}


vector<size_t> naive_string_matcher(string const& text, string const& pattern) {
    if (pattern.size() > text.size()) {
        return vector<size_t>();
    }
    vector<size_t> match_indexes;
    for (size_t i = 0; i <= text.size() - pattern.size(); ++i) {
        if (text[i] == pattern[0]) {
            size_t j = 0;
            for ( ; j < pattern.size() && i + j < text.size(); ++j) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == pattern.size()) {
                match_indexes.push_back(i + 1);
            }
        }
    }
    return match_indexes;
}
