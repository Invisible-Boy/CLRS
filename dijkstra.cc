#include <cstdio>
#include <cstring>

using namespace std;

const int Nmax = 1005;
const int Mmax = 105;

struct Edge {
    Edge(int _to = 0, int _cost = 0, int _next = -1) : to(_to), cost(_cost), next(_next) {}
    int to, cost, next;
}edge[Nmax << 2];

struct Node : public Edge {
    Node(int _to = 0, int _cost = 0, int _next = 0, int _pre = -1) : Edge(_to, _cost, _next), pre(_pre) {}
    int pre;
}buck[Nmax << 2];

int cnt, tot;
int pEdge[Nmax], pBuck[Mmax], mask, T, N, dist[Nmax], pos[Nmax];

void addEdge(int t1, int t2, int cost) {
    edge[cnt].cost = cost;
    edge[cnt].to = t2;
    edge[cnt].next = pEdge[t1];
    pEdge[t1] = cnt++;
}

void insert(int now, int cost) {
    pos[now] = tot;
    dist[now] = cost;
    buck[tot].cost = cost;
    cost %= mask;
    buck[tot].next = pBuck[cost];
    buck[tot].to = now;
    if(pBuck[cost] > -1) buck[pBuck[cost]].pre = tot;
    pBuck[cost] = tot++;
}

void change(int now, int cost) {
    Node &nnow = buck[pos[now]];
    if(nnow.pre == -1)
        pBuck[nnow.cost % mask] = nnow.next;
    else
        buck[nnow.pre].next = nnow.next;
    buck[nnow.next].pre = nnow.pre;
    dist[now] = cost;
    now = pos[now];
    buck[now].cost = cost;
    cost %= mask;
    buck[now].next = pBuck[cost];
    if(pBuck[cost] > -1) buck[pBuck[cost]].pre = now;
    buck[now].pre = -1;
    pBuck[cost] = now;
}

inline int max(int t1, int t2) {
    return t1 > t2 ? t1 : t2;
}

void init() {
    cnt = tot = mask = 0;
    memset(pEdge, -1, sizeof(pEdge));
    memset(pBuck, -1, sizeof(pBuck));
    memset(pos, -1, sizeof(pos));
    scanf("%d%d", &T, &N);
    for(int i = 0; i < T; i++) {
        int t1, t2, cost;
        scanf("%d%d%d", &t1, &t2, &cost);
        addEdge(--t1, --t2, cost);
        addEdge(t2, t1, cost);
        mask = max(mask, cost);
    }
    mask++;
    insert(N - 1, 0);
}

int main() {
    init();
    while(!dist[0]) {
        for(int i = 0; i < mask; i++) {
            for(int j = pBuck[i]; j != -1; j = buck[j].next) {
                Node &now = buck[j];
                pos[now.to] = -2;
                for(int k = pEdge[now.to]; k != -1; k = edge[k].next) {
                    Edge &enow = edge[k];
                    if(pos[enow.to] < -1) continue;
                    else if(pos[enow.to] == -1)
                        insert(enow.to, enow.cost + now.cost);
                    else if(now.cost + enow.cost < dist[enow.to])
                        change(enow.to, now.cost + enow.cost);
                }
            }
            pBuck[i] = -1;
        }
    }
    printf("%d\n", dist[0]);
    return 0;
}
