//
// Created by 86157 on 25-1-16.
//
#include <vector>
#include <climits>
#include <queue>
#include "disjoint_set.cpp"
#include <algorithm>
class adjacent_matrix_map
{
private:
    std::vector<std::vector<int>> matrix;
    int vertex_num;
    int edge_num;
public:
    explicit adjacent_matrix_map(int vertex_num,int edge_num);
    explicit adjacent_matrix_map(const adjacent_matrix_map &item);
    void breadth_first_search(int pos);
    void Dijkstra(int pos);
    void Kruskal();
    void Prim(int pos);
};

void adjacent_matrix_map::Prim(int pos){
    std::vector<bool> selected(vertex_num,false);
    std::vector<int> parents(vertex_num,-1);
    std::vector<int> distance(vertex_num,INT_MAX);
    selected[pos]=true;
    distance[pos]=0;
    int nonselected=vertex_num-1;
    while(nonselected)
    {
        int min_distance=INT_MAX;
        int min_dis_index=-1;
        for (int i=0;i<vertex_num;++i)
        {
            if (selected[i]=true)
            {
                for (int j=0;j<vertex_num;++j)
                {
                    if (matrix[i][j]!=INT_MAX)
                    {
                        if (min_distance>matrix[i][j])
                        {
                            min_distance=matrix[i][j];
                            min_dis_index=j;
                            parents[j]=i;
                        }
                    }
                }
            }
        }
        if (min_dis_index=-1)
            break;
        selected[min_dis_index]=true;
        distance[min_dis_index]=min_distance;

    }
}

void adjacent_matrix_map::Kruskal(){
    DisjointSet ds(vertex_num);
    std::vector<std::pair<int,std::pair<int,int>>> edges;
    for (int i=0;i<vertex_num;++i)
    {
        for (int j=0;j<vertex_num;++j)
        {
            if (i<j&&matrix[i][j]<INT_MAX)
            {
                edges.push_back({i,{j,matrix[i][j]}});
            }
        }
    }
    std::sort(edges.begin(),edges.end());
    std::vector<std::pair<int,int>> mst;
    for (const auto edge:edges)
    {
        int weight=edge.second.second;
        int u=edge.first;
        int v=edge.second.first;
        int set_u=ds.find(u);
        int set_v=ds.find(v);
        if (set_u!=set_v)
        {
            mst.push_back({u,v});
            ds.union_set_by_height(set_u,set_v);
        }
    }
}

void adjacent_matrix_map::breadth_first_search(int pos){
    std::vector<bool> visited(vertex_num,false);
    std::vector<int> distance(vertex_num,INT_MAX);
    std::queue<int> que;
    visited[pos]=true;
    distance[pos]=0;
    que.push(pos);
    while(!que.empty())
    {
        int current=que.front();
        que.pop();
        for (int i=0;i<vertex_num;++i)
        {
            if (matrix[current][i]!=INT_MAX&&visited[i]!=true)
            {
                que.push(i);
                visited[i]=true;
                distance[i]=distance[current]+matrix[current][i];
            }
        }
        
    }
}

void adjacent_matrix_map:: Dijkstra(int pos){
    std::vector<bool> visited(vertex_num,false);
    std::vector<int> distance(vertex_num,INT_MAX);
    std::queue<int> que;
    visited[pos]=true;
    distance[pos]=0;
    que.push(pos);
    while(vertex_num--)
    {
        int current=que.front();
        que.pop();
        for (int i=0;i<vertex_num;++i)
        {
            if (matrix[current][i]!=INT_MAX)
            {
                if ((visited[i]==true&&distance[current]+matrix[current][i]<distance[i])||(visited[i]==false))
                {
                    distance[i]=distance[current]+matrix[current][i];
                    visited[i]=true;
                }
            }
        }
        int min_index=-1;
        int min_distance=INT_MAX;
        for (int i=0;i<vertex_num;++i)
        {
            if (matrix[current][i]<min_distance)
            {
                min_distance=matrix[current][i];
                min_index=i;
            }
        }
        que.push(min_index);
    }
}

adjacent_matrix_map::adjacent_matrix_map(int vertex_num,int edge_num) {
    this->vertex_num=vertex_num;
    this->edge_num=edge_num;
    matrix.resize(vertex_num,std::vector<int>(vertex_num,INT_MAX));
}

adjacent_matrix_map::adjacent_matrix_map(const adjacent_matrix_map &item) {
    vertex_num=item.vertex_num;
    edge_num=item.edge_num;
    for (int i=0;i<vertex_num;++i)
    {
        for (int j=0;j<vertex_num;++j)
        {
            matrix[i][j]=item.matrix[i][j];
        }
    }
}








