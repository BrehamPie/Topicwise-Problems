#include <bits/stdc++.h>
using namespace std;

int dp[10][2][90][90];

vector<int> NumberSequence;
void createSequence(int n) {
    NumberSequence.clear();
    while (n) {
        NumberSequence.push_back(n % 10);
        n /= 10;
    }
    reverse(NumberSequence.begin(), NumberSequence.end());
}
int K;
int call(int pos, int is_small, int remainder, int sumOfDigitRemainder) {
    if (pos == NumberSequence.size()) {
        return remainder == 0 && sumOfDigitRemainder == 0;
    }
    int &ret = dp[pos][is_small][remainder][sumOfDigitRemainder];
    if (ret != -1) return ret;
    int limit = 9;
    if (is_small == false) limit = NumberSequence[pos];

    ret = 0;
    for (int i = 0; i <= limit; i++) {
        ret += call(pos + 1, is_small | i < limit, (remainder * 10 + i) % K,
                    (sumOfDigitRemainder + i) % K);
    }
    return ret;
}
int solve(int X) {
    if (K > 81) return 0;
    createSequence(X);
    memset(dp, -1, sizeof dp);
    return call(0, 0, 0, 0);
}

int main() {
    int t;
    scanf("%d", &t);
    for (int ks = 1; ks <= t; ks++) {
        int a, b;
        scanf("%d%d%d", &a, &b, &K);
        int ans = solve(b) - solve(a - 1);
        printf("Case %d: %d\n", ks, ans);
    }
}
