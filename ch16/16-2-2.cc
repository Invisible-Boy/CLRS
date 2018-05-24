#include <iostream>
#include <vector>

using namespace std;

int max(int t1, int t2) {
    return t1 > t2 ? t1 : t2;
}

int main() {
    int W, N;
    cin >> W >> N;
    vector<int> dp(W + 1, 0);
    for(int i = 0; i < N; i++) {
        int w1, v1;
        cin >> w1 >> v1;
        for(int j = W; j >= 0; j--)
            if(j >= w1)
                dp[j] = max(dp[j], dp[j - w1] + v1);
    }
    cout << dp[W] << endl;
    return 0;
}
