/**
 * Title:   Binary Search Tree
 * Author:  InvisibleMan
 * Time:    2017-6-2
 */
#ifndef _BINARY_SEARCH_TREE_
#define _BINARY_SEARCH_TREE_
#include <iostream>

class Node {
    public:
        int value;
        Node *l, *r, *p;
        static Node Nil;
        Node(int _value = 0, Node* null = &Nil) : value(_value), l(null), r(null), p(null) {}
        ~Node() {}
        virtual Node* GetNull();
};

Node Node::Nil;
Node* Node::GetNull() {
    return &Nil;
}

class BSTree {
    public:
        Node *T;
        BSTree(Node* null = &Node::Nil) : T(null) {}
        ~BSTree() {}
        
        Node* search(int value);
        virtual void insert(int value);
        virtual void deleteOne(Node* x);
        virtual void deleteOne(int value);
        Node* findMax(Node *x);
        Node* findMin(Node *x);
        Node* findSuccessor(Node *x);
        Node* findPredecessor(Node *x);
        void print(Node *x);
        void deleteAll(Node *x);
    protected:
        virtual void transPlant(Node *x, Node *y);
};

Node* BSTree::search(int value) {
    Node *ans = T;
    while(ans != ans->GetNull() && ans->value != value) {
        if(ans->value > value)
            ans = ans->l;
        else ans = ans->r;
    }
    return ans;
}

void BSTree::insert(int value) {
    Node *x = new Node(value);
    Node *p = x->GetNull(), *now = T;
    while(now != now->GetNull()) {
        p = now;    // 对p的赋值要在开始进行，否则p一直是NULL
        if(now->value > value)
            now = now->l;
        else
            now = now->r;
    }
    if(p == p->GetNull()) T = x;
    else if(p->value > value)
        p->l = x;
    else p->r = x;
    x->p = p;
}

void BSTree::transPlant(Node *x, Node *y) {
    if(x->p == x->GetNull()) T = y;
    else {
        if(x == x->p->l)
            x->p->l = y;
        else
            x->p->r = y;
    }
    // 使用了哨兵，不需要判空
    y->p = x->p;
}

void BSTree::deleteOne(Node* x) {
    if(x == x->GetNull()) {
        std::cout << "The node x is NULL, can't delete->" << std::endl; 
        return;
    }
    if(x->l == x->GetNull())
        transPlant(x, x->r);
    else if(x->r == x->GetNull())
        transPlant(x, x->l);
    else {
        Node *t = findSuccessor(x);
        if(t->p != x) {
            transPlant(t, t->r);
            t->r = x->r;
            t->r->p = t;  // 不要漏了对孩子父节点的更改
        }
        transPlant(x, t);
        t->l = x->l;
        t->l->p = t;  // 不要忘记对孩子父节点的更改
    }
    delete x;
}

void BSTree::deleteOne(int value) {
    Node *t = search(value);
    while(t != t->GetNull()) {
        deleteOne(t);
        t = search(value);
    }
}

Node* BSTree::findMax(Node *x) {
    while(x != x->GetNull() && x->r != x->GetNull())
        x = x->r;
    return x;
}

Node* BSTree::findMin(Node *x) {
    while(x != x->GetNull() && x->l != x->GetNull())
        x = x->l;
    return x;
}

Node* BSTree::findSuccessor(Node *x) {
    if(x->r != x->GetNull())
        return findMin(x->r);
    Node *p = x->p;
    while(p != p->GetNull() && x == p->r) {
        x = p;
        p = x->p;
    }
    return p;
}

Node* BSTree::findPredecessor(Node *x) {
    if(x->l != x->GetNull())
        return findMax(x->l);
    Node *p = x->p;
    while(p != p->GetNull() && x == p->l) {
        x = p;
        p = x->p;
    }
    return p;
}

void BSTree::print(Node *x) {
    if(x == x->GetNull()) return;
    if(x->l != x->GetNull()) print(x->l);
    std::cout << x->value << std::endl;
    if(x->r != x->GetNull()) print(x->r);
}

void BSTree::deleteAll(Node *x) {
    if(x == x->GetNull()) return;
    if(x->l != x->GetNull()) deleteAll(x->l);
    if(x->r != x->GetNull()) deleteAll(x->r);
    if(x->p == x->GetNull()) T = x->GetNull();
    else x->p->l = x->p->r = x->GetNull();
    delete x;
}
#endif
