#ifndef B_num_
#define B_num_
using namespace std;

struct linkNode
{
    int data;
    linkNode *next;
};

class EmptyString{};

class B_num
{
private:
    linkNode *head;
public:
    B_num() {head = new linkNode;}
    B_num(string a);
    B_num(const B_num &b);
    ~B_num() {delete head;}
    B_num add(const B_num &b);
    void print() const;
};
#endif
