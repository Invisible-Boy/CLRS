/**
 * Title:   HDU1003
 * Author:  InvisibleMan
 * Data:    2016-1-11
 * Time:    TLE
 */

// tips: 采用分治策略

#include <cstdio>

using namespace std;

const int Nmax = 100001;
int num, data[Nmax];

void judge(int ans[3], int tAns[3]) {
    if(tAns[0] > ans[0] ||
      (tAns[0] == ans[0] && tAns[1] < ans[1]) ||
      (tAns[0] == ans[0] && tAns[1] == ans[1] && tAns[2] < ans[2])) {
        ans[0] = tAns[0];
        ans[1] = tAns[1];
        ans[2] = tAns[2];
    }
}

bool myfind(int p, int q, int ans[3]) {
    if(p > q) return false;
    int mid = (p + q) >> 1;
    int tAns[3];
    tAns[0] = -1000000001;
    if(myfind(p, mid - 1, tAns))
        judge(ans, tAns);
    tAns[0] = -1000000001;
    if(myfind(mid + 1, q, tAns))
        judge(ans, tAns);
    tAns[0] = data[mid];
    tAns[1] = tAns[2] = mid;
    int tt = data[mid];
    for(int j = mid - 1; j > -1; j--) {
        tt += data[j];
        if(tt >= tAns[0]) {
            tAns[0] = tt;
            tAns[1] = j;
        }
    }
    tt = tAns[0];
    for(int j = mid + 1; j <= q; j++) {
        tt += data[j];
        if(tt > tAns[0]) {
            tAns[0] = tt;
            tAns[2] = j;
        }
    }
    judge(ans, tAns);
    return true;
}

int main() {
    int T, ans[3];
    scanf("%d", &T);
    for(int i = 0; i < T; ) {
        ans[0] = -1000000001;
        if(i) printf("\n");
        scanf("%d", &num);
        for(int j = 0; j < num; j++)
            scanf("%d", &data[j]);
        myfind(0, num - 1, ans);
        printf("Case %d:\n%d %d %d\n", ++i, ans[0], ans[1] + 1, ans[2] + 1);
    }
    return 0;
}
