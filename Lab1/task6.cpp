#include <fstream>
#include <vector>
#include <string>
#include <queue>
using namespace std;


struct Vertex {
    int distance = 0;
    int parent = -1;    
    bool checked = false;
};

void bfs(vector<vector<char>> const &labyrinth, vector<Vertex> &vertexes, \
        int const &start_point, int const &exit_point);
vector<int> find_connections(vector<vector<char>> const &labyrinth, int const &check,\
                            int const &exit_point);
string find_path(vector<Vertex> const &vertexes, int const &exit_point);
int n, m;


int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    
    fin >> n >> m;
    vector<vector<char>> labyrinth(n, vector<char>(m));
    int starting_point, exit_point;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            char labyrinth_element;
            fin >> labyrinth_element;
            if (labyrinth_element == 'S') {
                starting_point = i * m + j;
            }
            else if (labyrinth_element == 'T') {
                exit_point = i * m + j;
            }
            labyrinth[i][j] = labyrinth_element;
        }
    }

    vector<Vertex> vertexes(n * m, Vertex());
    bfs(labyrinth, vertexes, starting_point, exit_point);
    
    if (vertexes[exit_point].checked) {
        string path = find_path(vertexes, exit_point);
        fout << vertexes[exit_point].distance << '\n' << path;
    }
    else {
        fout << -1;
    }

    return 0;
}


void bfs(vector<vector<char>> const &labyrinth, vector<Vertex> &vertexes,\
         int const &start_point, int const &exit_point) {

    vertexes[start_point].checked = true;
    queue<int> vertexes_queue;
    vertexes_queue.push(start_point);
    while (vertexes_queue.size() != 0) {

        int check = vertexes_queue.front();
        vertexes_queue.pop();
        vertexes[check].checked = true;
        vector<int> adj_list = find_connections(labyrinth, check, exit_point);

        for (vector<int>::iterator i = adj_list.begin(); i != adj_list.end(); ++i) {
            if (vertexes[*i].checked == false) {
                vertexes[*i].checked = true;
                vertexes[*i].parent = check;
                vertexes[*i].distance = vertexes[check].distance + 1;
                vertexes_queue.push(*i);
            }
            if (*i == exit_point) {
                return;
            }
        }

    }
}


vector<int> find_connections(vector<vector<char>> const &labyrinth, int const &check,\
                            int const &exit_point) {
    
    vector<int> adj_list;
    int y_pos = check / m;
    int x_pos = check % m;

    if (x_pos > 0 && (labyrinth[y_pos][x_pos - 1] == '.' || check - 1 == exit_point)) {
        adj_list.push_back(check - 1);
    }
    if (x_pos < m - 1 && (labyrinth[y_pos][x_pos + 1] == '.' || check + 1 == exit_point)) {
        adj_list.push_back(check + 1);
    }
    if (y_pos > 0 && (labyrinth[y_pos - 1][x_pos] == '.' || check - m == exit_point)) {
        adj_list.push_back(check - m);
    }
    if (y_pos < n - 1 && (labyrinth[y_pos + 1][x_pos] == '.' || check + m == exit_point)) {
        adj_list.push_back(check + m);
    }

    return adj_list;
}


string find_path(vector<Vertex> const &vertexes, int const &exit_point) {
    string path;
    int curr_index = exit_point;
    int parent_index = vertexes[exit_point].parent;
    while (parent_index != -1) {
        if (parent_index == curr_index - m) {
            path = "D" + path;
        }
        else if (parent_index == curr_index - 1) {
            path = "R" + path;
        }
        else if (parent_index == curr_index + m) {
            path = "U" + path;
        }
        else if (parent_index == curr_index + 1 && parent_index / m == curr_index / m) {
            path = "L" + path;
        }
        curr_index = parent_index;
        parent_index = vertexes[parent_index].parent;
    }
    return path;
}