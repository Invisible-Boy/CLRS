#include "./include/AVLTree.h"
#include "./include/testTool.h"
#include "./include/RBTree.h"
#include <cstdlib>
#include <time.h>
#include <iostream>

using namespace std;
using namespace binaryTree;
using namespace testTool;

int main() {
    srand(time(NULL));
    int n;
    cin >> n;
    int p;
    cin >> p;
    //AVLTree<int> avl;
    RBTree<int> avl;
    for(int i = 0; i < n; i++) {
        int now = rand() % 100 + 1;
        int t = rand() % 100;
        if(now <= p)
            avl.Insert(t);
        else
            avl.Delete(t);
        bool flag = true;
        //IsAVLTree(avl.Root(), flag);
        IsRBTree(avl.Root(), flag);
        if(!flag) {
            cout << "some error happened" << endl;
            Print(avl.Root());
            return -1;
        }
    }
    cout << "test passed" << endl;
    return 0;
}
