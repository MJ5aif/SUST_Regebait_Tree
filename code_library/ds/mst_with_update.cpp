// 0 based indexing
template <typename T>
struct MST {
  int n;
  vector<ordered_set<pair<T, int>>> tree;
  vector<T> a;
  MST(vector<T>& v) : a(v) {
    n = v.size();
    tree.resize(4 * n);
    build(0, 0, n - 1, a);
  }
  void merge(int u, int l, int r) {
    tree[u] = tree[l];
    for (auto x : tree[r]) tree[u].insert(x);
  }
  void build(int u, int l, int r, vector<T>& a) {
    if (l == r) {
      tree[u].insert({a[l], l});
      return;
    }
    int mid = (l + r) / 2;
    build(2 * u + 1, l, mid, a);
    build(2 * u + 2, mid + 1, r, a);
    merge(u, 2 * u + 1, 2 * u + 2);
  }
  // Returns number of elements smaller than x in range l, r
  int query(int l, int r, T x) { return get(0, 0, n - 1, l, r, x); }
  void update(int i, T x) {
    _update(0, 0, n - 1, i, x);
    a[i] = x;
  }
  int get(int u, int tl, int tr, int l, int r, T x) {
    if (tl >= l && tr <= r) return tree[u].order_of_key({x, 0});
    if (tl > r || tr < l) return 0;
    int mid = (tl + tr) / 2;
    return get(2 * u + 1, tl, mid, l, r, x) +
           get(2 * u + 2, mid + 1, tr, l, r, x);
  }
  void _update(int u, int l, int r, int i, T x) {
    tree[u].erase({a[i], i});
    tree[u].insert({x, i});
    if (l == r) return;
    int mid = (l + r) / 2;
    if (i <= mid)
      _update(2 * u + 1, l, mid, i, x);
    else
      _update(2 * u + 2, mid + 1, r, i, x);
  }
};