#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

typedef struct Node{
    int value;
    Node *left; 
    Node *right; 
}Node;

Node* bst_insert(Node *root, int v, int level){
    if(root == NULL){
        Node *n = new Node();
        n->value = v;
        n->left = NULL;
        n->right = NULL;
        cout << level << endl;
        return n;
    }else if(v < root->value){
        level++;
        root->left = bst_insert(root->left, v, level);
        return root;
    }else{
        level++;
        root->right = bst_insert(root->right, v, level);
        return root;
    }
}

Node *bst_delete_min(Node *root, int *min){
    if(root != NULL){
        if(root->left != NULL){
            root->left = bst_delete_min(root->left, min);
            return root;
        }else{
            Node *n = new Node();
            n = root->right;
            *min = root->value;
            delete(root);
            return n;
        }
    }else{
        return root;
    }
}

Node* bst_delete(Node *root, int v, bool print, int level){
    if(root == NULL){
        return NULL;
    }else{
        if(v < root->value){
            level++;
            root->left = bst_delete(root->left, v, print, level);
            return root;
        }else if(v > root->value){
            level++;
            root->right = bst_delete(root->right, v, print, level);
            return root;
        }else{  //v == root->value
            if(print) cout << level << endl;
            Node *n = new Node();
            if(root->left == NULL){
                n = root->right;
                delete(root);
                return n; 
            }else if(root->right == NULL){
                n = root->left;
                delete(root);
                return n; 
            }else{
                int min;
                n = bst_delete_min(root->right, &min);
                root->right = n;
                root->value = min;
                return root;
            }
        }
    }
}

Node* bst_search(Node *root, int v) {
    if(root == NULL){
        return NULL;
    }else{
        if(v == root->value){        
            return root;
        }else if(v < root->value){
            return bst_search(root->left, v);
        }else{
            return bst_search(root->right, v);
        }
    }
}

Node *rotate_right(Node *root){
    Node *r = new Node(), *l = new Node();
    l = root->left;
    r = l->right;
    root->left = r;
    l->right = root;

    return l;
}

Node *rotate_left(Node *root){
    Node *r = new Node(), *l = new Node();
    r = root->right;
    l = r->left;
    root->right = l;
    r->left = root;

    return r;
}

void pre_order(Node *root){
    if (root != NULL){
        cout << root->value << endl;
        pre_order(root->left);
        pre_order(root->right);
    }
}

Node *stocked(Node *root, int v){
    Node *r = NULL;
    r = bst_search(root, v);
    if(r != NULL){
        return bst_delete(root, v, true, 0);
    }

    cout << "NULL" << endl;

    return root;
}

Node* bst_search_son(Node *root, int v, bool *found, int level) {
    if(root != NULL){
        level++;
        if(v < root->value){
            if(root->left != NULL){
                if(root->left->value == v){
                    root = rotate_right(root);
                    //print
                    cout << level << endl;
                    return root;
                }
            }
            root->left = bst_search_son(root->left, v, found, level);
            return root;
        }else{
            if(root->right != NULL){
                if(root->right->value == v){
                    root = rotate_left(root);
                    cout << level << endl;
                    return root;
                }
            }
            root->right = bst_search_son(root->right, v, found, level);       
            return root;
        }
    }else{
        *found = false;
        return NULL;
    }
}

Node *emergency(Node *root){
    if(root != NULL){
        cout << root->value << " ";
        root = bst_delete(root, root->value, false, 0);
        if(root != NULL){
            cout << root->value << endl;
        }else{
            cout << "-1" << endl;
        }
    }else{
        cout << "-1 -1" << endl;
    }

    return root;
}

Node *sold(Node *root, int v){
    if(root != NULL){
        if(root->value == v){
            cout << "0" << endl;
            return root;
        }
    }
    bool found = true;
    root = bst_search_son(root, v, &found, -1);
    if(!found){
        root = bst_insert(root, v, 0);
    }
    return root;
}

void menu(){
    Node *root = NULL;
    bool escape = false;
    string command;
    int v;
    while (escape == false){
        cin >> command; 
        if(command == "SLD"){
            cin >> v;
            root = sold(root, v);
        }else if(command == "STK"){
            cin >> v;
            root = stocked(root, v);
        }else if(command == "EMG"){
            root = emergency(root);
        }else{
            escape = true;
        }
    }
    pre_order(root);
}

int main() { 

    menu();

}
