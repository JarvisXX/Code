#include <iostream>
#include <cstring>
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
void BinaryTree<Type>::preOrder(int *w) const
{
    if (root!=NULL)
    {
        preOrder(root, w);
    }
}

template <class Type>
void BinaryTree<Type>::postOrder(int *w) const
{
    if (root!=NULL)
    {
        postOrder(root, w);
    }
}

template <class Type>
void BinaryTree<Type>::midOrder(int *w) const
{
    if (root!=NULL)
    {
        midOrder(root, w);
    }
}

template <class Type>
void BinaryTree<Type>::levelOrder(int *w) const
{
    linkQueue<Node *> que;
    que.enQueue(root);
    while(!que.isEmpty())
    {
        Node *tmp=que.deQueue();
        cout << w[tmp->data] <<' ';
        if (tmp->left!=NULL)
            que.enQueue(tmp->left);
        if (tmp->right!=NULL)
            que.enQueue(tmp->right);
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
void BinaryTree<Type>::preOrder(Node *t, int *w) const
{
    if (t!=NULL)
    {
        cout << w[t->data] << ' ';
        preOrder(t->left, w);
        preOrder(t->right, w);
    }
}

template <class Type>
void BinaryTree<Type>::postOrder(Node *t, int *w) const
{
    if (t!=NULL)
    {
        postOrder(t->left, w);
        postOrder(t->right, w);
        cout << w[t->data] << ' ';
    }
}

template <class Type>
void BinaryTree<Type>::midOrder(Node *t, int *w) const
{
    if (t!=NULL)
    {
        midOrder(t->left, w);
        cout << w[t->data] << ' ';
        midOrder(t->right, w);
    }
}

int main()
{
    int N;
    int lt[100010], rt[100010], wt[100010];
    bool searchRoot[100010];
    int root;

    cin >> N;
    memset(searchRoot, 0, sizeof(searchRoot));
    for (int i=1; i<=N; ++i)
    {
        cin >> lt[i] >> rt[i] >> wt[i];
        searchRoot[lt[i]] = 1;
        searchRoot[rt[i]] = 1;
    }
    for (int i=1; i<=N; ++i)
    {
        if (searchRoot[i]==0)
        {
            root = i;
            break;
        }
    }
    BinaryTree<int> tree;
    tree.createTree(0, root, lt, rt);
    tree.levelOrder(wt);
}
