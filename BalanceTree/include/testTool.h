#ifndef TEST_TOOL_H_
#define TEST_TOOL_H_

#include "binaryTree.h"
#include <queue>
#include <iostream>
#include <string>
#include <sstream>

namespace binaryTree {
namespace testTool {

using std::string;
using std::queue;
using std::cout;
using std::endl;
using std::pair;
using std::stringstream;

template <typename T1, typename T2>
struct PrintNode {
    PrintNode(Node<T1, T2> *node = NULL, int cnt = 0) : m_node(node), m_left(NULL), m_right(NULL), m_cnt(cnt) {}
    Node<T1, T2> *m_node;
    PrintNode *m_left, *m_right;
    int m_cnt;
};

template <typename T1, typename T2>
PrintNode<T1, T2>* Clone(Node<T1, T2> *root) {
    PrintNode<T1, T2> *ans = NULL;
    if(!IsNull(root)) {
        ans = new PrintNode<T1, T2>(root);
        ans->m_left = Clone(root->GetLeft());
        ans->m_right = Clone(root->GetRight());
    }
    return ans;
}

template <typename T1, typename T2>
void DFS(PrintNode<T1, T2> *root, int &cnt) {
    if(root != NULL) {
        DFS(root->m_left, cnt);
        root->m_cnt = cnt++;
        DFS(root->m_right, cnt);
    }
}

template <typename T1, typename T2>
static string str(Node<T1, T2> *now, int size) {
    stringstream temp;
    temp << now->GetValue() << ':' << now->GetFactor();
    string ans = temp.str();
    size -= ans.length();
    if(size > 0) ans = string(size >> 1, ' ') + ans;
    return ans;
}

template <typename T1, typename T2>
void Destory(PrintNode<T1, T2> *root) {
    if(root != NULL) {
        Destory(root->m_left);
        Destory(root->m_right);
        delete root;
    }
}

template <typename T1, typename T2>
void Print(Node<T1, T2> *root) {
    if(IsNull(root)) {
        cout << '#' << endl;
        return;
    }
    PrintNode<T1, T2> *printRoot = Clone(root);
    int tot = 0;
    DFS(printRoot, tot);
    typedef pair<PrintNode<T1, T2>*, int> queNode;
    int cnt = 0;
    queue<queNode> que;
    que.push(queNode(printRoot, 0));
    string s0, s1, s2, s3;
    const int Size = 5;
    while(!que.empty()) {
        queNode now = que.front();
        que.pop();
        if(now.second > cnt) {
            cnt++;
            cout << s0 << endl << s1 << endl << s2 << endl << s3 << endl;
            s0.clear();
            s1.clear();
            s2.clear();
            s3.clear();
        }
        PrintNode<T1, T2> *nowNode = now.first;
        if(nowNode->m_left != NULL)
            que.push(queNode(nowNode->m_left, now.second + 1));
        if(nowNode->m_right != NULL)
            que.push(queNode(nowNode->m_right, now.second + 1));
        size_t nowSize = Size * nowNode->m_cnt;
        if(s0.length() < nowSize) s0.resize(nowSize, ' ');
        s0 += str(nowNode->m_node, Size);
        size_t mid = nowSize + (Size >> 1);
        if(s1.length() < mid) s1.resize(mid, ' ');
        if(nowNode->m_left == NULL && nowNode->m_right == NULL)
            continue;
        s1 += '|';
        if(nowNode->m_left != NULL) {
            nowSize = Size * nowNode->m_left->m_cnt + (Size >> 1);
            if(s2.length() < nowSize) s2.resize(nowSize, ' ');
            if(s3.length() < nowSize) s3.resize(nowSize, ' ');
            s3 += '|';
            s2 += '+';
            s2.resize(mid, '=');
            s2 += '+';
        }
        if(nowNode->m_right != NULL) {
            if(s2.length() < mid) {
                s2.resize(mid, ' ');
                s2 += '+';
            }
            nowSize = Size * nowNode->m_right->m_cnt + (Size >> 1);
            s2.resize(nowSize, '=');
            if(s3.length() < nowSize) s3.resize(nowSize, ' ');
            s3 += '|';
            s2 += '+';
        }
    }
    cout << s0 << endl;
    cout << string(tot * Size, '#') << endl; 
    Destory(printRoot);
}

template <typename T1, typename T2>
int IsAVLTree(Node<T1, T2> *now, bool &flag) {
    if(flag && !IsNull(now)) {
        int hleft = IsAVLTree(now->GetLeft(), flag) + 1;
        int hright = IsAVLTree(now->GetRight(), flag) + 1;
        if(flag) flag = now->GetFactor() == hright - hleft;
        return hleft > hright ? hleft : hright;
    }
    return 0;
}

template <typename T1, typename T2>
int IsRBTree(Node<T1, T2> *now, bool &flag) {
    if(flag && !IsNull(now)) {
        int hleft = IsRBTree(now->GetLeft(), flag);
        int hright = IsRBTree(now->GetRight(), flag);
        if(flag) flag = hleft == hright;
        return hleft + (now->GetFactor() ? 0 : 1);
    }
    return 0;
}

}
}
#endif // TEST_TOOL_H_
