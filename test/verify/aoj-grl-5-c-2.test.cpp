#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C"

#include "../../template/template.cpp"
#include "../../graph/template.cpp"

#include "../../graph/tree/heavy-light-decomposition.cpp"

int main() {
  int N, Q;
  scanf("%d", &N);
  UnWeightedGraph g(N);
  HeavyLightDecomposition< UnWeightedGraph > tree(g);
  for(int i = 0; i < N; i++) {
    int k;
    scanf("%d", &k);
    for(int j = 0; j < k; j++) {
      int c;
      scanf("%d", &c);
      g[i].push_back(c);
    }
  }
  tree.build();
  scanf("%d", &Q);
  for(int i = 0; i < Q; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    printf("%d\n", tree.lca(u, v));
  }
}
