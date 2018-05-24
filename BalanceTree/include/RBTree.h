#ifndef RB_TREE_H_
#define RB_TREE_H_

#include "binaryTree.h"

namespace binaryTree {

template <typename T1>
class RBNode : public Node<T1, bool>, virtual public unInheritBase<RBNode<T1> > {
    public:
        RBNode(const T1 &val = 0, Node<T1, bool> *left = &RBNode<T1>::NIL, 
               Node<T1, bool> *right = &RBNode<T1>::NIL, 
               Node<T1, bool> *parent = &RBNode::NIL, bool color = true) :
               Node<T1, bool>(val, left, right), m_parent(parent), m_color(color) {}
        virtual ~RBNode() {}

        virtual Node<T1, bool>* GetParent() const { return m_parent; }
        virtual const bool& GetFactor() const { return m_color; }
        virtual Node<T1, bool>* GetNull() const { return &RBNode::NIL; }

        virtual void SetParent(Node<T1, bool> *parent) { m_parent = parent; }
        virtual void SetFactor(const bool &color) { m_color = color; }

        static RBNode NIL;

    private:
        Node<T1, bool> *m_parent;
        bool m_color;
};

template <typename T1>
RBNode<T1> RBNode<T1>::NIL(0, &RBNode<T1>::NIL, &RBNode<T1>::NIL,
                           &RBNode<T1>::NIL, false);

template <typename T1>
class RBTree : virtual public unInheritBase<RBTree<T1> > {
    public:
        explicit RBTree() : m_root(&RBNode<T1>::NIL) {}
        ~RBTree() { Destory(m_root); }

        Node<T1, bool>*& Root() { return m_root; }
        Node<T1, bool>* Search(const T1 &val);
        void Insert(const T1 &val);
        void Delete(const T1 &val);

    private:
        RBTree(const RBTree&) {}
        const RBTree& operator = (const RBTree&) {}
        void Delete(Node<T1, bool>*);

        Node<T1, bool> *m_root;
};

template <typename T1>
Node<T1, bool>* RBTree<T1>::Search(const T1 &val) {
    return DoSearch(m_root, val);
}

template <typename T1>
void RBTree<T1>::Insert(const T1 &val) {
    Node<T1, bool> *pnow = new RBNode<T1>(val);
    DoInsert(m_root, pnow);
    Node<T1, bool> *pparent = pnow->GetParent();
    while(pparent->GetFactor()) {
        Node<T1, bool> *puncle;
        if(pparent == pparent->GetParent()->GetLeft()) {
            puncle = pparent->GetParent()->GetRight();
            if(puncle->GetFactor()) {
                pparent->SetFactor(false);
                puncle->SetFactor(false);
                pparent->GetParent()->SetFactor(true);
                pparent = pparent->GetParent()->GetParent();
                continue;
            }
            if(pparent->GetRight()->GetFactor()) {
                LeftRotate(m_root, pparent);
                pparent = pparent->GetParent();
            }
            pparent->SetFactor(false);
            pparent = pparent->GetParent();
            pparent->SetFactor(true);
            RightRotate(m_root, pparent);
            break;
        }
        else {
            puncle = pparent->GetParent()->GetLeft();
            if(puncle->GetFactor()) {
                pparent->SetFactor(false);
                puncle->SetFactor(false);
                pparent->GetParent()->SetFactor(true);
                pparent = pparent->GetParent()->GetParent();
                continue;
            }
            if(pparent->GetLeft()->GetFactor()) {
                RightRotate(m_root, pparent);
                pparent = pparent->GetParent();
            }
            pparent->SetFactor(false);
            pparent = pparent->GetParent();
            pparent->SetFactor(true);
            LeftRotate(m_root, pparent);
            break;
        }
    }
    m_root->SetFactor(false);
}

template <typename T1>
void RBTree<T1>::Delete(const T1 &val) {
    Node<T1, bool> *pnow = Search(val);
    while(!IsNull(pnow)) {
        Delete(pnow);
        pnow = Search(val);
    }
}

template <typename T1>
void RBTree<T1>::Delete(Node<T1, bool> *pnow) {
    assert(!IsNull(pnow));
    Node<T1, bool> *porigin = pnow;
    bool originColor = pnow->GetFactor();
    if(IsNull(pnow->GetLeft())) {
        TransPlant(m_root, pnow, pnow->GetRight());
        pnow = pnow->GetRight();
    }
    else if(IsNull(pnow->GetRight())) {
        TransPlant(m_root, pnow, pnow->GetLeft());
        pnow = pnow->GetLeft();
    }
    else {
        pnow = pnow->GetRight();
        while(!IsNull(pnow->GetLeft()))
            pnow = pnow->GetLeft();
        Node<T1, bool> *temp = pnow;
        originColor = temp->GetFactor();
        pnow = pnow->GetRight();
        pnow->SetParent(temp);
        if(temp->GetParent() != porigin) {
            TransPlant(m_root, temp, pnow);
            temp->SetRight(porigin->GetRight());
            temp->GetRight()->SetParent(temp);
        }
        TransPlant(m_root, porigin, temp);
        temp->SetLeft(porigin->GetLeft());
        temp->GetLeft()->SetParent(temp);
        temp->SetFactor(porigin->GetFactor());
    }
    delete porigin;
    if(!originColor) {
        while(pnow != m_root && !pnow->GetFactor()) {
            Node<T1, bool> *pparent = pnow->GetParent();
            if(pnow == pparent->GetLeft()) {
                Node<T1, bool> *pbrother = pparent->GetRight();
                if(pbrother->GetFactor()) {
                    pparent->SetFactor(true);
                    pbrother->SetFactor(false);
                    LeftRotate(m_root, pparent);
                }
                else {
                    if(pbrother->GetLeft()->GetFactor()) {
                        pbrother->SetFactor(true);
                        pbrother->GetLeft()->SetFactor(false);
                        RightRotate(m_root, pbrother);
                        pbrother = pbrother->GetParent();
                    }
                    if(pbrother->GetRight()->GetFactor()) {
                        pbrother->GetRight()->SetFactor(false);
                        pbrother->SetFactor(pparent->GetFactor());
                        pparent->SetFactor(false);
                        LeftRotate(m_root, pparent);
                        break;
                    }
                    else {
                        pbrother->SetFactor(true);
                        pnow = pparent;
                    }
                }
            }
            else {
                Node<T1, bool> *pbrother = pparent->GetLeft();
                if(pbrother->GetFactor()) {
                    pparent->SetFactor(true);
                    pbrother->SetFactor(false);
                    RightRotate(m_root, pparent);
                }
                else {
                    if(pbrother->GetRight()->GetFactor()) {
                        pbrother->GetRight()->SetFactor(false);
                        pbrother->SetFactor(true);
                        LeftRotate(m_root, pbrother);
                        pbrother = pbrother->GetParent();
                    }
                    if(pbrother->GetLeft()->GetFactor()) {
                        pbrother->GetLeft()->SetFactor(false);
                        pbrother->SetFactor(pparent->GetFactor());
                        pparent->SetFactor(false);
                        RightRotate(m_root, pparent);
                        break;
                    }
                    else {
                        pbrother->SetFactor(true);
                        pnow = pparent;
                    }
                }
            }
        }
        pnow->SetFactor(false);
    }
}

}

#endif // RBTREE_H_
