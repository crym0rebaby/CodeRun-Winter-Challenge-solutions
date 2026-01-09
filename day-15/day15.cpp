#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using vi = std::vector<int>;
using vvi = std::vector<vi>;
const int mod = 998244353;
void addto(int &a, int b) {
    a += b;
    if (a >= mod)
        a -= mod;
}
int mul(int a, int b) {
    return int(a * 1LL * b % mod);
}
void solve() {
    std::string s, t; std::cin >> s >> t;
    vi powerOfTwo(isz(s)+1, 1);
    for (int i = 1; i <= isz(s); i++)
        powerOfTwo[i] = mul(powerOfTwo[i-1], 2);
    vvi sameLen(isz(s)+1, vi(isz(t)+1));
    for (int i = isz(s)-1; i >= 0; i--)
        for (int j = isz(t)-1; j >= 0; j--)
            if (s[i] == t[j])
                sameLen[i][j] = 1 + sameLen[i+1][j+1];
    std::vector count(isz(t)+1, std::vector<int>(isz(s)+1));
    std::vector visited(isz(t)+1, std::vector<bool>(isz(s)+1));
    std::function<int(int,int)> calc = [&](int startT, int lenS) -> int {
        if (lenS == 0) {
            return isz(t) - startT;
        }
        const int i = startT;
        if (i >= isz(t))
            return 0;
        if (visited[i][lenS])
            return count[i][lenS];
        visited[i][lenS] = true;
        int result = 0;
        for (int len = 1; len <= lenS; len++) {
            int j = lenS - len;
            assert(0 <= i && i < isz(t));
            int same = sameLen[j][i];
            if (same >= len) { 
                addto(result, calc(i+len, lenS-len));
            } else {
                int lastPosT = i + same, lastPosS = j + same;
                if (lastPosT >= isz(t))
                    continue;
                if (lastPosS == lenS) {
                    result += isz(t) - lastPosT;
                    continue;
                }
                assert(lastPosS < lenS);
                if (s[lastPosS] > t[lastPosT])
                    continue;
                int cntWaysT = isz(t)-lastPosT;
                int cntWaysS = 1;
                if (int prefixLen = lenS-len; prefixLen >= 1)
                    cntWaysS = powerOfTwo[prefixLen-1];
                addto(result, mul(cntWaysS, cntWaysT));
            }
        }
        return count[i][lenS] = result;
    };
    int answ{};
    for (int i = 0; i < isz(t); i++)
        addto(answ, calc(i, isz(s)));
    std::cout << answ << std::endl;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}