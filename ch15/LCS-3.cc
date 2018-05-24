/**
 * Title:   Longest Common Subsequence
 * Author:  InvisibleMan
 * Date:    2017-10-19
 * Remark:  递归备忘
 */

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

const int iNmax = 1024;

int c[iNmax][iNmax], vis[iNmax][iNmax] = {0}, now = 1;
string str1, str2;

int dp(int p, int q) {
    int &ans = c[p][q], &v = vis[p][q];
    if(v == now)
        return ans;
    v = now;
    if(p == 0 || q == 0)
        return ans = 0;
    if(str1[p - 1] == str2[q - 1])
        return ans = dp(p - 1, q - 1) + 1;
    return ans = max(dp(p - 1, q), dp(p, q - 1));
}

int main() {
    while(cin >> str1 >> str2) {
        int n = str1.length(), m = str2.length();
        cout << dp(n, m) << endl;
        ++now;
    }
    return 0;
}
