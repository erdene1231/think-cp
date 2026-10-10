#include <bits/stdc++.h>
using namespace std;

long long factorial(int n) {
    if (n == 0) {
        return 1;
    }

    long long smaller = factorial(n - 1);
    return n * smaller;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    cout << factorial(n) << '\n';

    return 0;
}
