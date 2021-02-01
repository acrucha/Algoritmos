#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

typedef struct No{
    string url;
    No *next;
}No;

// function that inserts a new node to the list according to the received node (head)
void list_insert(No *head, string url){ 
    No *newNo = new No(), *cur = head;  // creating a new node and making a head's copy
    newNo->url = url;                   // assigning the current url to the new node's url
    newNo->next = cur->next;            // now, the new node is head's next node (because we must add the new node at the top of the list)
    head->next = newNo;                 // and, finally, the head's next node is the new node
}

// function that inserts a node at the bottom of the list
void list_save(No *saves, string url){
    No *newNo = new No(), *cur = saves; // the cur is the list of saved nodes
    while(cur->next != NULL){           // this while runs through the entire list to the end
        cur = cur->next;                // so the current node is at the end of the list
    }
                                        // calling the function that inserts a node to the list
    list_insert(cur, url);              // in this case, exceptionally, the sended node is not the actually the list head
                                        // it happens because we want to insert a node at the last position, so we send the last node
}

// function that deletes the first node of the list
void list_delete(No *head){
    No *prox = head->next;              // assigning the head next node to an auxiliary node (prox)
    head->next = prox->next;            // the new head next node is the prox next node
    delete(prox);                       // deleting the prox node and freeing memory
}

// function that deletes all nodes of the list, that is, clean the entire list
void panic(No *head){
    while(head->next != NULL){          // this while runs through the entire list to the end
        list_delete(head);              // deleting the current node
    }
}

void menu(No *head, No *saves){
    int escape = 0, size = 0, not_read = 0;
    string command, url;
    while (escape==0){                  // runs while the "escape" is not true
        cin >> command;
        switch (command[0]){
            case 'O':                   // add a node with this url to the list and returns the list size
                cin >> url;
                list_insert(head, url); // call the function that insert a node 
                size++;                 // increases the size
                cout << size << endl;   
                break;
            case 'C':                   // print the current head next url of the list (the node at the top of the list)
                if(size==0) cout << "NULL" << endl;
                else cout << (head->next)->url << endl;
                break;    
            case 'B':                   // remove the current node, the node at the top of the list, and print the new first url (if the list is empty, print NULL)
                if(size==0) cout << "NULL" << endl;
                else{
                    list_delete(head);  // call the function that delete a node 
                    size--;             // decreases the size
                    if(size>0) cout << (head->next)->url << endl;
                    else cout << "NULL" << endl;
                }
                break;
            case 'P':
                panic(head);            // call the function to clear the list and print the number of deleted nodes
                cout << size << endl;
                size = 0;
                break;
            case 'S':                   // insert the current node to the saves list and print the size of the saves list
                if(size>0){
                  list_save(saves, (head->next)->url);
                  not_read++;
                }            
                cout << not_read << endl;
                break;
            case 'R':                   // remove the last node of saves list and print the url (if the saves list is empty, print NULL)
                if(not_read==0) cout << "NULL" << endl;
                else{
                  cout << (saves->next)->url << endl;
                  list_delete(saves);
                  not_read--;
                }
                break;  
            case 'E':                   // get out the menu function
                escape = 1;
                break;
            default:
                break;
        }
    }
}

int main(){
    // creating the lists
    No *head = new No(), *saves = new No();
    head->url = "head";                 // the head node doesn't really have a value, it just points to the first node
    head->next = NULL;                  // i assigned the value "head" to head->url just to initialize it with default value (will not be used)
    saves->url = "saves";
    saves->next = NULL;
    menu(head, saves);                  // enter the menu of the program

    panic(head);                        // freeing memory 
    panic(saves);                       // freeing memory 

    return 0;
}