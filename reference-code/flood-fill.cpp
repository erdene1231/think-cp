#include <bits/stdc++.h>
using namespace std;

int count_rooms(const vector<string>& grid) {
    int n = grid.size();

    if (n == 0) {
        return 0;
    }

    int m = grid[0].size();
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    int ans = 0;

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (grid[r][c] == '#' || visited[r][c]) {
                continue;
            }

            ans++;
            queue<pair<int, int>> q;
            q.push({r, c});
            visited[r][c] = true;

            while (!q.empty()) {
                int row = q.front().first;
                int col = q.front().second;
                q.pop();

                for (int d = 0; d < 4; d++) {
                    int nr = row + dr[d];
                    int nc = col + dc[d];

                    if (nr < 0 || nr >= n || nc < 0 || nc >= m) {
                        continue;
                    }

                    if (grid[nr][nc] == '#' || visited[nr][nc]) {
                        continue;
                    }

                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
    }

    return ans;
}
