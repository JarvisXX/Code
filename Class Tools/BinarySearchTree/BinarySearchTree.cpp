#include "BinarySearchTree.h"
#include<iostream>
using namespace std;

template <class Type>
bool BinarySearchTree<Type>::find(const Type &x) const
{
    return find(x, root);
}

template <class Type>
void BinarySearchTree<Type>::insert(const Type &x)
{
    insert(x, root);
}

template <class Type>
void BinarySearchTree<Type>::remove(const Type &x)
{
    remove(x, root);
}

template <class Type>
void BinarySearchTree<Type>::clear(BinaryNode *t)
{
    if (t==NULL)
        return;
    if (t->left!=NULL)
        clear(t->left);
    if (t->right!=NULL)
        clear(t->right);
    delete t;
}

template <class Type>
bool BinarySearchTree<Type>::find(const Type &x, BinaryNode* t) const
{
    if (t==NULL)
        return false;
    else if (x<t->data)
        return find(x, t->left);
    else if (x>t->data)
        return find(x, t->right);
    else
        return true;
}

template <class Type>
void BinarySearchTree<Type>::insert(const Type &x, BinaryNode* &t)
{
    if (t==NULL)
        t = new BinaryNode(x, NULL, NULL);
    else if (x<t->data)
        insert(x, t->left);
    else if (x>t->data)
        insert(x, t->right);
    else
        return;
}

template <class Type>
void BinarySearchTree<Type>::remove(const Type &x, BinaryNode* &t)
{
    if (t==NULL)
        return;
    if (x<t->data)
        remove(x, t->left);
    else if (x>t->data)
        remove(x, t->right);
    else if (t->left!=NULL && t->right!=NULL)
    {
        BinaryNode *tmp=t->right;
        while (tmp->left!=NULL)
            tmp = tmp->left;
        t->data = tmp->data;
        remove(t->data, t->right);
    }
    else
    {
        BinaryNode *oldNode=t;
        if (t->left!=NULL)
            t = t->left;
        else
            t = t->right;
        delete oldNode;
    }
}
