#include <iostream>
#include "BinaryTree.h"
#include "linkQueue.cpp"
using namespace std;

template <class Type>
Type BinaryTree<Type>::getRoot() const
{
    return root->data;
}

template <class Type>
Type BinaryTree<Type>::getLeft() const
{
    return root->left->data;
}

template <class Type>
Type BinaryTree<Type>::getRight() const
{
    return root->right->data;
}

template <class Type>
void BinaryTree<Type>::makeTree(const Type &x, BinaryTree &lt, BinaryTree &rt)
{
    root = new Node(x, lt.root, rt.root);
    lt.root = NULL;
    rt.root = NULL;
}

template <class Type>
void BinaryTree<Type>::delLeft()
{
    BinaryTree tmp=root->left;
    root->left = NULL;
    tmp.clear();
}

template <class Type>
void BinaryTree<Type>::delRight()
{
    BinaryTree tmp=root->right;
    root->right = NULL;
    tmp.clear();
}

template <class Type>
bool BinaryTree<Type>::isEmpty()
{
    return root==NULL;
}

template <class Type>
void BinaryTree<Type>::clear()
{
    if (root!=NULL)
        clear(root);
    root = NULL;
}

template <class Type>
int BinaryTree<Type>::size() const
{
    return size(root);
}

template <class Type>
int BinaryTree<Type>::height() const
{
    return height(root);
}

template <class Type>
void BinaryTree<Type>::preOrder() const
{
    if (root!=NULL)
    {
        cout << "\nNLR: ";
        preOrder(root);
    }
}

template <class Type>
void BinaryTree<Type>::postOrder() const
{
    if (root!=NULL)
    {
        cout << "\nLRN: ";
        postOrder(root);
    }
}

template <class Type>
void BinaryTree<Type>::midOrder() const
{
    if (root!=NULL)
    {
        cout << "\nLNR: ";
        midOrder(root);
    }
}

template <class Type>
void BinaryTree<Type>::createTree(Type flag, Type x, Type *l, Type *r)
{
    linkQueue<Node *> que;
    Node *tmp;
    Type ldata, rdata;

    root = new Node(x);
    que.enQueue(root);
    while(!que.isEmpty())
    {
        tmp = que.deQueue();
        ldata = l[tmp->data];
        rdata = r[tmp->data];
        if (ldata!=flag)
            que.enQueue(tmp->left=new Node(ldata));
        if (rdata!=flag)
            que.enQueue(tmp->right=new Node(rdata));
    }
}

template <class Type>
bool BinaryTree<Type>::isComplete()
{
    bool flag=0;
    linkQueue<Node *> que;
    que.enQueue(root);
    while (!que.isEmpty())
    {
        Node* tmp;
        tmp = que.deQueue();
        if (tmp==NULL)
            flag = 1;
        else if (flag==1)
            return false;
        else
        {
            que.enQueue(tmp->left);
            que.enQueue(tmp->right);
        }
    }
    return true;
}

template <class Type>
void BinaryTree<Type>::clear(Node *t)
{
    if (t->left!=NULL)
        clear(t->left);
    if (t->right!=NULL)
        clear(t->right);
    delete t;
}

template <class Type>
int BinaryTree<Type>::size(Node *t) const
{
    if (t==NULL)
        return 0;
    return 1+size(t->left)+size(t->right);
}

template <class Type>
int BinaryTree<Type>::height(Node *t) const
{
    if (t==NULL)
        return 0;
    int lt=height(t->left);
    int rt=height(t->right);
    return 1+(lt>rt?lt:rt);
}

template <class Type>
void BinaryTree<Type>::preOrder(Node *t) const
{
    if (t!=NULL)
    {
        cout << t->data << ' ';
        preOrder(t->left);
        preOrder(t->right);
    }
}

template <class Type>
void BinaryTree<Type>::postOrder(Node *t) const
{
    if (t!=NULL)
    {
        postOrder(t->left);
        postOrder(t->right);
        cout << t->data << ' ';
    }
}

template <class Type>
void BinaryTree<Type>::midOrder(Node *t) const
{
    if (t!=NULL)
    {
        midOrder(t->left);
        cout << t->data << ' ';
        midOrder(t->right);
    }
}

