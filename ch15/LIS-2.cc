/**
 * Title:   LIS-2 POJ2533
 * Author:  InvisibleMan
 * Date:    2017-10-20
 * Remark:  DP(O(n^2))
 */
#include <iostream>

using namespace std;

int N, str[1024], c[1024];

inline int dp() {
    for(int i = 0; i < N; i++)
        c[i] = 1;
    int ans = 1;
    for(int i = 1; i < N; i++) {
        for(int j = i - 1; j > -1; j--) {
            if(str[i] > str[j] && c[j] + 1 > c[i])
                c[i] = c[j] + 1;
        }
        if(c[i] > ans)
            ans = c[i];
    }
    return ans;
}

int main() {
    while(cin >> N) {
        for(int i = 0; i < N; i++)
            cin >> str[i];
        cout << dp() << endl;
    }
    return 0;
}
