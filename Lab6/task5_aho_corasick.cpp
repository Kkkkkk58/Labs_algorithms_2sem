#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <iostream>
using namespace std;

const size_t LETTERS_COUNT = 26;
size_t n;


struct Node {
    Node(char s, Node *p = nullptr) : symbol(s), parent(p) {}
    ~Node() {
        for (size_t i = 0; i < n; ++i) {
            delete successors[i];
        }
    }

    int pattern_index = -1; 
    bool is_terminal = false;
    Node *parent = nullptr;
    Node *suffix_link = nullptr;
    Node *short_link = nullptr;
    vector<Node *> successors = vector<Node *>(LETTERS_COUNT); 
    vector<Node *> moves = vector<Node *>(LETTERS_COUNT);
    char symbol;
};


class Trie {
public:

    Trie(vector<string> const& trie_base) : root(new Node(' ')) {
        size_t i = 0;
        for (string const& pattern : trie_base) {
            add_pattern(pattern, i);
            ++i;
        }
    }

    vector<bool> find_occurences(string const& text) {
        vector<bool> occurences(n);
        Node *state = root;
        for (char symbol : text) {
            state = get_move(state, symbol);
            mark(state, occurences);
        }
        return occurences;
    }

    ~Trie() {
        delete root;
    }
private:

    void add_pattern(string const& pattern, size_t order) {
        Node *curr = root;
        for (char symbol : pattern) {
            if (curr->successors[symbol - 'a'] == nullptr) {
                curr->successors[symbol - 'a'] = new Node(symbol, curr);
            }
            curr = curr->successors[symbol - 'a'];
        }
        curr->is_terminal = true;
        curr->pattern_index = order;    
    }

    Node *get_suffix_link(Node *node) {
        if (node->suffix_link == nullptr) {
            if (node == root || node->parent == root) {
                node->suffix_link = root;
            }
            else {
                node->suffix_link = get_move(get_suffix_link(node->parent), node->symbol);
            }
        }
        return node->suffix_link;
    }

    Node *get_move(Node *node, char symbol) {
        if (node->moves[symbol - 'a'] == nullptr) {
            if (node->successors[symbol - 'a'] != nullptr) {
                node->moves[symbol - 'a'] = node->successors[symbol - 'a'];
            }
            else {
                if (node == root) {
                    node->moves[symbol - 'a'] = root;
                }
                else {
                    node->moves[symbol - 'a'] = get_move(get_suffix_link(node), symbol);
                }
            }
        }
        return node->moves[symbol - 'a'];
    }

    Node *get_short_link(Node *node) {
        if (node->short_link == nullptr) {
            Node *suff_link = get_suffix_link(node);
            if (suff_link == root || suff_link->is_terminal) {
                node->short_link = suff_link;
            }
            else {
                node->short_link = get_short_link(suff_link);
            }
        }
        return node->suffix_link;
    }

    void mark(Node *node, vector<bool>& occurences) {
        Node *curr = node;
        while (curr != root) {
            if (curr->is_terminal) {
                occurences[curr->pattern_index] = true;
            }
            curr = get_short_link(curr);
        }
    }

    Node *root;
};




int main() {
    ifstream fin("search4.in");
    ofstream fout("search4.out");
    fin >> n;

    vector<string> trie_base(n);
    for (size_t i = 0; i < n; ++i) {
        fin >> trie_base[i];
    }
    Trie trie(trie_base);

    string t;
    fin >> t;

    std::vector<bool> occurences = trie.find_occurences(t);
    for (bool found : occurences) {
        if (found) {
            fout << "YES\n";
        }
        else {
            fout << "NO\n";
        }
    } 
    return 0;
}