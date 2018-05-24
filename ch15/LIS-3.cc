/**
 * Title:   LIS-3 POJ2533
 * Author:  InvisibleMan
 * Date:    2017-10-20
 * Remark:  O(nlg(n))
 */

#include <iostream>

using namespace std;

const int iNmax = 1024;

inline int find(int data[], int size, int now) {
    int p = 0, q = size;
    while(q > p) {
        int mid = (p + q) >> 1;
        if(data[mid] >= now)
            q = mid;
        else
            p = mid + 1;
    }
    return q;
}

int main() {
    int data[iNmax], N;
    while(cin >> N) {
        cin >> data[0];
        int size = 1;
        for(int i = 1; i < N; i++) {
            int t;
            cin >> t;
            if(t < data[0]) data[0] = t;
            else if(t > data[size - 1]) data[size++] = t;
            else {
                int temp = find(data, size, t);
                data[temp] = t;
            }
        }
        cout << size << endl;
    }
    return 0;
}
