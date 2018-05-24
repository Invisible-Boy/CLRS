#include "LinerSort.h"

using std::vector;

namespace {

void m_CountingSort(vector<int> &A, vector<int> &B, int base) {
    vector<int> S(10, 0);
    for(size_t i = 0; i < A.size(); i++) {
        int t = (A[i] / base) % 10;
        S[t]++;
    }
    for(int i = 1; i < 10; i++)
        S[i] += S[i - 1];
    for(int i = A.size() - 1; i > -1; i--) {
        int t = (A[i] / base) % 10;
        B[--S[t]] = A[i];
    }
}

}

void RadixSort(vector<int> &A, int d) {
    int base = 1;
    vector<int> B(A);
    while(d--) {
        if(d & 1)
            m_CountingSort(A, B, base);
        else
            m_CountingSort(B, A, base);
        base *= 10;
    }
}
