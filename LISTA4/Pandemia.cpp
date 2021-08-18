#include <bits/stdc++.h>
#define endl '\n'
#define ll int

using namespace std;

typedef struct Hospital{
    ll id;
    ll cases;
}Hospital;


class Heap {
    public:
        ll size;
        ll pos[230000] = {};
        bool active[230000] = {};
        Hospital h[230000];
        
        Heap(ll s){
            size = s;
        }

        bool priority(Hospital h1, Hospital h2){
            if(h1.cases > h2.cases){
                return true;
            }else if(h1.cases == h2.cases){
                if(h1.id > h2.id){
                    return true;
                }
                return false;
            }else{
                return false;
            }
        }

        void swap(ll i, ll m){
            ll p;
            p = pos[h[i].id];
            pos[h[i].id] = pos[h[m].id];
            pos[h[m].id] = p;

            Hospital aux;
            aux = h[i];
            h[i] = h[m];
            h[m] = aux;
        }

        void heapify(ll i){
            ll m = i, l = 2*i + 1, r = 2*i + 2;

            if(l < size && priority(h[l], h[m])){
                m = l;
            }
            if(r < size && priority(h[r], h[m])){
                m = r;
            }
            if(m != i){
                swap(i, m);
                heapify(m);
            }
        }

        void print(){
            if(size != 0){
                cout << h[0].id << " " << h[0].cases << endl;
            }else{
                cout << "-1 -1" << endl;
            } 
        }

        void build(){
            for(ll i = (floor(size/2) - 1); i >= 0; i--){
                heapify(i);
            }
        }   


        void bubble_up(ll i){
            ll f = floor((i-1)/2);  
            while(i > 0 && priority(h[i], h[f])){
                swap(i, f);
                i = f;
                f = floor((i-1)/2);
            }
        }

        void extract(ll id){
            ll p = pos[id];
            swap(p, size-1);
            size--;
            bubble_up(p);
            heapify(p); 
        }

        void insert(ll id, ll cases){
            h[size].id = id;
            h[size].cases = cases;
            pos[id] = size;
            active[id] = true;
            size++;
            bubble_up(size - 1);
        }

};


void menu(){
    bool esc = 0;
    ll n, cases, id, r;
    string cmd;

    cin >> n;

    Heap heap = Heap(n);

    for(ll i = 0; i < n; i++){
        ll c;
        heap.h[i].id = i;
        cin >> c;
        heap.h[i].cases = c;
        heap.pos[i] = i;
        heap.active[i] = true;
    }

    heap.build();

    while(!esc){
        cin >> cmd;
        if(cmd == "NEW"){
            cin >> id >> cases;
            if (!heap.active[id]) heap.insert(id, cases);
            heap.print();
        }else if(cmd == "DEL"){
            cin >> id;
            if(heap.active[id]){
              heap.active[id] = false;
              heap.extract(id);
            }
            heap.print();
        }else if(cmd == "IN"){
            cin >> id >> cases;
            ll p = heap.pos[id];
            heap.h[p].cases += cases;
            cout << heap.h[p].cases << endl;
            heap.bubble_up(p);
        }else if(cmd == "OUT"){
            cin >> id >> cases;
            ll p = heap.pos[id];
            heap.h[p].cases -= cases;
            if(heap.h[p].cases < 0){
                heap.h[p].cases = 0;
            }
            heap.heapify(p);
            p = heap.pos[id];
            cout << heap.h[p].cases << endl;
        }else if(cmd == "PAY"){
            cin >> r;
            ll p = 0;
            while(r > 0 && heap.h[0].cases > 0){
                r--;
                heap.h[0].cases--;
                heap.heapify(0);
                p++;
            }
            cout << p << endl;
        }else{
            esc = true;
        }
    }

    ll total = 0;    
    for(ll i = 0; i < heap.size; i++){
        total += heap.h[i].cases;
    }

    cout << total << endl;
}

int main() { 

    menu();

}
