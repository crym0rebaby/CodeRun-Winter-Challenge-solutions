#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
const int mod = (int)1e9+7;
using ll = long long;
void solve() {
    ll M; int n;
    std::cin >> M >> n;
    std::vector<ll> w(n);
    for (auto &it : w)
        std::cin >> it;
    w.push_back(0);
    std::sort(all(w));
    n++;
    std::vector<ll> add(n+1);
    for (int i = n-1; i >= 1; i--) {
        ll delta = w[i] - w[i-1];
        ll cnt = (n - i);
        if (M >= delta * cnt) {
            add[i] -= delta;
            M -= delta * cnt;
        } else {
            delta = M / cnt;
            ll rem = M % cnt;
            add[i] -= delta;
            add[i] -= 1;
            add[i+rem] += 1;
            break;
        }
    }
    ll answ = 0;
    for (int i = 1; i < isz(w); i++) {
        add[i] += add[i-1];
        w[i] += add[i];
        w[i] %= mod;
        (answ += w[i] * w[i]) %= mod;
    }
    std::cout << answ << std::endl;
}

int main() {
    solve();
}
