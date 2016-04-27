//BinarySearchTree.h
#ifndef BST
#define BST
template <class Type>
class BinarySearchTree
{
private:
    struct BinaryNode
    {
        Type data;
        BinaryNode *left;
        BinaryNode *right;
        BinaryNode(const Type &d, BinaryNode *lt, BinaryNode *rt)
                   :data(d), left(lt), right(rt) {}
    };
    BinaryNode *root;
public:
    BinarySearchTree(BinaryNode *t=NULL) {root=t;}
    ~BinarySearchTree() {clear(root);}
    bool find(const Type &x) const;
    void insert(const Type &x);
    void remove(const Type &x);
    void clear(BinaryNode *t);
private:
    bool find(const Type &x, BinaryNode* t) const;
    void insert(const Type &x, BinaryNode* &t);
    void remove(const Type &x, BinaryNode* &t);
    void makeEmpty(BinaryNode* &t);
};
#endif
