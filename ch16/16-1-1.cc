#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> Pair;

bool cmp(Pair &t1, Pair &t2) {
    return t1.second < t2.second;
}

void Print(int p, int q, vector<vector<int> > &vNext) {
    if(vNext[p][q] < 0) return;
    cout << vNext[p][q] << '\t';
    Print(p, vNext[p][q], vNext);
    Print(vNext[p][q], q, vNext);
}

inline int Greedy(vector<Pair> &vEvent) {
    int N = vEvent.size() - 1;
    int ans = 0, end = -1;
    for(int i = 1; i < N; i++)
        if(vEvent[i].first >= end) {
            ++ans;
            end = vEvent[i].second;
            cout << i << '\t';
        }
    cout << endl;
    return ans;
}

int main() {
    vector<Pair> vEvent;
    int tp, tq;
    // vEvent[0]为哨兵
    vEvent.push_back(Pair(1e9, -1));
    while(cin >> tp >> tq)
        vEvent.push_back(Pair(tp, tq));
    sort(vEvent.begin(), vEvent.end(), cmp);
    // vEvent[N - 1]同样为哨兵
    vEvent.push_back(Pair(1e9, 1e9));
    const int N = vEvent.size();
    // 区间为开区间
    vector<vector<int> > vVal(N, vector<int>(N, 0));
    vector<vector<int> > vNext(N, vector<int>(N, -1));
    for(int len = 2; len < N; len++) {
        for(int i = 0; i < N - len; i++) {
            int j = i + len;
            int &ans = vVal[i][j];
            int &next = vNext[i][j];
            for(int k = i + 1; k < j; k++) {
                if(vEvent[k].first >= vEvent[i].second && vEvent[k].second <= vEvent[j].first) {
                    int t = vVal[i][k] + vVal[k][j] + 1;
                    if(t > ans) {
                        ans = t;
                        next = k;
                    }
                }
            }
        }
    }
    cout << vVal[0][N - 1] << endl;
    Print(0, N - 1, vNext);
    cout << endl;
    
    cout << Greedy(vEvent) << endl;
    return 0;
}
