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
//归并排序
/*
 * 驱动函数
 */
template<typename T>
void mergeSort(std::vector<T>&a)
{
    std::vector<T> tmp(a.size());
    mergeSort(a,tmp,0,a.size()-1);
}
template<typename T>
void merge(std::vector<T>&a,std::vector<T>&tmp,int leftpos,int rightpos,int rightend)
{
    int leftend=rightpos-1;
    int tmppos=leftpos;
    int numElement=rightend-leftpos+1;
    while(leftpos<=leftend&&rightpos<=rightend)
    {
        if (a[leftpos]<=a[rightpos])
            tmp[tmppos++]=std::move(a[leftpos++]);
        else
            tmp[tmppos++]=std::move(a[rightpos++]);
    }
    while(leftpos<=leftend)
        tmp[tmppos++]=std::move(a[leftpos++]);
    while(rightpos<=rightend)
        tmp[tmppos++]=std::move(a[rightpos++]);
    for(int i=0;i<numElement;++i,--rightend)
        a[rightend]=std::move(tmp[rightend]);
}
template<typename T>
void mergeSort(std::vector<T> &a,std::vector<T>&tmp,int left,int right)
{
    if (left<right)
    {
        int center=(left+right)/2;
        mergeSort(a,tmp,left,center);
        mergeSort(a,tmp,center+1,right);
        merge(a,tmp,left,center+1,right);
    }
}
//快速排序
/*
 * 驱动函数
 */
template<typename T>
void quickSort(std::vector<T>&a)
{

}
template<typename T>
const T&median3(std::vector<T>&a,int left,int right)
{
    int center=(left+right)/2;
    if(a[center]<a[left])
        std::swap(a[left],a[center]);
    if(a[right]<a[left])
        std::swap(a[left],a[right]);
    if(a[right]<a[center])
        std::swap(a[center],a[right]);
    std::swap(a[center],a[right-1]);
    return a[right-1];
}
template<typename T>
void quickSort(std::vector<T>&a,int left,int right)
{
    const T&pivot= median3(a,left,right);
    int i=left,j=right-1;
    for (;;)
    {
        while(a[++i]<pivot){}
        while(a[--j]>pivot){}
        if (i<j)
            std::swap(a[i],a[j]);
        else
            break;
    }
    std::swap(a[i],a[right-1]);
    quickSort(a,left,i-1);
    quickSort(a,i+1,right);
}
