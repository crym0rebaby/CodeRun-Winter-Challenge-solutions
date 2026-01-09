#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXN = 3000;

// dp[n][k] = число Стирлинга первого рода (без знака)
// количество перестановок n элементов с k циклами
vector<vector<long long>> dp(MAXN + 1, vector<long long>(MAXN + 1, 0));

void precompute() {
    dp[0][0] = 1;
    for (int i = 1; i <= MAXN; ++i) {
        for (int k = 1; k <= i; ++k) {
            dp[i][k] = (dp[i - 1][k - 1] + (i - 1) * dp[i - 1][k]) % MOD;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    int t;
    cin >> t;
    while (t--) {
        int n, q, l, r;
        cin >> n >> q >> l >> r;

        vector<int> out(n + 1, 0), in(n + 1, 0);
        bool conflict = false;

        vector<int> b(q), c(q);
        for (int i = 0; i < q; ++i) cin >> b[i];
        for (int i = 0; i < q; ++i) cin >> c[i];

        for (int i = 0; i < q; ++i) {
            int u = b[i], v = c[i];
            if (out[u] != 0 || in[v] != 0) {
                conflict = true;
                break;
            }
            out[u] = v;
            in[v] = u;
        }

        if (conflict) {
            cout << "0\n";
            continue;
        }

        // m = количество вершин без входящих заданных рёбер (начала цепей)
        int m = 0;
        for (int i = 1; i <= n; ++i) {
            if (in[i] == 0) {
                m++;
            }
        }

        vector<bool> visited(n + 1, false);
        for (int i = 1; i <= n; ++i) {
            if (in[i] == 0) {
                int cur = i;
                while (cur != 0 && !visited[cur]) {
                    visited[cur] = true;
                    cur = out[cur];
                }
            }
        }

        int k0 = 0;
        for (int i = 1; i <= n; ++i) {
            if (!visited[i] && out[i] != 0) {
                int cur = i;
                while (!visited[cur]) {
                    visited[cur] = true;
                    cur = out[cur];
                }
                k0++;
            }
        }

        int L = max(0, l - k0);
        int R = min(m, r - k0);
        if (L > R) {
            cout << "0\n";
            continue;
        }

        long long ans = 0;
        for (int c = L; c <= R; ++c) {
            ans = (ans + dp[m][c]) % MOD;
        }
        cout << ans << "\n";
    }

    return 0;
}