/**
 * Title:   Red Black Tree
 * Authror: InvisibleMan
 * Date:    2017-6-26
 */

#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H
#include "binary-search-tree.h"

class RBNode : public Node {
    public:
        bool color;
        static RBNode Nil;
        RBNode(int _value = 0, bool _c = true, RBNode *null = &Nil) : Node(_value, null), color(_c) {}
        ~RBNode() {}
        virtual Node* GetNull();
};
RBNode RBNode::Nil(0, false);

Node* RBNode::GetNull() {
    return &Nil;
}

class RBTree : public BSTree{
    public:
        RBTree(RBNode *null = &RBNode::Nil) : BSTree(null) {}
        ~RBTree() {}
        
        virtual void insert(int value);
        virtual void deleteOne(int value);
        virtual void deleteOne(Node *x);
    protected:
        virtual void leftRotate(Node *x);
        virtual void rightRotate(Node *x);
        void insertFix(RBNode *x);
        void deleteFix(RBNode *x);
};

void RBTree::leftRotate(Node *x) {
    if(x == x->GetNull() || x->r == x->GetNull())
        return;
    Node *temp = x->r;
    x->r = temp->l;
    x->r->p = x;
    if(x->p == x->GetNull())
        T = temp;
    else if(x == x->p->l)
        x->p->l = temp;
    else
        x->p->r = temp;
    temp->p = x->p;
    temp->l = x;
    x->p = temp;
}

void RBTree::rightRotate(Node *x) {
    if(x == x->GetNull() || x->l == x->GetNull())
        return;
    Node *temp = x->l;
    x->l = temp->r;
    x->l->p = x;
    if(x->p == x->GetNull())
        T = temp;
    else if(x == x->p->l)
        x->p->l = temp;
    else
        x->p->r = temp;
    temp->p = x->p;
    temp->r = x;
    x->p = temp;
}

void RBTree::insert(int value) {
    Node *x = new RBNode(value);
    Node *now = T, *p = x->GetNull();
    while(now != now->GetNull()) {
        p = now;
        if(now->value < value)
            now = now->r;
        else
            now = now->l;
    }
    if(p == p->GetNull())
        T = x;
    else if(p->value > value)
        p->l = x;
    else
        p->r = x;
    x->p = p;
    insertFix(dynamic_cast<RBNode*>(x));
}

void RBTree::insertFix(RBNode *x) {
    while(x->p != x->GetNull() && dynamic_cast<RBNode*>(x->p)->color) {
        if(x->p == x->p->p->l) {
            RBNode *y = dynamic_cast<RBNode*>(x->p->p->r);
            if(y->color) {
                y->color = false;
                RBNode *xp = dynamic_cast<RBNode*>(x->p);
                xp->color = false;
                x = dynamic_cast<RBNode*>(xp->p);
                x->color = true;
            }
            else{
                if(x == x->p->r) {
                    x = dynamic_cast<RBNode*>(x->p);
                    leftRotate(x);
                }
                RBNode* xp = dynamic_cast<RBNode*>(x->p);
                xp->color = false;
                RBNode *xpp = dynamic_cast<RBNode*>(xp->p);
                xpp->color = true;
                rightRotate(xpp);
            }
        }
        else {
            RBNode *y = dynamic_cast<RBNode*>(x->p->p->l);
            if(y->color) {
                y->color = false;
                RBNode *xp = dynamic_cast<RBNode*>(x->p);
                xp->color = false;
                x = dynamic_cast<RBNode*>(xp->p);
                x->color = true;
            }
            else {
                if(x == x->p->l) {
                    x = dynamic_cast<RBNode*>(x->p);
                    rightRotate(x);
                }
                RBNode *xp = dynamic_cast<RBNode*>(x->p);
                xp->color = false;
                RBNode *xpp = dynamic_cast<RBNode*>(x->p->p);
                xpp->color = true;
                leftRotate(xpp);
            }
        }
    }
    dynamic_cast<RBNode*>(T)->color = false;
}

void RBTree::deleteOne(Node *tx) {
    if(tx == tx->GetNull()) return;
    RBNode *x = dynamic_cast<RBNode*>(tx), *y = x;
    Node *t;
    bool yOriginColor = y->color;
    if(y->l == y->GetNull()) {
        t = y->r;
        transPlant(y, t);
    }
    else if(y->r == y->GetNull()) {
        t = y->l;
        transPlant(y, t);
    }
    else {
        y = dynamic_cast<RBNode*>(findSuccessor(x));
        t = y->r;
        yOriginColor = y->color;
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
    }
    delete x;
    if(!yOriginColor)
        deleteFix(dynamic_cast<RBNode*>(t));
}

void RBTree::deleteFix(RBNode *x) {
    while(x->p != x->GetNull() && !x->color) {
        if(x == x->p->l) {
            RBNode *y = dynamic_cast<RBNode*>(x->p->r);
            if(y->color) {
                y->color = false;
                RBNode *xp = dynamic_cast<RBNode*>(x->p);
                xp->color = true;
                leftRotate(xp);
            }
            else if(!dynamic_cast<RBNode*>(y->l)->color && !dynamic_cast<RBNode*>(y->r)->color) {
                y->color = true;
                x = dynamic_cast<RBNode*>(x->p);
            }
            else {
                if(!dynamic_cast<RBNode*>(y->r)->color) {
                    y->color = true;
                    dynamic_cast<RBNode*>(y->l)->color = false;
                    rightRotate(y);
                    y = dynamic_cast<RBNode*>(x->p->r);
                }
                RBNode *xp = dynamic_cast<RBNode*>(x->p);
                y->color = xp->color;
                xp->color = false;
                dynamic_cast<RBNode*>(y->r)->color = false;
                leftRotate(xp);
                x = dynamic_cast<RBNode*>(T);
            }
        }
        else {
            RBNode *y = dynamic_cast<RBNode*>(x->p->l);
            if(y->color) {
                y->color = false;
                RBNode *xp = dynamic_cast<RBNode*>(x->p);
                xp->color = true;
                rightRotate(xp);
            }
            else if(!dynamic_cast<RBNode*>(y->l)->color && !dynamic_cast<RBNode*>(y->r)->color) {
                y->color = true;
                x = dynamic_cast<RBNode*>(x->p);
            }
            else {
                if(!dynamic_cast<RBNode*>(y->l)->color) {
                    y->color = true;
                    dynamic_cast<RBNode*>(y->r)->color = false;
                    leftRotate(y);
                    y = dynamic_cast<RBNode*>(x->p->l);
                }
                RBNode *xp = dynamic_cast<RBNode*>(x->p);
                y->color = xp->color;
                dynamic_cast<RBNode*>(y->l)->color = false;
                xp->color = false;
                rightRotate(xp);
                x = dynamic_cast<RBNode*>(T);
            }
        }
    }
    x->color = false;
}

void RBTree::deleteOne(int value) {
    Node *t = search(value);
    while(t != t->GetNull()) {
        deleteOne(t);
        t = search(value);
    }
}
#endif
