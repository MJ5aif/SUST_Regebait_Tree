struct FT2 {
  vector<vector<ll>> ys; 
  vector<FT> ft;
  FT2(int limx) : ys(limx + 1) {}
  void fakeUpdate(int x, int y) {
    for (; x < ys.size(); x += x & -x) {
      ys[x].push_back(y);
    }
  }
  void init() {
    ft.clear();
    ft.resize(ys.size(), FT(0));
    for (int i = 0; i < ys.size(); ++i) {
      sort(ys[i].begin(), ys[i].end());
      ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());
      ft[i] = FT(ys[i].size());
    }
  }
  int update(int x, int y) {
    return lower_bound(ys[x].begin(), ys[x].end(), y - ys[x].begin()) + 1; 
  }
  int query(int x, int y) {
    return upper_bound(ys[x].begin(), ys[x].end(), y) - ys[x].begin();
  }
  void update(int x, int y, ll dif) {
    for (; x < ys.size(); x += x & -x)
      ft[x].update(update(x, y), dif);
  }
  ll query(int x, int y) {
    ll sum = 0;
    for (; x > 0; x -= x & -x) {
      sum += ft[x].query(query(x, y));
    }
    return sum;
  }
  ll query(ll x1, ll y1, ll x2, ll y2) {
    return (query(x2,y2) - query(x1-1, y2) - 
            query(x2, y1-1) + query(x1-1, y1-1) + 
            5ll*MOD) % MOD;
  }
};