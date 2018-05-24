/**
 * Title:   Red Black Tree Test
 * Author:  InvisibleMan
 * Time:    2017-7-12
 */

#include "order-statistic-tree.h"
#include <iostream>
#include <queue>
#include <string>

using namespace std;

void BFS(Node *t) {
    queue<Node *> q;
    q.push(t);
    while(!q.empty()) {
        OSNode *now = dynamic_cast<OSNode*>(q.front());
        q.pop();
        if(now != now->GetNull()) {
            cout << "value is " << now->value << " color is " << now->color << " size is " << now->size<< endl;
            if(now->l != now->GetNull())
                q.push(now->l);
            if(now->r != now->GetNull())
                q.push(now->r);
        }
    }
}

void DFS(Node *t) {
    if(t != t->GetNull()) {
        if(t->l != t->GetNull())
            DFS(t->l);
        OSNode *tt = dynamic_cast<OSNode*>(t);
        cout << "value is " << t->value << " color is " <<tt->color  <<  " size is " << tt->size << endl;
        if(t->r != t->GetNull())
            DFS(t->r);
    }
}

int main() {
    OSTree tree;
    string order;
    while(cin >> order) {
        if(order == "q") break;
        else if(order == "i") {
            cout << "Please input the number of insert value:";
            int n, t;
            cin >> n;
            cout << "Please input the insert value:";
            for(int i = 0; i < n; i++) {
                cin >> t;
                tree.insert(t);
            }
        }
        else if(order == "d") {
            cout << "Please input the number of delete value:";
            int n, t;
            cin >> n;
            cout << "Please input the delete value:";
            for(int i = 0; i < n; i++) {
                cin >> t;
                tree.deleteOne(t);
            }
        }
        else if(order == "dfs") {
            cout << "The dfs is:" << endl;
            DFS(tree.T);
        }
        else if(order == "bfs") {
            cout << "The bfs is:" << endl; 
            BFS(tree.T);
        }
        else if(order == "rank") {
            cout << "Please input the rank number:" << endl;
            int n;
            cin >> n;
            OSNode *ans = dynamic_cast<OSNode*>(tree.OSSelect(n));
            cout << "the ans value is " << ans->value << " the color is " << ans->color << " the size is " << ans->size << endl;
        }
    }
    return 0;
}
