#include <bits/stdc++.h>
#define endl '\n'
#define INF 1000000000
#define minim(a,b) a<b?a:b

using namespace std;

typedef struct No{
    int v;
    int w;
    No *next;
}No;

typedef struct Node{
    int v;
    int d;
}Node;

class Queue {
    public:
   
        No* head = NULL;
        No* tail = NULL;

        void Enqueue(int v, int w) {
            No* temp = new No();
            temp->w = w; 
            temp->v = v;
            temp->next = NULL;
            if(head == NULL && tail == NULL){
                head = tail = temp;
                return;
            }
            tail->next = temp;
            tail = temp;
        }

        bool isEmpty() {
            if(head == NULL) return true;
            return false;
        }

        void Dequeue() {
            No* temp = head;
            if(head == tail) {
                head = tail = NULL;
            }
            else {
                head = head->next;
            }
            delete(temp);
        }


};

class Graph{
    public: 
        int v, n, *y = NULL;
        Queue *nodes[23000];
        
        Graph(int v0, int n0){
            v = v0;
            n = n0;
            for(int i = 0; i < v0; i++){
                nodes[i] = new Queue();
            }
            y = new int[n0];
        }
};

class Min_heap {
    public:
        int size;
        int pos[230000] = {};
        bool act[230000];
        Node graph[230000];
        
        Min_heap(int s){
            size = s;
        }

        void swap(int i, int m){
            int p;
            p = pos[graph[i].v];
            pos[graph[i].v] = pos[graph[m].v];
            pos[graph[m].v] = p;

            Node aux;
            aux = graph[i];
            graph[i] = graph[m];
            graph[m] = aux;
        }

        void heapify(int i){
            int m = i, l = 2*i + 1, r = 2*i + 2;

            if(l < size && graph[l].d < graph[m].d){
                m = l;
            }
            if(r < size && graph[r].d < graph[m].d){
                m = r;
            }
            if(m != i){
                swap(i, m);
                heapify(m);
            }
        }

        void bubble_up(int i){
            int f = floor((i-1)/2);  
            while(i > 0 && graph[i].d < graph[f].d){
                swap(i, f);
                i = f;
                f = floor((i-1)/2);
            }
        }

        Node extract(){
            Node n;
            n = graph[0];
            act[n.v] = false;
            swap(0, size-1);
            size--;
            heapify(0); 
            return n;
        }

        void insert(int v, int d){
            graph[size].v = v;
            graph[size].d = d;
            act[v] = true;
            pos[v] = size;
            size++;
            bubble_up(size - 1);
        }

        void update(int v, int d){
            graph[pos[v]].d = d;
            bubble_up(pos[v]);
            heapify(pos[v]);
        }

};


int *dijkstra(Graph g, int x){
    int *d = new int[g.v];
    bool vis[g.v] = {};
    Min_heap heap = Min_heap(0);

    for(int j = 0; j < g.v; j++) d[j] = INF;

    d[x] = 0;
    heap.insert(x, d[x]);

    No *e = NULL;
    Node n;
    for(int i = 0; i < g.v; i++){
        n = heap.extract();
        vis[n.v] = true;
        e = g.nodes[n.v]->head; // u == n.v
        while(e != NULL){
            int v = e->v;
            int w = e->w;
            if(n.d + w < d[v] && vis[v] == false){
                d[v] = n.d + w;
                if(heap.act[v]){
                    heap.update(v, d[v]);   
                }else{
                    heap.insert(v, d[v]);
                }
            }
            e = e->next;
        }
    }

    return d;
}

int **min_dist(Graph g){
    int **d = new int*[g.v];

    for(int i = 0; i < g.n; i++){
        d[g.y[i]] = dijkstra(g, g.y[i]);
        d[g.y[i]][g.y[i]] = 0;
    }

    return d;
}

int totalDistance(int x, int z, int **dist, int *y, int *restaurants, int n){
    int distance = INF;

    for(int i = 0; i < n; i++){
        int r = restaurants[i];
        int d = dist[r][x] + dist[r][z];
        if(d <= distance){
            if(distance == d){
                *y = minim(*y, r);
            }else{
                distance = d;
                *y = r;
            }
        }
    }

    return distance;
}


void menu(){
    int v, e, n, m, nOrders = 0, currentOrder = 0, **dist = NULL;
    int orders[230000] = {}; // recebe o id e diz o local
    cin >> v >> e >> n >> m; 
    bool esc = false;
    int dlv[m] = {};
    Graph g = Graph(v, n);
    for(int i = 0; i < e; i++){
        int a, b, w;
        cin >> a >> b >> w;
        g.nodes[a]->Enqueue(b, w);
        g.nodes[b]->Enqueue(a, w);
    }
    for(int i = 0; i < n; i++){
        int y1;
        cin >> y1;
        g.y[i] = y1;
    }
    for(int i = 0; i < m; i++){
        dlv[i] = g.y[0];
    }
    dist = min_dist(g);

    string cmd;
    while(!esc){
        cin >> cmd;
        if(cmd == "NEW"){
            int id, z; cin >> id >> z;
            orders[id] = z;
            nOrders++;
            cout << "+" << id << " " << nOrders << endl;
        }else if(cmd == "CEL"){
            int id; cin >> id;
            nOrders--;
            orders[id] = -1;
            cout << "-" << id << " " << nOrders << endl;
        }else if(cmd == "DLV"){
            int id, x, y, z, k, d; cin >> d;
            while(orders[currentOrder] == -1){
                currentOrder++;
            }
            id = currentOrder;
            z = orders[id];
            x = dlv[d];
            dlv[d] = z;
            currentOrder++;
            nOrders--;
            k = totalDistance(x, z, dist, &y, g.y, n);
            cout << id << " " << x << " " << y << " " << z << " " << k << endl;
        }else{
            esc = true;
        }
    }


}

int main() { 

    menu();

}
