/*
    Problem: Magic Numbers (CF-628D)
    Topic: Digit DP

*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll dp[2020][2][2020][2][2];

vector<int> NumberSequence;
void createSequence(string X) {
    NumberSequence.clear();
    for (char c : X) {
        NumberSequence.push_back(c - '0');
    }
}
int M, D;
const int mod = 1e9 + 7;
ll call(int pos, int is_small, int remainder, int is_start, int is_odd) {
    if (pos == NumberSequence.size()) {
        return remainder == 0;
    }
    ll &ret = dp[pos][is_small][remainder][is_start][is_odd];
    if (ret != -1) return ret;
    int limit = 9;
    if (is_small == false) limit = NumberSequence[pos];

    ret = 0;
    if (is_odd) {
        if (is_small == 0 && D > limit) return ret = 0;
        ret = call(pos + 1, is_small | D < limit, (remainder * 10 + D) % M,
                   is_start, 1 - is_odd);
        ret %= mod;
        return ret;
    }
    for (int i = 1; i <= limit; i++) {
        if (i == D) continue;
        ret += call(pos + 1, is_small | i < limit, (remainder * 10 + i) % M, 0,
                    1 - is_odd);
        ret %= mod;
    }
    if (is_start)
        ret += call(pos + 1, 1, 0, 1, 0);
    else if (D != 0)
        ret += call(pos + 1, is_small | limit > 0, (remainder * 10) % M, 0,
                    1 - is_odd);
    ret %= mod;
    return ret;
}
ll solve(string X) {
    createSequence(X);
    memset(dp, -1, sizeof dp);
    return call(0, 0, 0, 1, 0);
}

int main() {
    string a, b;
    cin >> M >> D >> a >> b;
    for (int i = a.size() - 1; i >= 0; i--) {
        if (a[i] != '0') {
            a[i]--;
            break;
        }
        a[i] = '9';
    }

    if (a[0] == '0') a.erase(a.begin());
    ll ans = solve(b) - solve(a);
    ans = (ans + mod) % mod;
    printf("%lld\n", ans);
}
