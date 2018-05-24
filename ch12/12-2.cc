/**
 * Title:   12-2.cc
 * Author:  InvisibleMan
 * Date:    2017-5-5
 * remarks: 此代码用于实现思考题12-2中的字典树算法 
 */
#include <cstdio>
#include <string>

using namespace std;

struct Node {
    bool flag;
    Node *left, *right;
    Node(bool _flag = false, Node *_left = NULL, Node *_right = NULL) :
    flag(_flag), left(_left), right(_right) {}
};

void Insert(Node *T, string s) {
    int n = s.length();
    Node *now = T;
    for(int i = 0; i < n; i++) {
        if(s[i] == '0') {
            if(now->left == NULL)
                now->left = new Node();
            now = now->left;
        }
        else {
            if(now->right == NULL)
                now->right = new Node();
            now = now->right;
        }
    }
    now->flag = true;
}

void print(Node *now, string &t) {
    if(now->flag)
        printf("%s\n", t.c_str());
    if(now->left != NULL) {
        t.push_back('0');
        print(now->left, t);
        t.pop_back();
    }
    if(now->right != NULL) {
        t.push_back('1');
        print(now->right, t);
        t.pop_back();
    }
}

int main() {
    string d[] = {"1", "10", "011", "100", "0"};
    Node T;
    for(int i = 0; i < 5; i++)
        Insert(&T, d[i]);
    string t;
    print(&T, t);
    return 0;
}
