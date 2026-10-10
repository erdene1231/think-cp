#include <bits/stdc++.h>
using namespace std;

const long long INF = 4000000000000000000LL;

vector<vector<long long>> floyd(vector<vector<long long>> dist) {
    int n = dist.size();

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] == INF || dist[k][j] == INF) {
                    continue;
                }

                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    return dist;
}
