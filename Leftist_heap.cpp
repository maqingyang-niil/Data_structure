//
// Created by 86157 on 25-1-12.
//
#include <utility>
template<typename comparable>
class Leftist_heap
{
private:
    struct Leftist_node
    {
        comparable element;
        Leftist_node *left;
        Leftist_node *right;
        int npl;
    };
    Leftist_node *root;
    Leftist_node *merge(Leftist_node *h1,Leftist_node *h2);
    Leftist_node *merge1(Leftist_node *h1,Leftist_node *h2);
    void insert(comparable &x);
    comparable &find_min();
    bool is_empty();
public:
    void merge(Leftist_heap &rhs);
    void delete_min();
    void delete_min(comparable &min_item);

};

template <typename comparable>
comparable &Leftist_heap<comparable>::find_min() {
    return root->element;
}

template<typename comparable>
typename Leftist_heap<comparable>::Leftist_node *Leftist_heap<comparable>::merge(Leftist_node *h1,Leftist_node *h2) {
    if (h1== nullptr)
        return h2;
    if (h2== nullptr)
        return h1;
    if (h1->element<h2->element)
        merge1(h1,h2);
    else
        merge1(h2,h1);
}

template<typename comparable>
typename Leftist_heap<comparable>::Leftist_node *Leftist_heap<comparable>::merge1(Leftist_heap::Leftist_node *h1,
                                                                                  Leftist_heap::Leftist_node *h2) {
    if (h1->left== nullptr)
        h1->left=h2;
    else
    {
        h1->right=merge(h1->right,h2);
        if (h1->left->npl<h1->right->npl)
            std::swap(h1->right,h1->left);
        h1->npl=h1->right->npl+1;
    }
    return h1;
}

template<typename comparable>
void Leftist_heap<comparable>::merge(Leftist_heap &rhs) {
    if (&rhs==this)
        return;
    root= merge(root,rhs->root);
    rhs.root= nullptr;
}

template<typename comparable>
void Leftist_heap<comparable>::insert(comparable &x)
{
    root= merge(new Leftist_node{x},root);
}

template<typename comparable>
void Leftist_heap<comparable>::delete_min() {
    if (is_empty())
        return;
    Leftist_node *old_root;
    root= merge(root->left,root->right);
    delete old_root;
}

template<typename comparable>
void Leftist_heap<comparable>::delete_min(comparable &min_item) {
    min_item=find_min();
    delete_min();
}

