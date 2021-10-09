/*
    Problem: How Many Zeroes? (LightOJ-1140)
    Topic: Digit DP
    
*/
#include <bits/stdc++.h>
using namespace std;

long long dp[10][2][2][10];

vector<int> NumberSequence;
void createSequence(long long n) {
    NumberSequence.clear();
    while (n) {
        NumberSequence.push_back(n % 10);
        n /= 10;
    }
    reverse(NumberSequence.begin(), NumberSequence.end());
}
long long call(int pos, int is_small, int is_start, int zeroCount) {
    if (pos == NumberSequence.size()) {
        return zeroCount;
    }
    long long &ret = dp[pos][is_small][is_start][zeroCount];
    if (ret != -1) return ret;
    int limit = 9;
    if (is_small == false) limit = NumberSequence[pos];

    ret = 0;
    for (int i = 1; i <= limit; i++) {
        ret += call(pos + 1, is_small | i < limit, 0,zeroCount);
    }
    if(is_start) ret+=call(pos+1,1,1,0);
    else ret+=call(pos+1,is_small|0<limit,0,zeroCount+1);
    return ret;
}
long long solve(long long X) {
    if (X<10) return X>=0;
    createSequence(X);
    memset(dp, -1, sizeof dp);
    return 1+call(0, 0, 1, 0);
}

int main() {
    int t;
    scanf("%d", &t);
    for (int ks = 1; ks <= t; ks++) {
        long long a, b;
        scanf("%lld%lld", &a, &b);
        long long ans = solve(b) - solve(a - 1);
        printf("Case %d: %lld\n", ks, ans);
    }
}
