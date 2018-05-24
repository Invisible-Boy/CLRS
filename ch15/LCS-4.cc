/**
 * Title:   Longest Common Subsequence
 * Author:  InvisibleMan
 * Date:    2017-10-20
 * Remark:  Trans LCS to LIS
 *          当元素映射有重复元素时，按照降序填充
 *          如 A{a, b, c, a, d} B{a, b, c, d}
 *          loc[a] = {1, 4} loc[b] = {2} loc[c] = {3} loc[d] = {5}
 *          则映射后的B为{4, 1, 2, 3, 5}
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int iNmax = 1024;

inline int find(int ans[], int size, int now) {
    int p = 0, q = size;
    while(p < q) {
        int mid = (p + q) >> 1;
        if(now <= ans[mid])
            q = mid;
        else
            p = mid + 1;
    }
    return q;
}

int main() {
    string str1, str2;
    int ans[iNmax];
    while(cin >> str1 >> str2) {
        vector<int> mp[256];
        vector<int> data;
        for(int i = 0; i < (int)str1.length(); i++)
            mp[(int)str1[i]].push_back(i);
        for(int i = 0; i < (int)str2.length(); i++) {
            int now = str2[i], len = mp[now].size();
            if(len)
                for(int j = len - 1; j > -1; j--)
                    data.push_back(mp[now][j]);
        }
        if(data.size() < 1) {
            cout << 0 << endl;
            continue;
        }
        int size = 1;
        ans[0] = data[0];
        for(int i = 1; i < (int)data.size(); i++) {
            if(data[i] > ans[size - 1])
                ans[size++] = data[i];
            else {
                int temp = find(ans, size, data[i]);
                ans[temp] = data[i];
            }
        }
        cout << size << endl;
    }
    return 0;
}
