#include <utility>
template<typename T>
class LeftistHeap
{
public:

    void merge(LeftistHeap&rhs)
    {
        if (this==&rhs)
            return;
        root= merge(root,rhs.root);
        rhs.root=nullptr;
    }
    void insert(const T&x)
    {
        root= merge(LeftistNode{x},root);
    }
    bool isEmpty()
    {
        return root==nullptr;
    }
    void deleteMin()
    {
        if (isEmpty())
            return;
        LeftistNode*oldNode=root;
        root= merge(root->left,root->right);
        delete oldNode;
    }
private:
    struct LeftistNode
    {
        T element;
        LeftistNode*left;
        LeftistNode*right;
        int npl;
        LeftistNode(const T&ele,LeftistNode*le=nullptr,LeftistNode*ri=nullptr,int np=0):element(ele),left(le),right(ri),npl(np){}
        LeftistNode(const T&&ele,LeftistNode*le=nullptr,LeftistNode*ri=nullptr,int np=0):element(std::move(ele)),left(le),right(ri),npl(np){}
    };
    LeftistNode*root;
    LeftistNode*merge(LeftistNode*h1,LeftistNode*h2)
    {
        if (h1==nullptr)
            return h2;
        if (h2==nullptr)
            return h1;
        if (h1->element<h2->element)
            return merge1(h1,h2);
        else
            return merge1(h2,h1);
    }
    void swapChild(LeftistNode*t)
    {
        LeftistNode*oldNode=t->right;
        t->right=t->left;
        t->left=oldNode;
    }
    LeftistNode*merge1(LeftistNode*h1,LeftistNode*h2)
    {
        if (h1->left==nullptr)
            h1->left=h2;
        else
        {
            h1->right= merge(h1->right,h2);
            if (h1->left->npl<h1->right->npl)
                swapChild(h1);
            h1->npl=h1->right->npl+1;
        }
        return h1;
    }

};
