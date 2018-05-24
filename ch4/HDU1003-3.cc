/**
 * Title:   HDU1003-3
 * Author:  InvisibleMan
 * Date:    2017-3-8
 * Time:    ms
 */

#include <cstdio>

using namespace std;

int main() {
    int T, n, t;
    scanf("%d", &T);
    for(int i = 1; i <= T; i++) {
        scanf("%d", &n);
        int ans = -1001, Smin = 0, sum = 0, tAnsI = 1, ansI, ansJ;
        for(int j = 1; j <= n; j++) {
            scanf("%d", &t);
            sum += t;
            if(sum - Smin > ans) {
                ans = sum - Smin;
                ansI = tAnsI, ansJ = j;
            }
            if(sum < Smin) {
                Smin = sum;
                tAnsI = j + 1;
            }
        }
        printf("Case %d:\n%d %d %d\n", i, ans, ansI, ansJ);
        if(i < T) printf("\n");
    }
    return 0;
}
