#include "./include/AVLTree.h"
#include "./include/RBTree.h"
#include "./include/testTool.h"
#include <iostream>

using namespace binaryTree;
using namespace testTool;
using std::cin;

int main() {
    AVLTree<int> avltree;
    RBTree<int> rbtree;
    while(1) {
        cout << "Please input insert, delete or quit!\n>>> ";
        string op;
        cin >> op;
        if(op == "quit") return 0;
        if(op == "insert") {
            cout << "Please input the number of insert:\n>>> ";
            int n;
            cin >> n;
            cout << "Please input " << n << " objects:\n>>> ";
            while(n--) {
                int t;
                cin >> t;
                //avltree.Insert(t);
                rbtree.Insert(t);
            }
        }
        else if(op == "delete") {
            cout << "Please input the object that you want to delete:\n>>> ";
            int t;
            cin >> t;
            rbtree.Delete(t);
        }
        else {
            cout << "Invalid operation!" << endl;
            continue;
        }
        cout << "After " << op << " the tree is:" << endl << endl;
        //Print(avltree.Root());
        Print(rbtree.Root());
    }
    return 0;
}
