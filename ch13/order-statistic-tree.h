/**
 * Title:   Order Statistic Tree
 * Author:  InvisibleMan
 * Date:    2017-7-12
 */

#ifndef ORDER_STATISTIC_TREE_H
#define ORDER_STATISTIC_TREE_H
#include "red-black-tree.h"

class OSNode : public RBNode {
    public:
        int size;
        static OSNode Nil;
        OSNode(int _v = 0, int _s = 0, bool _c = true, RBNode *null = &Nil) :
            RBNode(_v, _c, null), size(_s) {}
        virtual ~OSNode() {}
        virtual Node* GetNull();
};

OSNode OSNode::Nil(0, 0, false);
Node* OSNode::GetNull() {
    return &Nil;
}

class OSTree : public RBTree {
    public:
        OSTree(OSNode *null = &OSNode::Nil) : RBTree(null) {}
        ~OSTree() {}

        using RBTree::deleteOne;
        virtual void insert(int value);
        virtual void deleteOne(Node *x);
        int OSRank(Node *x);
        Node* OSSelect(int i);
    protected:
        virtual void leftRotate(Node *x);
        virtual void rightRotate(Node *x);
    private:
        void subSize(Node *x);
};

void OSTree::insert(int value) {
    OSNode *x = new OSNode(value, 1);
    OSNode *now = dynamic_cast<OSNode*>(T);
    Node *p = now->GetNull();
    while(now != now->GetNull()) {
        p = now;
        now->size++;
        if(now->value > value)
            now = dynamic_cast<OSNode*>(now->l);
        else
            now = dynamic_cast<OSNode*>(now->r);
    }
    if(p == p->GetNull())
        T = x;
    else if(p->value > value)
        p->l = x;
    else
        p->r = x;
    x->p = p;
    insertFix(x);
}

void OSTree::subSize(Node *x) {
    OSNode *p = dynamic_cast<OSNode*>(x->p);
    while(p != p->GetNull()) {
        p->size--;
        p = dynamic_cast<OSNode*>(p->p);
    }
}

void OSTree::deleteOne(Node *tx) {
    if(tx == tx->GetNull()) return;
    OSNode *x = dynamic_cast<OSNode*>(tx), *y = x;
    Node *t;
    bool yOriginColor = y->color;
    if(y->l == y->GetNull()) {
        subSize(y);
        t = y->r;
        transPlant(y, t);
    }
    else if(y->r == y->GetNull()) {
        subSize(y);
        t = y->l;
        transPlant(y, t);
    }
    else {
        y = dynamic_cast<OSNode*>(findSuccessor(y));
        subSize(y);
        yOriginColor = y->color;
        t = y->r;
        if(y->p == x)
            t->p = y;
        else {
            transPlant(y, t);
            y->r = x->r;
            y->r->p = y;
        }
        y->l = x->l;
        y->l->p = y;
        transPlant(x, y);
        y->color = x->color;
        y->size = x->size;
    }
    delete x;
    if(!yOriginColor)
        deleteFix(dynamic_cast<OSNode*>(t));
}

void OSTree::leftRotate(Node *x) {
    if(x == x->GetNull() || x->r == x->GetNull()) return;
    RBTree::leftRotate(x);
    OSNode *tp = dynamic_cast<OSNode*>(x->p);
    OSNode *tx = dynamic_cast<OSNode*>(x);
    tp->size = tx->size;
    tx->size = dynamic_cast<OSNode*>(tx->l)->size + dynamic_cast<OSNode*>(tx->r)->size + 1;
}

void OSTree::rightRotate(Node *x) {
    if(x == x->GetNull() || x->l == x->GetNull()) return;
    RBTree::rightRotate(x);
    OSNode *tp = dynamic_cast<OSNode*>(x->p);
    OSNode *tx = dynamic_cast<OSNode*>(x);
    tp->size = tx->size;
    tx->size = dynamic_cast<OSNode*>(tx->l)->size + dynamic_cast<OSNode*>(tx->r)->size + 1;
}

int OSTree::OSRank(Node *x) {
    if(x == x->GetNull()) return -1;
    int ans = dynamic_cast<OSNode*>(x->l)->size + 1;
    while(x->p != x->GetNull()) {
        if(x == x->p->r)
            ans += dynamic_cast<OSNode*>(x->p->l)->size + 1;
        x = x->p;
    }
    return ans;
}

Node* OSTree::OSSelect(int i) {
    Node *x = T;
    if(i > dynamic_cast<OSNode*>(x)->size) return x->GetNull();
    while(x != x->GetNull()) {
        int now = dynamic_cast<OSNode*>(x->l)->size + 1;
        if(now == i)
            return x; 
        else if(now > i)
            x = x->l;
        else {
            i -= now;
            x = x->r;
        }
    }
    return x->GetNull();
}
#endif
