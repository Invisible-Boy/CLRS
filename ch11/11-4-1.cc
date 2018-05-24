#include <iostream>
#include <cstring>

using namespace std;

int myhash(int k, int i, int t) {
    if(t == 0) return (k + i) % 11;
    if(t == 1) return (k + i + 3 * i * i) % 11;
    return (k + i * (1 + k % 10)) % 11;
}

int main() {
    int num[11], aim[100], n;
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> aim[i];
    for(int t = 0; t < 3; t++) {
        memset(num, 0, sizeof(num));
        for(int i = 0; i < n; i++) {
            int step = 1, index = myhash(aim[i], 0, t);
            while(num[index] != 0 && step < 11)
                index = myhash(aim[i], step++, t);
            num[index] = aim[i];
        }
        for(int i = 0; i < 11; i++)
            cout << num[i] << '\t';
        cout << endl;
    }
    return 0;
}
