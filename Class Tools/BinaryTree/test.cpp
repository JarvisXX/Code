#include <iostream>
using namespace std;

template <class elemType>
class queue
{
public:
    virtual bool isEmpty() = 0;
    virtual void enQueue(const elemType &x) = 0;
    virtual elemType deQueue() = 0;
    virtual elemType getHead() = 0;
    virtual ~queue() {}
};

template <class elemType>
class linkQueue:public queue<elemType>
{
private:
    struct node
    {
        elemType data;
        node *next;
        node (const elemType &x, node *N=NULL)
        {
            data = x;
            next = N;
        }
        node():next(NULL) {}
        ~node() {}
    };
    node *front, *rear;
public:
    linkQueue() {front = rear = NULL;}
    ~linkQueue();
    bool isEmpty() {return front==NULL;}
    void enQueue(const elemType &x);
    elemType deQueue();
    elemType getHead() {return front->data;}
};

template <class elemType>
linkQueue<elemType>::~linkQueue()
{
    node *tmp;
    while (front!=NULL)
    {
        tmp = front;
        front = front->next;
        delete tmp;
    }
}

template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x)
{
    if (rear==NULL)
        front = rear = new node(x);
    else
    {
        rear->next = new node(x);
        rear = rear->next;
    }
}

template <class elemType>
elemType linkQueue<elemType>::deQueue()
{
    node *tmp = front;
    elemType value = front->data;
    front = front->next;
    if (front==NULL) rear=NULL;
    delete tmp;
    return value;
}

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
    void preOrder() const; //NLR
    void postOrder() const; //LRN
    void midOrder() const; //LNR
    void createTree(Type flag);
private:
    void clear(Node *t);
    int size(Node *t) const;
    int height(Node *t) const;
    void preOrder(Node *t) const;
    void postOrder(Node *t) const;
    void midOrder(Node *t) const;
};

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
void BinaryTree<Type>::createTree(Type flag)
{
    linkQueue<Node *> que;
    Node *tmp;
    Type x, ldata, rdata;

    cout << "\nInput root node: ";
    cin >> x;
    root = new Node(x);
    que.enQueue(root);
    while(!que.isEmpty())
    {
        tmp = que.deQueue();
        cout << "\nInput" << tmp->data << "'s two children(" << flag << "means NULL): ";
        cin >> ldata >> rdata;
        if (ldata!=flag)
            que.enQueue(tmp->left=new Node(ldata));
        if (rdata!=flag)
            que.enQueue(tmp->right=new Node(rdata));
    }
    cout << "create completed!\n";
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
