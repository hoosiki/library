#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450"

#include "../../template/template.cpp"
#include "../../graph/template.cpp"

#include "../../structure/segment-tree/lazy-segment-tree.cpp"

#include "../../graph/tree/heavy-light-decomposition.cpp"

int main() {
  int N, Q, S[200000];
  cin >> N >> Q;
  for(int i = 0; i < N; i++) {
    cin >> S[i];
  }
  UnWeightedGraph g(N);
  HeavyLightDecomposition< UnWeightedGraph > tree(g);
  for(int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  tree.build();

  struct Node {
    int64 ans, all, left, right, length;

    Node() : ans(-infll), all(0), left(-infll), right(-infll), length(0) {}

    Node(int64 val, int64 len) {
      length = len;
      all = val * length;
      ans = left = right = (val > 0 ? all : val);
    }

    Node operator+(const Node &s) const {
      Node ret;
      ret.length = length + s.length;
      ret.ans = max({ans, s.ans, right + s.left});
      ret.all = all + s.all;
      ret.left = max(left, all + s.left);
      ret.right = max(s.right, right + s.all);
      return ret;
    }
  };
  auto F = [](const Node &a, const Node &b) { return a + b; };
  auto G = [](const Node &a, int64 x) { return Node(x, a.length); };
  auto H = [](int64 x, int64 y) { return y; };
  LazySegmentTree< Node, int64 > seg(N, F, G, H, Node(), infll);
  for(int i = 0; i < N; i++) seg.set(i, Node(S[tree.rev[i]], 1));
  seg.build();

  auto QF = [&](int a, int b) { return seg.query(a, b); };
  auto QG = [](const Node &a, const Node &b) { return a + b; };
  auto QS = [](Node l, const Node &r) {
    swap(l.left, l.right);
    return l + r;
  };


  while(Q--) {
    int T, A, B, C;
    cin >> T >> A >> B >> C;
    --A, --B;
    if(T == 1) {
      tree.add(A, B, [&](int a, int b) { seg.update(a, b, C); });
    } else {
      cout << tree.query(A, B, Node(), QF, QG, QS).ans << "\n";
    }
  }
}

