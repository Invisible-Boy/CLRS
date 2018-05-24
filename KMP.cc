/**
 * Title:   KMP-Algorithm
 * Author:  InvisibleMan
 * Date:    2017-5-26
 */

#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    string s1, s2;
    while(cin >> s1 >> s2) {
        int n = s1.length(), m = s2.length();
        if(n < m) cout << -1;
        else if(m == 0) cout << 0;
        else {
            vector<int> pi(m, 0);
            int k = 0;
            for(int i = 2; i <= m; i++) {
                while(k > 0 && s2[i - 1] != s2[k])
                    k = pi[k];
                if(s2[i - 1] == s2[k])
                    k++;
                pi[i] = k;
            }
            k = 0;
            for(int i = 0; i < n && k < m; i++) {
                while(k > 0 && s1[i] != s2[k])
                    k = pi[k];
                if(s1[i] == s2[k])
                    k++;
                if(k == m)
                    cout << i - m + 1 << endl;
            }
            if(k < m) cout << -1 << endl;
        }
    }
    return 0;
}
