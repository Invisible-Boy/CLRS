/**
 * Title:   LIS POJ2533
 * Author:  InvisibleMan
 * Date:    2017-10-20
 * Remark:  Trans LIS to LCS O(n^2)
 */

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int iNmax = 1024;

int N, str1[iNmax], str2[iNmax], c[iNmax];

inline int dp(int M) {
    for(int i = 0; i <= M; i++)
        c[i] = 0;
    for(int i = 1; i <= N; i++) {
        for(int j = M; j > 0; j--)
            if(str1[i - 1] == str2[j - 1])
                c[j] = c[j - 1] + 1;
        for(int j = 1; j <= M; j++)
            if(str1[i - 1] != str2[j - 1])
                c[j] = max(c[j - 1], c[j]);
    }
    return c[M];
}

int main() {
    while(cin >> N) {
        for(int i = 0; i < N; i++)
            cin >> str1[i];
        memcpy(str2, str1, sizeof(int) * N);
        sort(str2, str2 + N);
        int M = unique(str2, str2 + N) - str2;
        cout << dp(M) << endl;
    }
    return 0;
}
