#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        p[i]--;
    }

    vector<int> q(n);
    for (int i = 0; i < n; ++i) {
        q[i] = i;
    }

    for (int i = 0; i < n; ++i) {
        if (q[i] == p[i]) {
            if (i < n - 1) {
                swap(q[i], q[i + 1]);
            } else {
                swap(q[i], q[i - 1]);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << q[i] + 1 << " \n"[i == n - 1];
    }

    return 0;
}