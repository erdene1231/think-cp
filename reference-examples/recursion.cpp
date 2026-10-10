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
    cout << factorial(4) << '\n';

    return 0;
}
