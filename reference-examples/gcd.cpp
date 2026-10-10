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
    cout << gcd_value(24, 18) << '\n';

    return 0;
}
