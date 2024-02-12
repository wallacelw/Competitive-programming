/**
 * Author: Wallace, Bruno Monteiro
 * Date: 04/02/2024
 * Description: After Merging 2-Vertex Connected Components, one can 
 * generate a block cut tree
 * Time: O(V+E)
 */

// Block-Cut Tree (bruno monteiro)
//
// Cria a block-cut tree, uma arvore com os blocos
// e os pontos de articulacao
// Blocos sao as componentes 2-vertice-conexos maximais
// Uma 2-coloracao da arvore eh tal que uma cor sao
// os componentes, e a outra cor sao os pontos de articulacao
//
// Funciona para grafo nao conexo
//
// isAP[i] responde o numero de novas componentes conexas
// criadas apos a remocao de i do grafo g
// Se isAP[i] >= 1, i eh ponto de articulacao
// 
// Para todo i < blocks.size()
// blocks[i] eh uma componente 2-vertce-conexa maximal
// blockEdges[i] sao as arestas do bloco i
//
// tree eh a arvore block-cut-tree
// tree[i] eh um vertice da arvore que corresponde ao bloco i
// 
// comp[i] responde a qual vertice da arvore vertice i pertence
//
// Arvore tem no maximo 2n vertices
//
// O(n+m)

// 0-idx graph!!!
vector<vll> g(MAX), tree, blocks; 
vector<vector<pll>> blockEdges;
stack<ll> st; // st for vertices,
stack<pll> st2; // st2 for edges
vector<ll> low, tin, comp, isAP;
ll timer = 1;

void dfs(ll u, ll p = -1) {
    low[u] = tin[u] = timer++;
    
    st.push(u);

    // add only back-edges to stack
    if (p != -1) st2.push({u, p}); 
    for(auto v : g[u]) if (v != p) {
        if (tin[v] != -1) // visited
            st2.push({u, v});
    }

    for(auto v : g[u]) if (v != p) {
        if (tin[v] != -1) // visited
            low[u] = min(low[u], tin[v]);
        else { // not visited
            dfs(v, u);
            low[u] = min(low[u], low[v]);

            if (low[v] >= tin[u]) {
                isAP[u] += 1;
                
                blocks.pb(vll(1, u));
                while(blocks.back().back() != v)
                    blocks.back().pb(st.top()), st.pop();
                
                blockEdges.pb(vector<pll>(1, st2.top())), st2.pop();
                while(blockEdges.back().back() != pair<ll, ll>(v, u))
                    blockEdges.back().pb(st2.top()), st2.pop();
            }
        }
    }

    // corner case: root
    if (p == -1 and isAP[u]) isAP[u]--;
}

void blockCutTree(ll n) {
    
    // initialize vectors and reset
    tree.clear(), blocks.clear(), blockEdges.clear();
    st = stack<ll>(), st2 = stack<pll>();
    tin.assign(n, -1);
    low.assign(n, 0), comp.assign(n, 0), isAP.assign(n, 0);
    timer = 1;

    // find Articulation Points
    for(ll i=0; i<n; i++) if (tin[i] == -1)
        dfs(i);

    // set component id for APs
    tree.assign(blocks.size(), vll());
    for(ll i=0; i<n; i++) if (isAP[i])
        comp[i] = tree.size(), tree.pb(vll()); 
    
    // set component id for non-APs and construct tree
    for(ll u=0; u<(ll)blocks.size(); u++) {
        for(auto v : blocks[u]) {
            if (!isAP[v]) 
                comp[v] = u;
            else 
                tree[u].pb(comp[v]), tree[comp[v]].pb(u);
        }
    }
}