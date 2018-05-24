#include "LinerSort.h"

using std::vector;

namespace {

void InsertSort(vector<double> &A, double t) {
    vector<double>::iterator it = A.begin();
    while(it != A.end() && *it <= t) it++;
    A.insert(it, t);
}

}

// 带排序数据A中元素的取值范围为(0,1)双开区间
void BucketSort(vector<double> &A) {
    int n = A.size();
    vector<double> bucket[n];
    for(int i = 0; i < n; i++) {
        int t = A[i] * n;
        InsertSort(bucket[t], A[i]);
    }
    int now = 0;
    for(int i = 0; i < n; i++)
        for(size_t j = 0; j < bucket[i].size(); j++)
            A[now++] = bucket[i][j];
}
