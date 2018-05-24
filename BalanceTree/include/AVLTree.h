#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include "binaryTree.h"

namespace binaryTree {

template <typename T1>
class AVLNode : public Node<T1, int>, virtual public unInheritBase<AVLNode<T1> > {
    public:
        AVLNode(const T1 &val = 0, Node<T1, int> *left = &NIL, 
                Node<T1, int> *right = &NIL, Node<T1 ,int> *parent = &NIL, 
                int factor = 0) :
                Node<T1, int>(val, left, right), m_parent(parent), m_factor(factor) {}
        virtual ~AVLNode() {}

        virtual Node<T1, int>* GetParent () const { return m_parent; }
        virtual const int& GetFactor() const { return m_factor; }
        virtual Node<T1, int>* GetNull() const { return &NIL; }

        virtual void SetParent(Node<T1, int> *parent) { m_parent = parent; }
        virtual void SetFactor(const int &factor) { m_factor = factor; }
        
        static AVLNode NIL;
    private:
        Node<T1, int> *m_parent;
        int m_factor;


        int abs(int t) { return t < 0 ? -t : t; }
};

template<typename T1>
AVLNode<T1> AVLNode<T1>::NIL;

template <typename T1>
class AVLTree : virtual public unInheritBase<AVLTree<T1> > {
    public:
        explicit AVLTree() : m_root(&AVLNode<T1>::NIL) {}
        ~AVLTree() { Destory(m_root); }

        Node<T1, int>*& Root() { return m_root; }
        Node<T1, int>* Search(const T1 &val);
        void Insert(const T1 &val);
        void Delete(const T1 &val);

    private:
        AVLTree(const AVLTree&) {}
        const AVLTree& operator = (const AVLTree&) {}
        void Delete(Node<T1, int>*);
        void Fix(Node<T1, int>*);
        void LeftRotateChangeFactor(Node<T1, int>*);
        void RightRotateChangeFactor(Node<T1, int>*);

        Node<T1, int> *m_root;
};

template <typename T1>
Node<T1, int>* AVLTree<T1>::Search(const T1 &val) {
    return DoSearch(Root(), val);
}

template <typename T1>
void AVLTree<T1>::Insert(const T1 &val) {
    Node<T1, int> *pnow = new AVLNode<T1>(val);
    DoInsert(Root(), pnow);
    do {
        Node<T1, int> *temp = pnow;
        pnow = pnow->GetParent();
        if(IsNull(pnow)) return;
        int newFactor = pnow->GetFactor() + (temp == pnow->GetLeft() ? -1 : 1);
        pnow->SetFactor(newFactor);
        if(newFactor == 0) return;
    } while(abs(pnow->GetFactor()) < 2);
    Fix(pnow);
}

template <typename T1>
void AVLTree<T1>::Delete(const T1 &val) {
    Node<T1, int> *pnow = DoSearch(Root(), val);
    while(!IsNull(pnow)) {
        Delete(pnow);
        pnow = DoSearch(Root(), val);
    }
}

template <typename T1>
void AVLTree<T1>::Delete(Node<T1, int> *pnow) {
    assert(!IsNull(pnow));
    Node<T1, int> *porigin = pnow, *pdel = pnow->GetParent();
    int deta = porigin == porigin->GetParent()->GetLeft() ? -1 : 1;
    if(IsNull(pnow->GetLeft())) {
        pnow = pnow->GetRight();
        TransPlant(Root(), porigin, pnow);
    }
    else if(IsNull(pnow->GetRight())) {
        pnow = pnow->GetLeft();
        TransPlant(Root(), porigin, pnow);
    }
    else {
        pnow = pnow->GetRight();
        deta = 1;
        pdel = pnow;
        while(!IsNull(pnow->GetLeft()))
            pnow = pnow->GetLeft();
        if(pnow->GetParent() != porigin) {
            TransPlant(Root(), pnow, pnow->GetRight());
            pnow->SetRight(porigin->GetRight());
            pnow->GetRight()->SetParent(pnow);
            deta = -1;
            pdel = pnow->GetParent();
        }
        TransPlant(Root(), porigin, pnow);
        pnow->SetFactor(porigin->GetFactor());
        pnow->SetLeft(porigin->GetLeft());
        pnow->GetLeft()->SetParent(pnow);
    }
    delete(porigin);
    while(!IsNull(pdel)) {
        int newFactor = pdel->GetFactor() - deta;
        pdel->SetFactor(newFactor);
        if(abs(newFactor) == 2) {
            Fix(pdel);
            pdel = pdel->GetParent();
            newFactor = pdel->GetFactor();
        }
        if(newFactor) return;
        Node<T1, int> *pparent = pdel->GetParent();
        if(IsNull(pparent)) return;
        deta = pdel == pparent->GetLeft() ? -1 : 1;
        pdel = pparent;
    }
}

template <typename T1>
void AVLTree<T1>::Fix(Node<T1, int> *pnow) {
    assert(!IsNull(pnow));
    if(pnow->GetFactor() == -2) {
        if(pnow->GetLeft()->GetFactor() == 1) {
            LeftRotateChangeFactor(pnow->GetLeft());
            LeftRotate(Root(), pnow->GetLeft());
        }
        RightRotateChangeFactor(pnow);
        RightRotate(Root(), pnow);
    }
    else {
        if(pnow->GetRight()->GetFactor() == -1) {
            RightRotateChangeFactor(pnow->GetRight());
            RightRotate(Root(), pnow->GetRight());
        }
        LeftRotateChangeFactor(pnow);
        LeftRotate(Root(), pnow);
    }
}

template <typename T1>
void AVLTree<T1>::LeftRotateChangeFactor(Node<T1, int> *pnow) {
    assert(!IsNull(pnow));
    Node<T1, int> *pright = pnow->GetRight();
    assert(!IsNull(pright));
    if(pright->GetFactor() < 0)
        pnow->SetFactor(pnow->GetFactor() - 1);
    else 
        pnow->SetFactor(pnow->GetFactor() - 1 - pright->GetFactor());
    if(pnow->GetFactor() > 0)
        pright->SetFactor(pright->GetFactor() - 1);
    else
        pright->SetFactor(pright->GetFactor() + pnow->GetFactor() - 1);
}

template <typename T1>
void AVLTree<T1>::RightRotateChangeFactor(Node<T1, int> *pnow) {
    assert(!IsNull(pnow));
    Node<T1, int> *pleft = pnow->GetLeft();
    assert(!IsNull(pleft));
    if(pleft->GetFactor() > 0)
        pnow->SetFactor(pnow->GetFactor() + 1);
    else
        pnow->SetFactor(pnow->GetFactor() - pleft->GetFactor() + 1);
    if(pnow->GetFactor() < 0)
        pleft->SetFactor(pleft->GetFactor() + 1);
    else
        pleft->SetFactor(pnow->GetFactor() + pleft->GetFactor() + 1);
}

}
#endif // AVL_TREE_H_
