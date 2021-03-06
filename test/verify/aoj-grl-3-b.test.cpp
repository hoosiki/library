#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B"

#include "../../template/template.cpp"
#include "../../graph/template.cpp"

#include "../../graph/others/lowlink.cpp"

int main() {
  int V, E;
  scanf("%d %d", &V, &E);
  UnWeightedGraph g(V);
  for(int i = 0; i < E; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  LowLink< UnWeightedGraph > lowlink(g);
  lowlink.build();
  sort(lowlink.bridge.begin(), lowlink.bridge.end());
  for(auto &p : lowlink.bridge) printf("%d %d\n", p.first, p.second);
}
