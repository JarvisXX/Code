// hfTree.h
#ifndef hfTree_
#define hfTree_
#include <iostream>
using namespace std;

template <class Type>
class hfTree
{
private:
    struct Node
    {
        Type data;
        int weight;
        int parent, left, right;
    };
    Node *elem;
    int length;
public:
    struct hfCode
    {
        Type data;
        string code;
    };
    hfTree(const Type *x, const int *w, int size);
    void getCode(hfCode result[]);
    ~hfTree() {delete [] elem;}
};
#endif
