/**
 * Title:   Print Optimal BST(15.5-1)
 * Author:  InvisibleMan
 * Date:    2017-10-22
 */

#include <iostream>

using namespace std;

const int iNmax = 1024;
const double INF = 1e10;

double dp[iNmax], dq[iNmax], dval[iNmax][iNmax], dwei[iNmax][iNmax];
int root[iNmax][iNmax];

void OptimalBst(int p, int q) {
    for(int i = p; i <= q + 1; i++) {
        dwei[i][i - 1] = dq[i - 1];
        dval[i][i - 1] = dq[i - 1];
    }
    for(int len = 1; len <= q - p + 1; len++) {
        for(int i = p; i <= q - len + 1; i++) {
            int j = i + len - 1;
            dwei[i][j] = dwei[i][j - 1] + dq[j] + dp[j];
            dval[i][j] = INF;
            for(int k = i; k <= j; k++) {
                double t = dval[i][k - 1] + dval[k + 1][j] + dwei[i][j];
                if(t < dval[i][j] - 1e-3) {
                    dval[i][j] = t;
                    root[i][j] = k;
                }
            }
        }
    }
}

void PrintBst(int p, int q) {
    int r = root[p][q];
    if(r - 1 >= p) {
        int rr = root[p][r - 1];
        cout << "K" << rr << " 为 " << "K" << r << " 的左孩子" << endl;
        PrintBst(p, r - 1);
    }
    else
        cout << "D" << r - 1 << " 为 " << "K" << r << " 的左孩子" << endl;
    if(q >= r + 1) {
        int rr = root[r + 1][q];
        cout << "K" << rr << " 为 " << "K" << r << " 的右孩子" << endl;
        PrintBst(r + 1, q);
    }
    else 
        cout << "D" << q << " 为 " << "K" << r << " 的右孩子" << endl;
}

int main() {
    int N;
    cin >> N;
    for(int i = 1; i <= N; i++)
        cin >> dp[i];
    for(int i = 0; i <= N; i++)
        cin >> dq[i];
    OptimalBst(1, N);
    cout << "K"<< root[1][N] << "为根" << endl;
    PrintBst(1, N);
    cout << "总代价为：" << dval[1][N] << endl;
    return 0;
}
