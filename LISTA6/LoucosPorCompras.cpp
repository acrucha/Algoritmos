#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

// int counter = 0;

int backtrack(int *p, int l, int q, int m, int t, int s, int n){
    // counter++;
    int ans = 0;
    if(t == l){
        if(n >= m && s <= q){
            ans++;
        }
        return ans;
    }
    if(s > q){
        return ans;
    }
    for(int j = 1; j >= 0; j--){ 
        ans += backtrack(p, l, q, m, t+1, s + (j * p[t]), n+j);
    }
    return ans;

}

void solve(int c){
    int l, m, q, p[33] = {}, ans = 0;

    cin >> l;

    for(int i = 0; i < l; i++){
        cin >> p[i];
    }
    // sort(p, p + l, greater<int>());

    cin >> m >> q;

    ans = backtrack(p, l, q, m, 0, 0, 0);
    cout << "caso " << c << ": " << ans << endl;

};


int main(){
    int k, i = 0; 

    cin >> k;
    
    cin.ignore(1);
    while(k--){
        solve(i);
        i++;
    }

    // cout << "counter: " << counter << endl;
}