//calc.h
#ifndef calc_
#define calc_

class calc
{
    enum Type {DATA, ADD, SUB, MULTI, DIV,
               OPAREN, CPAREN, EOL};
    struct node
    {
        Type type;
        int data;
        node *lchild, *rchild;
        node(Type t, int d=0, node *lc=NULL, node *rc=NULL)
        {
            type = t;
            data = d;
            lchild = lc;
            rchild = rc;
        }
    };
    node *root;
public:
    calc(char *s) {root =  create(s);}
    int result()
    {
        if (root==NULL)
            return 0;
        return result(root);
    }
private:
    node *create(char* &s);
    Type getToken(char* &s, int &value);
    int result(node *t);
};
#endif
