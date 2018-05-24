#include "LinerSort.h"

using std::vector;

void CountingSort(vector<int> &A, vector<int> &B, int k) {
    vector<int> S(k, 0);
    for(size_t i = 0; i < A.size(); i++) {
        int t = A[i];
        if(t >= k)
            throw("Error: in CountingSort k is too small!");
        S[t]++;
    }
    for(int i = 1; i < k; i++)
        S[i] += S[i - 1];
    for(int i = A.size() - 1; i > -1; i--) {
        int t = A[i];
        B[--S[t]] = t;
    }
}
