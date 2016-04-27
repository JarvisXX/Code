//BinaryTree.h
#ifndef BinaryTree_
#define BinartTree_
template <class Type>
class BinaryTree
{
private:
    struct Node
    {
        Node *left, *right;
        Type data;
        Node(): left(NULL), right(NULL) {}
        Node(Type item, Node *L=NULL, Node *R=NULL): data(item), left(L), right(R) {}
        ~Node() {}
    };
    Node *root;
public:
    BinaryTree(): root(NULL) {}
    BinaryTree(const Type &value) {root=new Node(value);}
    BinaryTree(Node *p) {root=p;}
    ~BinaryTree() {clear();}
    Type getRoot() const;
    Type getLeft() const;
    Type getRight() const;
    void makeTree(const Type &x, BinaryTree &lt, BinaryTree &rt);
    void delLeft();
    void delRight();
    bool isEmpty();
    void clear();
    int size() const;
    int height() const;
    void preOrder(int *w) const; //NLR
    void postOrder(int *w) const; //LRN
    void midOrder(int *w) const; //LNR
    void levelOrder(int *w) const;
    void createTree(Type flag, Type x, Type *l, Type *r);
    bool isComplete();
private:
    void clear(Node *t);
    int size(Node *t) const;
    int height(Node *t) const;
    void preOrder(Node *t, int *w) const;
    void postOrder(Node *t, int *w) const;
    void midOrder(Node *t, int *w) const;
};
#endif
