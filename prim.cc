#include <cstdio>
#include <cstring>

using namespace std;

const int Nmax = 10005;
const int Mmax = 50005;

struct Node {
    Node(int _id = 0, int _cost = 0) : id(_id), cost(_cost) {}
    int id, cost;
    bool operator < (const Node &rhs) {
        return cost < rhs.cost;
    }
}heap[Nmax];

int top;

struct Edge {
    int to, cost, next;
}edge[Mmax << 1];

int cnt = 0, pEdge[Nmax];

void addEdge(int t1, int t2, int cost) {
    edge[cnt].to = t2;
    edge[cnt].cost = cost;
    edge[cnt].next = pEdge[t1];
    pEdge[t1] = cnt++;
}

int pos[Nmax], ans;

void init(int n) {
    memset(pEdge, -1, sizeof(int) * n);
    memset(pos, 0, sizeof(int) * n);
    top = 1;
    cnt = 0;
    ans = 0;
}

void heapify(int index) {
    Node tmp = heap[index];
    while(index << 1 < top) {
        int swp = index << 1;
        if(swp + 1 < top && heap[swp + 1].cost < heap[swp].cost)
            swp++;
        if(heap[swp].cost < tmp.cost) {
            heap[index] = heap[swp];
            pos[heap[swp].id] = index;
            index = swp;
        }
        else break;
    }
    heap[index] = tmp;
    pos[tmp.id] = index;
}

void pop(Node &now) {
    now = heap[1];
    heap[1] = heap[--top];
    if(top > 1) heapify(1);
}

void descrease(int index, int cost) {
    if(heap[index].cost <= cost) return;
    Node tmp = heap[index];
    while(index >> 1) {
        if(cost < heap[index >> 1].cost) {
            heap[index] = heap[index >> 1];
            pos[heap[index].id] = index;
            index >>= 1;
        }
        else break;
    }
    tmp.cost = cost;
    heap[index] = tmp;
    pos[tmp.id] = index;
}

void push(int id, int cost) {
    heap[top].id = id;
    heap[top].cost = cost + 1;
    descrease(top++, cost);
}

int main() {
    int k;
    scanf("%d", &k);
    while(k--) {
        int n, m;
        scanf("%d%d", &n, &m);
        init(n);
        while(m--) {
            int t1, t2, cost;
            scanf("%d%d%d", &t1, &t2, &cost);
            addEdge(--t1, --t2, cost);
            addEdge(t2, t1, cost);
        }
        heap[top++] = Node(0, 0);
        Node now;
        while(top > 1) {
            pop(now);
            pos[now.id] = -1;
            ans += now.cost;
            for(int i = pEdge[now.id]; i != -1; i = edge[i].next) {
                int to = edge[i].to, cost = edge[i].cost;
                if(pos[to] != -1) {
                    if(pos[to])
                        descrease(pos[to], cost);
                    else
                        push(to, cost);
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
