#include <vector>
class DisjointSet {
public:
    explicit DisjointSet(int num_element);
    void union_set(int root1,int root2);
    void union_set_by_height(int root1,int root2);
    int find(int x);
private:
    std::vector<int> s;
};
DisjointSet::DisjointSet(int num_element):s(num_element,-1){}

void DisjointSet::union_set(int root1,int root2){
    s[root2]=root1;
}

void DisjointSet::union_set_by_height(int root1,int root2){
    if (s[root2]<s[root1])
    s[root1]=root2;
    else
    {
        if (s[root1]==s[root2])
        --s[root1];
        s[root2]=root1;
    }
}
int DisjointSet::find(int x){
    if (s[x]<0)
    return x;
    else
    return s[x]=find(s[x]);
}