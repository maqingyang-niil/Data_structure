//
// Created by 86157 on 25-1-13.
//
#include <vector>
#include <queue>
#include <limits.h>
#include <algorithm>
#include "disjoint_set.cpp"
template<typename comparable>
class adjacency_list_map
{
private:
    struct list_node
    {
        int element;
        int value;
        list_node *next;
    };
    std::vector<list_node*> array;
    int vertex_num;
    int edge_num;
public:
    explicit adjacency_list_map(adjacency_list_map&item);
    explicit adjacency_list_map(int capacity=100);
    void Kruskal_no_orient();
    void breadth_first_search(int pos);
    void Dijkstra(int pos);
    void Prim(int pos);
};


template<typename comparable>
void adjacency_list_map<comparable>::Kruskal_no_orient() {
    std::vector<std::pair<int,std::pair<int,int>>> edge;
    for(int i=0;i<vertex_num;++i)
    {
        list_node *current=array[i]->next;
        while(current)
        {
            if (i<current->element)
            {
                edge.push_back({current->value,{i,current->element}});
            }
            current=current->next;
        }
    }
    std::sort(edge.begin(),edge.end());
    DisjointSet ds(vertex_num);
    std::vector<std::pair<int,int>> mst;
    for (const auto edge1:edge)
    {
        int weight=edge1.first;
        int u=edge1.second.first;
        int v=edge1.second.second;
        int set_u=ds.find(u);
        int set_v=ds.find(v);
        if (set_u!=set_v)
        {
            mst.push_back({u,v});
            ds.union_set_by_height(set_u,set_v);
        }
    }
}

template<typename comparable>
void adjacency_list_map<comparable>::Prim(int pos){
    std::vector<bool> selected(vertex_num, false);
    std::vector<int> parent(vertex_num, -1);
    std::vector<int> min_distance(vertex_num, INT_MAX);
    selected[pos] = true;
    min_distance[pos] = 0;
    int nonselected_vertex = vertex_num - 1;
    while (nonselected_vertex) {
        int min_distance_vertex = -1;
        int mini_distance = INT_MAX;

        for (int i = 0; i < vertex_num; ++i) {
            if (selected[i]) {
                list_node *ptr = array[i]->next;
                while (ptr != nullptr) {
                    if (!selected[ptr->element] && ptr->value < mini_distance) {
                        mini_distance = ptr->value;
                        min_distance_vertex = ptr->element;
                        parent[min_distance_vertex] = i;
                    }
                    ptr = ptr->next;
                }
            }
        }
        if (min_distance_vertex == -1) {
            break; // 图不连通
        }
        selected[min_distance_vertex] = true;
        min_distance[min_distance_vertex] = mini_distance;
        --nonselected_vertex;
    }
}

template<typename comparable>
void adjacency_list_map<comparable>::Dijkstra(int pos){
    std::vector<bool> visited(vertex_num,false);
    std::vector<int> length(vertex_num,INT_MAX);
    std::queue<int> que;
    visited[pos]=true;
    length[pos]=0;
    que.push(pos);
    while(!que.empty())
    {
        int current_vertex=que.front();
        que.pop();
        list_node *ptr=array[current_vertex]->next;
        int nearest_pos=INT_MAX;
        int nearest_distance=INT_MAX;
        for (;ptr!=nullptr;ptr=ptr->next)
        {
            int vertex=ptr->element;
            if (visited[vertex]=true)
            {
                if (length[current_vertex]+ptr->value<length[vertex])
                {
                    length[vertex]=length[current_vertex]+ptr->value;
                }
            }
            else
            {
                length[vertex]=length[current_vertex]+ptr->value;
                visited[vertex]=true;
            }
            if (ptr->value<nearest_distance)
            {
                nearest_distance=ptr->value;
                nearest_pos=ptr->element;
            }
        }
        que.push(nearest_pos);
    }
}



template<typename comparable>
void adjacency_list_map<comparable>::breadth_first_search(int pos){
    std::vector<bool> visited(vertex_num,false);
    std::vector<int> length(vertex_num,0);
    std::queue<int> que;
    visited[pos]=true;
    length[pos]=0;
    que.push(pos);
    while(!que.empty())
    {
        int distance=1;
        int current_vertex=que.front();
        que.pop();
        list_node *ptr=array[current_vertex]->next;
        for (;ptr!=nullptr;ptr=ptr->next)
        {
            int vertex=ptr->element;
            que.push(vertex);
            length[vertex]=distance;
        }
        ++distance;
    }
}



template<typename comparable>
adjacency_list_map<comparable>::adjacency_list_map(adjacency_list_map&item) {
    vertex_num=item->vertex_num;
    edge_num=item->edge_num;
    array.resize(item->array.size(), nullptr);
    for (int i = 0; i < array.size(); ++i) {
        list_node *ex_ptr = item->array[i];
        list_node **in_ptr = &array[i];
        while (ex_ptr != nullptr) {
            *in_ptr = new list_node{
                ex_ptr->element,
                ex_ptr->value,
                nullptr
            };
            in_ptr = &((*in_ptr)->next);
            ex_ptr = ex_ptr->next;
        }
    }
}