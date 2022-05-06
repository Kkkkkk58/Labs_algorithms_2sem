#include <fstream>
#include <vector>
#include <string>
using namespace std;

void build_prefix(string const& text, vector<size_t> &prefix);

int main() {
    ifstream fin("prefix.in");
    ofstream fout("prefix.out");
    string text;
    fin >> text;

    vector<size_t> prefix(text.size() + 1);
    build_prefix(text, prefix);

    for (size_t i = 1; i < prefix.size(); ++i) {
        fout << prefix[i] << " ";
    }
    return 0;
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