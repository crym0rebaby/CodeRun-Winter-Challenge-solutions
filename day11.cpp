#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> inv(n + 1);
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) {
        inv[i] = MOD - (MOD / i) * 1LL * inv[MOD % i] % MOD;
    }

    long long current_D = 1;
    long long ans = current_D;
    for (int k = n - 1; k >= 1; --k) {
        current_D = (n + (n - k) * current_D) % MOD;
        current_D = current_D * inv[k] % MOD;
        ans = (ans + current_D) % MOD;
    }

    cout << ans << "\n";
    return 0;
}