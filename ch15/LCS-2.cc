/**
 * Title:   Longest common subsequence
 * Author:  InvisibleMan
 * Date:    2017-10-19
 * Remark:  15.4-4
 */

#include <iostream>
#include <string>

using namespace std;

const int iNmax = 1024;

int c[iNmax];

inline int LCS(string &str1, string &str2) {
    int n = str1.length(), m = str2.length();
    for(int i = 0; i <= m; i++)
        c[i] = 0;
    for(int i = 1; i <= n; i++) {
        // dp[i][j] = dp[i - 1][j - 1] + 1            if str1[i] == str2[j]
        for(int j = m; j > 0; j--) {
            int &ans = c[j];
            if(str1[i - 1] == str2[j - 1])
                ans = c[j - 1] + 1;
        }
        // dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) if str1[i] != str2[j]
        for(int j = 1; j <= m; j++) {
            int &ans = c[j];
            if(str1[i - 1] != str2[j - 1])
                ans = max(c[j - 1], ans);
        }
    }
    return c[m];
}

int main() {
    string str1, str2;
    while(cin >> str1 >> str2) 
        cout << LCS(str1, str2) << endl;
    return 0;
}
