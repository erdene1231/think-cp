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
