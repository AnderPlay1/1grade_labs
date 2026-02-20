#include <iostream>
#include <vector>

using namespace std;

int n, m;

// DFS
bool dfs(vector<vector<int>> &maze, vector<vector<bool>> &visited, int r, int c, int tr, int tc)
{
    if (r < 0 || r >= n || c < 0 || c >= m)
        return false;

    if (maze[r][c] == 1 || visited[r][c])
        return false;

    if (r == tr && c == tc)
        return true;

    visited[r][c] = true;

    return dfs(maze, visited, r - 1, c, tr, tc) || // вверх
           dfs(maze, visited, r + 1, c, tr, tc) || // вниз
           dfs(maze, visited, r, c - 1, tr, tc) || // влево
           dfs(maze, visited, r, c + 1, tr, tc);   // вправо
}

int main()
{
    cout << "Enter rows and columns:\n";
    cin >> n >> m;

    vector<vector<int>> maze(n, vector<int>(m));

    cout << "Enter maze (0 - free, 1 - wall):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> maze[i][j];

    int sr, sc, tr, tc;
    cout << "Enter start cell (row col): ";
    cin >> sr >> sc;
    cout << "Enter target cell (row col): ";
    cin >> tr >> tc;

    if (maze[sr][sc] == 1 || maze[tr][tc] == 1)
    {
        cout << "Нет\n";
        return 0;
    }

    vector<vector<bool>> visited(n, vector<bool>(m, false));

    if (dfs(maze, visited, sr, sc, tr, tc))
        cout << "Да\n";
    else
        cout << "Нет\n";

    return 0;
}