#include <iostream>

using namespace std;

template <typename T>
inline void swp(T &t1, T &t2) {
    T t = t1;
    t1 = t2;
    t2 = t;
}

template <typename T>
int QuickPartion1(T vec[], int p, int q) {
    int pp = p, x = vec[q];
    for(int i = p; i < q; i++) {
        if(vec[i] <= x)
            swp(vec[pp++], vec[i]);
    }
    swp(vec[pp], vec[q]);
    return pp;
}

template <typename T>
int QuickPartion2(T vec[], int p, int q) {
    int key = vec[p];
    while(q > p) {
        while(q > p && vec[q] >= key)
            --q;
        vec[p] = vec[q];
        while(q > p && vec[p] <= key)
            ++p;
        vec[q] = vec[p];
    }
    vec[p] = key;
    return p;
}

template <typename T>
int QuickPartion3(T vec[], int p, int q) {
    int pp = p;
    while(p < q) {
        while(p < q && vec[q] >= vec[pp])
            --q;
        while(p < q && vec[p] < vec[pp])
            ++p;
        swp(vec[p], vec[q]);
    }
    swp(vec[p], vec[pp]);
    return p;
}

template <typename T>
int QuickPartion4(T vec[], int p, int q) {
    int pp = p;
    while(p < q) {
        while(q > p && vec[q] >= vec[pp])
            --q;
        while(q > p && vec[p] < vec[pp])
            ++p;
        swp(vec[p], vec[q]);
    }
    return q;
}

template <typename T>
void QuickSort(T vec[], int p, int q) {
    if(p < q) {
        int mid = QuickPartion1(vec, p, q - 1);
        QuickSort(vec, p, mid);
        QuickSort(vec, mid + 1, q);
    /* version 4 is error for q - p == 1
    if(q - p > 1) {
        int mid = QuickPartion4(vec, p, q - 1);
        QuickSort(vec, p, mid + 1);
        QuickSort(vec, mid + 1, q);
    */
    }
}

int main() {
    int vec[] = {5, 5, 4, 4, 3, 3, 2, 2, 1, 1};
    QuickSort(vec, 0, 10);
    for(int i = 0; i < 10; i++)
        cout << vec[i] << endl;
    return 0;
}
