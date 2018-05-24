/**
 * Title:   Binary Search Tree Test
 * Author:  InvisibleMan
 * Time:    2017-6-2
 */

#include "binary-search-tree.h"

using namespace std;

int main() {
    BSTree tree;
    int n, t;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> t;
        tree.insert(t);
    }
    cout << "The tree is:" << endl;
    tree.print(tree.T);
    
    Node *min = tree.findMin(tree.T);
    for(int i = 0; i < n; i++) {
        cout << "\nThe " << i << "th small value is:\n" << min->value << endl;
        min = tree.findSuccessor(min);
    }
    
    Node *max = tree.findMax(tree.T);
    for(int i = 0; i < n; i++) {
        cout << "\nThe " << i<< "th big value is:\n" << max->value << endl;
        max = tree.findPredecessor(max);
    }
    
    cout << "\nAfter delete the root, the tree is:\n" << endl;
    tree.deleteOne(tree.T);
    tree.print(tree.T);
    
    cout << "\nAfter delete value " << n << ", the tree is:\n" << endl;
    tree.deleteOne(n);
    tree.print(tree.T);
    
    cout << "\nAfter delete all node, the tree is:\n" << endl;
    tree.deleteAll(tree.T);
    tree.print(tree.T);
    return 0;
}
