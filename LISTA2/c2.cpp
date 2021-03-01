#include <bits/stdc++.h>

#define endl '\n'
#define ll long long
#define W 32
#define L 0.5
#define power 4294967296

using namespace std;

typedef struct rehash
{
    bool re;
    bool stopType;
}rehash;

class HashTable {
    public:
        ll M, A;
        double R;
        int n;
        ll *table = NULL;

        HashTable(ll mM, ll mA){
            n = 0;
            M = mM;
            A = mA;
            R = log(mM)/log(2);
            table = new ll[mM];
        }

        void create(int x){
            ll *temp = new ll[x];
            table = temp;
            for(int i = 0; i < x; i++){
                table[i] = 0;
            }
            delete(temp);
        }

        ll hashFunction(ll x){
            ll ans = (A*x) % power >> (W - ((int) R));
            return ans;
        }

        ll insert(ll x){
            ll index = hashFunction(x);
            if(table[index] == 0){
                table[index] = x;
                return index;
            }else{
                ll aux = 0;
                aux = table[index];
                table[index] = x;
                return aux;                                                             
            }
        }

        ll find(ll x){
            ll index = hashFunction(x);
            if(table[index] == x){
                return index;
            }else{
                return -1;
            }
        }

        void show(){
            for(int i = 0; i < M; i++){
                cout << i + 1 << ". " << table[i] << endl;
            }
        }

};


bool search(ll id, HashTable *tables){
    ll index;

    for(int i = 0; i < 2; i++){
        index = tables[i].find(id);
        if(index != -1){
            cout << "FAIL"<< endl;
            return true;
        }
    }
    return false;
}

void testInsert(HashTable *table, ll *id, int j, bool t, rehash *r){
    ll index = table[t].insert(*id);
    double F = (double)(table[t].n)/(double)(table[t].M);
    if(F <= L){
        table[t].n++;
    }else{
        r->re = true;
        r->stopType = 1;    //não sobrou id
        table[t].n = 0;
    }
    *id = index;
}

void put(ll *id, HashTable *tables, rehash *r, bool print){
    bool t = 0;
    int j;

    if(!search(*id, tables)){
        for(j = 0; j < tables[0].M && !r->re; j++){
            ll i = tables[t].hashFunction(*id);
            testInsert(tables, id, j, t, r);
            // if(j == 0 && print)
            //     cout << "OK " << t << " " << i << endl;
            if(i == *id) break;
            t = !t;
        }
        if(j == tables[t].M){
            r->re = true;
            r->stopType = 0;    //sobrou 1 id
        } 
    }
}

void reHashing(int M, HashTable *tables, ll *id, rehash *r){
    HashTable newTables[2] = { HashTable(M, tables[0].A), HashTable(M, tables[1].A) };
    ll x;
    rehash cur;
    cur.re = false;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < tables[0].M; j++){
            x = tables[i].table[j];
            if(x != 0) {
                put(&x, newTables, &cur, false);
                if(cur.re) reHashing(2*M, tables, id, r);
            }
        }
    }
    if(!r->stopType){
        put(id, newTables, &cur, false);
        if(cur.re) reHashing(2*M, tables, id, r);
    }
    r->re = false; 
    for(int i = 0; i < 2; i++){
        ll *aux;
        aux = tables[i].table;
        tables[i].table = newTables[i].table;
        tables[i].M = newTables[i].M;
        tables[i].R = newTables[i].R;
        tables[i].A = newTables[i].A;
        delete(aux);
    }
    // tables[0].show();
    // tables[1].show();
}

void check(ll id, HashTable t[]){
    ll index;

    for(int i = 0; i < 2; i++){
        index = t[i].find(id);
        if(index != -1){
            cout << "OK " << i << " " << index << endl;
            return;
        }
    }

    cout << "FAIL"<< endl;
}

void menu(){
    bool escape = false;
    rehash r;
    r.re = false;
    r.stopType = 0;

    int M;
    ll A0, A1, id, id0;
    string command;

    cin >> M >> A0 >> A1;

    HashTable tables[2] = { HashTable(M, A0), HashTable(M, A1) };

    while (escape == false){
        cin >> command; 
        switch (command[0]){
            case 'I':  
                cin >> id;
                id0 = id;
                put(&id, tables, &r, true);
                if(r.re){
                    M = 2*(tables[0].M);
                    reHashing(M, tables, &id, &r);
                }
                check(id0, tables);
                break;                 
            case 'Q':                  
                cin >> id;
                check(id, tables);
                break;
            case 'E':
                escape = true;
                break;
            default:
                break;
        }
    }

}

int main() { 

    menu();

}
