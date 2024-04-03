#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

struct Node {
    int x, y;
    int g, h;
    Node* parent;

    Node(int x, int y, int g, int h, Node* parent) : x(x), y(y), g(g), h(h), parent(parent) {}

    int f() const {
        return g + h;
    }
};

vector<Node*> findPath(const vector<vector<int>>& grid, const pair<int, int>& start, const pair<int, int>& end) {
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    int rows = grid.size();
    int cols = grid[0].size();

    auto isValid = [&](int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0;
    };

    auto manhattanDistance = [&](int x1, int y1, int x2, int y2) {
        return abs(x2 - x1) + abs(y2 - y1);
    };

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> pq;
    pq.push({0, new Node(start.first, start.second, 0, manhattanDistance(start.first, start.second, end.first, end.second), nullptr)});

    while (!pq.empty()) {
        auto [priority, current] = pq.top();
        pq.pop();

        if (current->x == end.first && current->y == end.second) {
            vector<Node*> path;
            while (current != nullptr) {
                path.push_back(current);
                current = current->parent;
            }
            return path;
        }

        if (visited[current->x][current->y]) continue;
        visited[current->x][current->y] = true;

        for (int i = 0; i < 4; ++i) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (isValid(nx, ny) && !visited[nx][ny]) {
                pq.push({current->g + 1 + manhattanDistance(nx, ny, end.first, end.second),
                         new Node(nx, ny, current->g + 1, manhattanDistance(nx, ny, end.first, end.second), current)});
            }
        }
    }

    return {};
}

int main() {
    vector<vector<int>> grid = {
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 1, 0, 0, 0},
    {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
    {1, 1, 0, 0, 0, 0, 0, 0, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 1, 0, 1, 0}
};

    pair<int, int> start = {0, 0};
    pair<int, int> end = {19, 7};

    auto path = findPath(grid, start, end);

    if (!path.empty()) {
        cout << "Caminho encontrado:" << endl;
        for (int i = path.size() - 1; i >= 0; --i) {
            cout << "(" << path[i]->x << ", " << path[i]->y << ")" << endl;
        }
    } else {
        cout << "Nenhum caminho encontrado." << endl;
    }

    return 0;
}
