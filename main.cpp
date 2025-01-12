#include <vector>
template<typename comparable>
class Binary_heap
{
public:
    explicit Binary_heap(int capacity=100);
    explicit Binary_heap(const std::vector<comparable> &items);
    void insert(const comparable &x);
    void insert(comparable &&x);
    void delete_min(comparable &min_item);
    bool is_empty();
    void percolate_down(int hole);
    void Build_heap();
private:
    int current_size;
    std::vector<comparable> array;

};

template<typename comparable>
void Binary_heap<comparable>::Build_heap() {
    for (int i=current_size;i>0;--i)
    {
        percolate_down(i);
    }
}


template<typename comparable>
Binary_heap<comparable>::Binary_heap(const std::vector<comparable> &items):array(items.size()+10),current_size(items.size())
{
    for (int i=0;i<items.size();++i)
    {
        array[i+1]=items[i];
    }
    Build_heap();
}

template<typename comparable>
bool Binary_heap<comparable>::is_empty() {
    return array.empty();
}


template<typename comparable>
void Binary_heap<comparable>:: insert(const comparable &x)
{
    if(current_size==array.size()-1)
        array.resize(array.size()*2);
    int hole=++current_size;
    comparable copy=x;
    array[0]=std::move(copy);
    for(;x<array[hole/2];hole/=2)
        array[hole]=std::move(array[hole/2]);
    array[hole]=std::move(array[0]);
}

template<typename comparable>
void Binary_heap<comparable>::delete_min(comparable &min_item)
{
    if (is_empty())
        return;
    min_item=std::move(array[1]);
    array[1]=std::move(array[current_size--]);
    percolate_down(1);
}

template <typename comparable>
void Binary_heap<comparable>::percolate_down(int hole) {
    int child;
    comparable tmp=std::move(array[hole]);
    for (;hole*2<=current_size;hole=child){
        child=hole*2;
        if (child!=current_size&&array[child+1]<array[child])
            ++child;
        if (array[child]<tmp)
            array[hole]=std::move(array[child]);
        else
            break;
    }
    array[hole]=std::move(tmp);
}