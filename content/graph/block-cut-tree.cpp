/**
 * Author: Quirino
 * Date: 31/08/2024
 * Description: Quirino Block cut tree
 * Time: O(V+E)
 */

// Block-Cut Tree {{{
struct BlockCutTree {
  int N;
  vector<vector<int>> const& G;

  stack<pair<int, int>> S;
  int TIMER = -1;
  vector<int> pre, low;

  vector<int> art;
  vector<bool> is_art;
  vector<vector<pair<int, int>>> bcc;

  vector<vector<int>> BCT;
  vector<int> comp;

  void make_bcc(pair<int, int> until) {
    bcc.push_back({});
    pair<int, int> e{-1, -1};
    while (e != until) {
      e = S.top(); S.pop();
      bcc.back().push_back(e);
    }
  }

  void dfs(int v, int p) {
    pre[v] = low[v] = ++TIMER;

    int children = 0;
    bool low_child = false;

    for (auto u : G[v]) {
      if (u == p) continue;
      if (pre[u] == -1) {
        S.push({v, u});
        dfs(u, v);
        children++;

        low[v] = min(low[v], low[u]);
        if (low[u] >= pre[v]) {
          low_child = true;
          make_bcc({v, u});
        }
      } else {
        low[v] = min(low[v], pre[u]);
      }
    }

    if ((p == -1 && children >= 2) || (p != -1 && low_child))
      art.push_back(v);
  }


  BlockCutTree(vector<vector<int>> const& G) : G(G), N(size(G)) {
    pre.assign(N, -1);
    low.assign(N, -1);
    for (int i = 0; i < N; i++) {
      if (pre[i] == -1) {
        dfs(i, -1);
      }
    }

    is_art.resize(N, false);
    for (auto v : art) is_art[v] = true;

    BCT.resize(N + size(bcc));
    comp.resize(N);
    for (int i = 0; i < size(bcc); i++) {
      for (auto [v, u] : bcc[i]) {
        if (is_art[v] && (empty(BCT[v]) || BCT[v].back() != N+i)) BCT[v].push_back(N+i), BCT[N+i].push_back(v);
        if (is_art[u] && (empty(BCT[u]) || BCT[u].back() != N+i)) BCT[u].push_back(N+i), BCT[N+i].push_back(u);
        comp[v] = comp[u] = N+i;
      }
    }

    for (auto v : art) comp[v] = v;
  }
};
//}}}