/// USAGE
adj.resize(n);
for(int i = 0; i < edges.size(); i++) {
  auto [u, v] = edges[i];
  adj[u].push_back({v, i});
  adj [v].push_back({u, i});
}

vector<vector<int>> components;
bicomps(n, [&](vi& comp) {
  components.push_back(comp);
});
///////////////////////////////////


vector<vector<pair<int,int>>> adj;   // adj[u] = {(v, edge_id), ...}
vector<int> num, isArt;
vector<pair<int,int>> bridges;      // {u, v} for each bridge
vector<int> st;           // edge stack
int Time = 0;

template <class F>
int dfs(int at, int par, F& f) {
  int me = num[at] = ++Time;
  int top = me;
  int children = 0;
  for (auto [y, e] : adj[at]) {
    if (e == par) continue;
    if (num[y]) {
      top = min(top, num[y]);
      if (num[y] < me) st.push_back(e);   // back edge
    } else {
      children++;
      int si = st.size();
      int up = dfs(y, e, f);
      top = min(top, up);
      if (par != -1 && up >= me) isArt[at] = 1;
      if (up > me) bridges.push_back({at, y});
      if (up >= me) {
        st.push_back(e);
        vi comp(st.begin() + si, st.end());
        f(comp);
        st.resize(si);
      } else {
        st.push_back(e);
      }
    }
  }
  if (par == -1 && children > 1) isArt[at] = 1;
  return top;
}

template <class F>
void bicomps(int n, F f) {
  adj.resize(n);
  num.assign(n, 0);
  isArt.assign(n, 0);
  bridges.clear();
  st.clear();
  Time = 0;
  for(int i = 0; i < n; i++) if (!num[i]) dfs(i, -1, f);
}