//
// Created by 86157 on 25-1-16.
//

#include <queue>
#include <iostream>
int main()
{
    std::priority_queue<int,std::vector<int>,std::greater<int>> que;
    que.push(30);
    que.push(20);
    que.push(2);
    que.push(59);
    que.push(100);
    while(!que.empty())
    {
        std::cout<<que.top()<<std::endl;
        que.pop();
    }
}
