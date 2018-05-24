/**
 * Title:   HDU1003-2
 * Author:  InvisibleMan
 * Data:    2016-1-11
 * Time:    46ms
 */

#include <cstdio>
int main() {
    int T;
    scanf("%d", &T);
    for(int i = 0; i < T; ) {
        if(i) printf("\n");
        int num, temp;
        int ans[3] = {0};
        int tAns[2] = {0};
        scanf("%d", &num);
        for(int j = 0; j < num; j++) {
            scanf("%d", &temp);
            if(tAns[0] < 0) {
                tAns[0] = temp;
                tAns[1] = j;
            }
            else tAns[0] += temp;
            if(tAns[0] > ans[0] || !j) {
                ans[0] = tAns[0];
                ans[1] = tAns[1];
                ans[2] = j;
            }
        }
        printf("Case %d:\n%d %d %d\n", ++i, ans[0], ans[1] + 1, ans[2] + 1);
    }
    return 0;
}
