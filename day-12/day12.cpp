#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int SZ = 100; // 10*10

using Matrix = array<array<int, SZ>, SZ>;
using Vector = array<int, SZ>;

Matrix mul(const Matrix &A, const Matrix &B) {
    Matrix C;
    for (int i = 0; i < SZ; ++i) {
        for (int j = 0; j < SZ; ++j) {
            long long sum = 0;
            for (int k = 0; k < SZ; ++k) {
                sum += (long long)A[i][k] * B[k][j];
                if (sum >= (1LL<<62)) sum %= MOD; // чтобы избежать переполнения
            }
            C[i][j] = sum % MOD;
        }
    }
    return C;
}

Vector mul(const Vector &v, const Matrix &A) {
    Vector res;
    for (int j = 0; j < SZ; ++j) {
        long long sum = 0;
        for (int i = 0; i < SZ; ++i) {
            sum += (long long)v[i] * A[i][j];
            if (sum >= (1LL<<62)) sum %= MOD;
        }
        res[j] = sum % MOD;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    int m;
    cin >> n >> m;
    vector<bool> good(28, false);
    for (int i = 0; i < m; ++i) {
        int x;
        cin >> x;
        good[x] = true;
    }

    Matrix A{};
    for (int a = 0; a < 10; ++a) {
        for (int b = 0; b < 10; ++b) {
            int from = a * 10 + b;
            for (int c = 0; c < 10; ++c) {
                if (good[a + b + c]) {
                    int to = b * 10 + c;
                    A[from][to] = (A[from][to] + 1) % MOD;
                }
            }
        }
    }

    Vector v{};
    for (int a = 1; a < 10; ++a) {
        for (int b = 0; b < 10; ++b) {
            int id = a * 10 + b;
            v[id] = 1;
        }
    }

    long long power = n - 2;
    Matrix curA = A;
    Vector res = v;
    while (power > 0) {
        if (power & 1) {
            res = mul(res, curA);
        }
        curA = mul(curA, curA);
        power >>= 1;
    }

    long long ans = 0;
    for (int i = 0; i < SZ; ++i) {
        ans += res[i];
        if (ans >= MOD) ans -= MOD;
    }
    cout << ans << "\n";

    return 0;
}