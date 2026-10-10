#include <bits/stdc++.h>
using namespace std;

long long count_pairs(int n) {
    long long ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ans++;
        }
    }

    return ans;
}

int halvings(int n) {
    int steps = 0;

    while (n > 1) {
        n /= 2;
        steps++;
    }

    return steps;
}
