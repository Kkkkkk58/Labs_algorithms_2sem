#include <fstream>
#include <vector>
#include <iostream>
#include <set>
#include <string>
#include <queue>
using namespace std;


struct Vertex {
    int distance = 0;
    int parent = -1;    
    bool checked = false;
};

void bfs(vector<vector<int>> const &adj_list, vector<Vertex> &vertexes, \
        int start_point, int exit_point);


int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    
    int n, m;
    fin >> n >> m;
    vector<vector<char>> labyrinth(n + 2, vector<char>(m + 2));
    int starting_point, exit_point;
    for (size_t i = 1; i < n + 1; ++i) {
        for (size_t j = 1; j < m + 1; ++j) {
            char labyrinth_element;
            fin >> labyrinth_element;
            if (labyrinth_element == 'S') {
                starting_point = (i - 1) * m + (j - 1);
            }
            else if (labyrinth_element == 'T') {
                exit_point = (i - 1) * m + (j - 1);
            }
            labyrinth[i][j] = labyrinth_element;
        }
    }

    vector<vector<int>> adj_list(n * m, vector<int>());
    for (size_t i = 1; i < n + 1; ++i) {
        for (size_t j = 1; j < m + 1; ++j) {
            int vertex_index = (i - 1) * m + (j - 1);
            if (labyrinth[i - 1][j] == '.' || labyrinth[i - 1][j] == 'T') {
                adj_list[vertex_index].push_back((i - 2) * m + (j - 1));
            }
            if (labyrinth[i][j - 1] == '.' || labyrinth[i][j - 1] == 'T') {
                adj_list[vertex_index].push_back((i - 1) * m + (j - 2));
            }
            if (labyrinth[i + 1][j] == '.' || labyrinth[i + 1][j] == 'T') {
                adj_list[vertex_index].push_back(i * m + (j - 1));
            }
            if (labyrinth[i][j + 1] == '.' || labyrinth[i][j + 1] == 'T') {
                adj_list[vertex_index].push_back((i - 1) * m + j);
            }
        }
    }
    
    vector<Vertex> vertexes(n * m, Vertex());
    bfs(adj_list, vertexes, starting_point, exit_point);
    
    if (vertexes[exit_point].checked) {
        int curr_index = exit_point;
        int parent_index = vertexes[exit_point].parent;
        string path;
        while (parent_index != -1) {
            if (parent_index == curr_index - 1) {
                path = "R" + path;
            } 
            else if (parent_index == curr_index - m) {
                path = "D" + path;
            }
            else if (parent_index == curr_index + 1) { 
                path = "L" + path;
            }
            else if (parent_index == curr_index + m) {
                path = "U" + path;
            }
            curr_index = parent_index;
            parent_index = vertexes[parent_index].parent;
        }
        fout << vertexes[exit_point].distance << '\n' << path;
    }
    else {
        fout << -1;
    }

    return 0;
}


void bfs(vector<vector<int>> const &adj_list, vector<Vertex> &vertexes,\
         int start_point, int exit_point) {

    vertexes[start_point].checked = true;
    queue<int> vertexes_queue;
    vertexes_queue.push(start_point);

    while (vertexes_queue.size() != 0) {

        int checked_index = vertexes_queue.front();
        vertexes_queue.pop();

        for (size_t i = 0; i < adj_list[checked_index].size(); ++i) {

            int adj_position = adj_list[checked_index][i];
            if (vertexes[adj_position].checked == false) {
                vertexes[adj_position].checked = true;
                vertexes[adj_position].distance = vertexes[checked_index].distance + 1;
                vertexes[adj_position].parent = checked_index;
                vertexes_queue.push(adj_position);
            }

            if (adj_position == exit_point) {
                return;
            }

        }

    }
}