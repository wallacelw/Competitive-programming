stack<int> order;
vector<vector<int>> components;
vector<int> component;

void dfs1(int no){
    vistos[no] = 1;
    for(auto v: graph[no]){
        if(!vistos[v]){
            dfs1(v);
        }
    }
    order.push(no);
}

void dfs2(int no){
    vistos[no] = 1;
    component.push_back(no);
    for(auto v: invertedGraph[no]){
        if(!vistos[v]){
            dfs2(v);
        }
    }
}
