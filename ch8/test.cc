#include <iostream>
#include "LinerSort.h"

using namespace std;

template <typename T>
inline void Print(vector<T> &A) {
    if(A.size() == 0) return;
    cout << A[0];
    for(size_t i = 1; i < A.size(); i++)
        cout << ' ' << A[i];
    cout << endl;
}

int main() {
    vector<int> A1;
    for(int i = 9; i > -1; i--) {
        A1.push_back(i);
        A1.push_back(i);
    }
    vector<int> B1(A1);
    CountingSort(A1, B1, 10);
    cout << "Before CountingSort the vector is:" << endl << '\t';
    Print(A1);
    cout << "After CountingSort the vector is:" << endl << '\t';
    Print(B1);

    vector<int> A2;
    for(int i = 19; i > -1; i -= 2)
        A2.push_back(i);
    cout << "Before RadixSort the vector is:" << endl << '\t';
    Print(A2);
    RadixSort(A2, 2);
    cout << "After RadixSort the vector is:" << endl << '\t';
    Print(A2);

    vector<double> A3;
    for(int i = 10; i > -1; i--)
        A3.push_back(i / 11.0);
    cout << "Before BucketSort the vector is:" << endl << '\t';
    Print(A3);
    BucketSort(A3);
    cout << "After BucketSort the vector is:" << endl << '\t';
    Print(A3);
    return 0;
}
