#include <bits/stdc++.h>
using namespace std;

bool balanced(const string& s) {
    stack<char> st;

    for (char c : s) {
        if (c == '(') {
            st.push(c);
        } else {
            if (st.empty()) {
                return false;
            }

            st.pop();
        }
    }

    return st.empty();
}

vector<int> queue_order(const vector<int>& a) {
    queue<int> q;

    for (int x : a) {
        q.push(x);
    }

    vector<int> ans;

    while (!q.empty()) {
        ans.push_back(q.front());
        q.pop();
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    cout << (balanced(s) ? "YES" : "NO") << '\n';
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> ans = queue_order(a);
    for (int i = 0; i < (int)ans.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << ans[i];
    }
    cout << '\n';

    return 0;
}
