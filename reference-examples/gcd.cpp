#include <bits/stdc++.h>
using namespace std;

long long gcd_value(long long a, long long b) {
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }

    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b;
    cin >> a >> b;
    cout << gcd_value(a, b) << '\n';

    return 0;
}
