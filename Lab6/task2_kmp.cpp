#include <fstream>
#include <vector>
#include <string>
using namespace std;

vector<size_t> kmp_string_matcher(string const& text, string const& pattern);
void build_prefix(string const& text, vector<size_t> &prefix);


int main() {
   ifstream fin("search2.in");
   ofstream fout("search2.out");
   string pattern, text;
   fin >> pattern >> text;

   vector<size_t> match_indexes = kmp_string_matcher(text, pattern);

   fout << match_indexes.size() << "\n";
   for (size_t index : match_indexes) {
       fout << index << " ";
   }
   return 0;
}


vector<size_t> kmp_string_matcher(string const& text, string const& pattern) {
   vector<size_t> pattern_prefix(pattern.size() + 1);
   build_prefix(pattern, pattern_prefix);

   size_t i = 0, j = 0;
   vector<size_t> match_indexes;

   while (i < text.size()) {

       while (j < pattern.size() && i < text.size()) {
           if (text[i] == pattern[j]) {
               ++i;
               ++j;
           }
           else if (j != 0) {
               j = pattern_prefix[j];
           }
           else {
               ++i;
           }
       }

       if (j == pattern.size()) {
           match_indexes.push_back(i - pattern.size() + 1);
           j = pattern_prefix[j];
       }   
   }
   
   return match_indexes;
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