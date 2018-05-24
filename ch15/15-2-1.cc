#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;
void dfs(vector<int> &p, vector<vector<int> > &dp, vector<vector<int> > &sta) {
   int n = dp.size() - 1;
   for(int l = 2; l <= n; l++) {
        for(int i = 0; i < n - l + 1; i++) {
            int j = i + l;
            int &ans = dp[i][j];
            ans = INF;
            for(int k = i + 1; k < j; k++) {
                int tAns = dp[i][k] + dp[k][j] + p[i] * p[k] * p[j];
                if(tAns < ans) {
                    ans = tAns;
                    sta[i][j] = k;
                }
            }
        }
   }
}

int main() {
    vector<int> p;
    int n, t;
    cin >> n;
    for(int i = 0; i < n + 1; i++) {
        cin >> t;
        p.push_back(t);
    }
    // sta, dp为[i, j)的最小值
    vector<vector<int> > dp(n + 1, vector<int>(n + 1, 0));
    vector<vector<int> > sta = dp;
    dfs(p, dp, sta);
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++)
            cout << dp[i][j] << '\t';
        cout << endl;
    }
    return 0;
}
