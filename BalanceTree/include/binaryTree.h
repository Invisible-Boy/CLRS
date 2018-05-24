#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include <cstddef>
#include <assert.h>

namespace binaryTree {

template <typename T>
class unInheritBase {
    friend T;
    private:
        unInheritBase() {}
        ~unInheritBase() {}
};

template <typename T1, typename T2 = int>
class Node  {
    public:
        Node(const T1 &val = 0, Node *left = NULL, Node *right = NULL) :
            m_val(val), m_left(left), m_right(right) {}
        virtual ~Node() {}

        const T1& GetValue() const { return m_val; }
        Node* GetLeft() const { return m_left; }
        Node* GetRight() const { return m_right; }
        virtual Node* GetParent() const = 0;
        virtual const T2& GetFactor() const = 0;
        virtual Node* GetNull() const { return NULL; }

        void SetValue(const T1& val) { m_val = val; }
        void SetLeft(Node *left) { m_left = left; }
        void SetRight(Node *right) { m_right = right; }
        virtual void SetParent(Node*) = 0;
        virtual void SetFactor(const T2&) = 0;

    private:
        T1 m_val;
        Node *m_left, *m_right;
};

template <typename T1, typename T2>
inline bool IsNull(const Node<T1, T2> *now) {
    return now == NULL || now == now->GetNull();
}

template <typename T1, typename T2>
Node<T1, T2>* DoSearch(Node<T1, T2> *root, const T1 &val) {
    while(!IsNull(root)) {
        if(root->GetValue() == val)
            return root;
        else if(root->GetValue() > val)
            root = root->GetLeft();
        else root = root->GetRight();
    }
    return root;
}

template <typename T1, typename T2>
void DoInsert(Node<T1, T2> *&rproot, Node<T1, T2> *pnew) {
    assert(!IsNull(pnew));
    if(IsNull(rproot))
        rproot = pnew;
    else {
        Node<T1, T2> *pnow, *pnext = rproot;
        do {
            pnow = pnext;
            pnext = pnow->GetValue() > pnew->GetValue() ? pnow->GetLeft() : pnow->GetRight();
        } while(!IsNull(pnext));
        if(pnow->GetValue() > pnew->GetValue())
            pnow->SetLeft(pnew);
        else
            pnow->SetRight(pnew);
        if(pnew != NULL)
            pnew->SetParent(pnow);
    }
}

template <typename T1, typename T2>
void TransPlant(Node<T1, T2> *&rproot, Node<T1, T2> *p1, Node<T1, T2> *p2) {
    assert(!IsNull(p1));
    Node<T1, T2> *pparent = p1->GetParent();
    if(IsNull(pparent))
        rproot = p2;
    else {
        if(p1 == pparent->GetLeft())
            pparent->SetLeft(p2);
        else
            pparent->SetRight(p2);
    }
    if(p2 != NULL)
        p2->SetParent(pparent);
}

template <typename T1, typename T2>
Node<T1, T2>* GetSuccessor(Node<T1, T2> *pnow) {
    assert(!IsNull(pnow));
    Node<T1, T2> *ans = pnow->GetRight();
    if(!IsNull(ans))
        while(!IsNull(ans->GetLeft()))
            ans = ans->GetLeft();
    else {
        ans = pnow->GetParent();
        while(!IsNull(ans) && pnow != ans->GetLeft()) {
            pnow = ans;
            ans = pnow->GetParent();
        }
    }
    return ans;
}

template <typename T1, typename T2>
Node<T1, T2>* GetPredecessor(Node<T1, T2> *pnow) {
    assert(!IsNull(pnow));
    Node<T1, T2> *ans = pnow->GetLeft();
    if(!IsNull(ans))
        while(!IsNull(ans->GetRight()))
            ans = ans->GetRight();
    else {
        ans = pnow->GetParent();
        while(!IsNull(ans) && pnow != ans->GetRight()) {
            pnow = ans;
            ans = pnow->GetParent();
        }
    }
    return ans;
}

template <typename T1, typename T2>
void LeftRotate(Node<T1, T2> *&rproot, Node<T1, T2> *pnow) {
    assert(!IsNull(pnow));
    Node<T1, T2> *pright = pnow->GetRight();
    if(!IsNull(pright)) {
        TransPlant(rproot, pnow, pright);
        pnow->SetRight(pright->GetLeft());
        if(!IsNull(pnow->GetRight()))
            pnow->GetRight()->SetParent(pnow);
        pright->SetLeft(pnow);
        pnow->SetParent(pright);
    }
}

template <typename T1, typename T2>
void RightRotate(Node<T1, T2> *&rproot, Node<T1, T2> *pnow) {
    assert(!IsNull(pnow));
    Node<T1, T2> *pleft = pnow->GetLeft();
    if(!IsNull(pleft)) {
        TransPlant(rproot, pnow, pleft);
        pnow->SetLeft(pleft->GetRight());
        if(!IsNull(pnow->GetLeft()))
            pnow->GetLeft()->SetParent(pnow);
        pleft->SetRight(pnow);
        pnow->SetParent(pleft);
    }
}

template <typename T1, typename T2>
void Destory(Node<T1, T2> *now) {
    if(!IsNull(now)) {
        Destory(now->GetLeft());
        Destory(now->GetRight());
        delete now;
    }
}

}
#endif // BINARY_TREE_H_
