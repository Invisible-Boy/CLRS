/**
 * Title:   Longest common subsequence
 * Author:  InvisibleMan
 * Date:    2017-10-19
 * Remark:  15.4-2, 空间复杂度O(nm)
 */

#include <iostream>
#include <string>

using namespace std;

const int iNmax = 1024;

int c[iNmax][iNmax];

inline int LCS(string &str1, string &str2) {
    int n = str1.length(), m = str2.length();
    for(int i = 0; i < n; i++)
        c[i][0] = 0;
    for(int i = 0; i < m; i++)
        c[0][i] = 0;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) {
            int &ans = c[i][j];
            if(str1[i - 1] == str2[j - 1])
                ans = c[i - 1][j - 1] + 1;
            else
                ans = max(c[i - 1][j], c[i][j - 1]);
        }
    return c[n][m];
}

void printLCS(int p, int q, string &str1, string &str2) {
    if(p == 0 || q == 0 || c[p][q] == 0) return;
    if(c[p][q] == c[p - 1][q - 1] + 1) {
        printLCS(p - 1, q - 1, str1, str2);
        cout << str1[p - 1] << ' ';
    }
    else if(c[p][q] == c[p - 1][q])
        printLCS(p - 1, q, str1, str2);
    else if(c[p][q] == c[p][q - 1])
        printLCS(p, q - 1, str1, str2);
}

int main() {
    string str1, str2;
    cin >> str1 >> str2;
    cout << LCS(str1, str2) << endl;
    printLCS(str1.length(), str2.length(), str1, str2);
    return 0;
}
