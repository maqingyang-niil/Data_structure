#include <vector>
#include <utility>
//插入排序
template<typename T>
void insertSort(std::vector<T>&a)
{
    for (int p=1;p<a.size();++p)
    {
        T tmp=std::move(a[p]);
        int j;
        for (j=p;j>0&&tmp<a[j-1];--j)
            a[j]=std::move(a[j-1]);
        a[j]=std::move(tmp);
    }
}
//希尔排序
template<typename T>
void shellsort(std::vector<T>&a)
{
    for (int gap=a.size()/2;gap>0;gap/=2)
    {
        for (int i=gap;i<a.size();++i)
        {
            T tmp=std::move(a[i]);
            int j=i;
            for (;j>=gap&&tmp<a[j-gap];j-=gap)
            {
                a[j]=std::move(a[j-gap]);
            }
            a[j]=std::move(tmp);
        }
    }
}
//堆排序
/*
 * 内联函数，找到左儿子
 */
inline int leftChild(int i)
{
    return 2*i+1;
}
/*
 * para i:开始下滤的位置
 * para n:堆的逻辑大小
 */
template<typename T>
void percDown(std::vector<T>&a,int i,int n)
{
    int child;
    T tmp;
    for (tmp=std::move(a[i]); leftChild(i)<n;i=child)
    {
        child= leftChild(i);
        if (child!=n-1&&a[child]<a[child+1])
            ++child;
        if (tmp<a[child])
            a[i]=std::move(a[child]);
        else
            break;
    }
    a[i]=std::move(tmp);
}
//堆排序函数
template<typename T>
void heapsort(std::vector<T>&a)
{
    for (int i=a.size()/2-1;i>=0;--i)
    {
        percDown(a,i,a.size());
    }
    for (int j=a.size();j>0;--j)
    {
        std::swap(a[0],a[j]);
        percDown(a,0,j);
    }
}