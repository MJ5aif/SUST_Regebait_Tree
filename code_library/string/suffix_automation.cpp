// Suffix Automaton (SAM)
// Handles all substrings of a string in linear time
struct State {
  int next[26];
  int link, len;
  State() {
    memset(next, -1, sizeof next);
    link = -1;
    len = 0;
  }
};
vector<State> st;
int last;
void sa_init() {
  st.clear();
  st.push_back(State());
  last = 0;
}
// extend by character c
void sa_extend(char ch) {
  int c = ch - 'a';
  int cur = st.size();
  st.push_back(State());
  st[cur].len = st[last].len + 1;
  int p = last;
  while (p != -1 && st[p].next[c] == -1) {
    st[p].next[c] = cur;
    p = st[p].link;
  }
  if (p == -1) {
    st[cur].link = 0;
  } else {
    int q = st[p].next[c];
    if (st[p].len + 1 == st[q].len) {
      st[cur].link = q;
    } else {
      int clone = st.size();
      st.push_back(st[q]);
      st[clone].len = st[p].len + 1;
      while (p != -1 && st[p].next[c] == q) {
        st[p].next[c] = clone;
        p = st[p].link;
      }
      st[q].link = st[cur].link = clone;
    }
  }
  last = cur;
}
// count distinct substrings
int64_t count_distinct() {
  int64_t ans = 0;
  for (auto& s : st) ans += s.len - (s.link == -1 ? 0 : st[s.link].len);
  return ans;
}