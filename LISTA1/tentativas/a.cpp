#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

typedef struct No{
    string id;
    int time;
    No *next;
}No;

typedef struct Process {
  string id;
  int time;
} Process;

void list_insert(No *head, string id, int time){ 
    No *newNo = new No(), *cur = head;  // creating a new node and making a head's copy
    newNo->id = id;                   // assigning the current id to the new node's id
    newNo->time = time;
    newNo->next = cur->next;            
    head->next = newNo;                 // and, finally, the head's next node is the new node
}

// function that inserts a node at the bottom of the list
void enqueue(No *head, string id, int time){
    No *cur = head;  
    for(;cur->next != NULL;){           // this while runs through the entire queue to the end
        cur = cur->next;                // so the current node is at the end of the queue
    }
                                        // calling the function that inserts a node to the queue
    list_insert(cur, id, time);         // in this case, exceptionally, the sended node is not the actually the list head
                                        // it happens because we want to insert a node at the last position, so we send the last node
}

// function that deletes the first node of the list
void dequeue(No *head){
    No *prox = head->next;              // assigning the head next node to an auxiliary node (prox)
    head->next = prox->next;            // the new head next node is the prox next node
    delete(prox);                       // deleting the prox node and freeing memory
}

void deleteFinished(string *toFinish, Process processors[], int p, int *f){
    bool test = false;
    for(int i = *f; i >= 0; i--){          
        for(int j = 0; j < p; j++){
          if(toFinish[i] == processors[j].id){
            cout << processors[j].id << " " << processors[j].time << endl;
            processors[j].id = "empty";
            processors[j].time = 0;
            test = true;
          }
        }
        if(test){
          (*f) = (*f) - 1;
          toFinish = (string *) realloc(toFinish, ((*f)+2)*sizeof(string));
        }
    }
}

void interrupt(Process processors[], No *execution, int cicle, int p) {
    int wasInterrupted = 0;

    for(int i = 0; i < p; i++){        
        if(processors[i].id != "empty" && processors[i].time % cicle == 0 && processors[i].time != 0){
            enqueue(execution, processors[i].id, processors[i].time); // adding the process to the executionQueue 
            processors[i].id = "empty";
            processors[i].time = 0;
            wasInterrupted++;
        }    
    }

    cout << wasInterrupted << endl;
}

void add(No *execution, string *waiting, int *w){
    int wasAdded = 0;
    for(int i = *w; i >= 0; i--){
        enqueue(execution, waiting[i], 0);
        wasAdded++;
    }
    (*w) = -1;
    waiting[0] = "empty";   
    waiting = (string *) realloc(waiting, sizeof(string));
    cout << wasAdded << endl;
}

void despatch(Process processors[], No *execution, int p){
    
    int wasDispatched = 0;
    for(int i = 0; i < p; i++){
        string id;
        if(processors[i].id == "empty" && execution->next != NULL){                 // if the processor is free to use, that is id = "empty"
            processors[i].id = (execution->next)->id;
            processors[i].time = (execution->next)->time;
            dequeue(execution);
            wasDispatched++;
        }
    }
    cout << wasDispatched << endl;
}

// this function increments the total execution time of all programs on processors queue
void incrementTime(Process processors[], int p){
    string id;
    for(int i = 0; i < p; i++){
      if(processors[i].id != "empty") processors[i].time++; 
    }
}

// string *aloc(string *str, string id, int size){
//     string *newStr = NULL; 

//     newStr = (string *) realloc(str, (size + 1)*sizeof(string));
//     if(newStr == NULL){
//         exit(-1);
//     }

//     newStr[size] = id;

//     return newStr;
// }

// void sort(string *Finished, string *toFinish, int size){
//     int j = 0;
//     for(int i = size; i >= 0; i--){
//         Finished[j] = toFinish[i];
//         j++;
//     }
// }

void menu(No *execution , string *waiting, string *toFinish){
    int cicle, p, nCicles = 0, w = -1, f = -1;
    bool escape = false;
    string command, id;

    cin >> p >> cicle;

    Process processors[p];

    for(int i = 0; i < p; i++){
      processors[i].id = "empty";
    }

    for(;escape == false;){
        cin >> command; 
        switch (command[0]){
            case 'N':                   // a process will be inserted on the waitingQueue
                cin >> id;            
                w++;
                waiting = (string *) realloc(waiting, (w + 1)*sizeof(string)); 
                waiting[w] = id;
                break;
            case 'T':                   // a process will be inserted on the toFinishQueue
                cin >> id;
                f++;
                toFinish = (string *) realloc(toFinish, (f + 1)*sizeof(string)); 
                toFinish[f] = id;
                break;
            case 'S':
                cout << "ciclo " << nCicles << endl;
                incrementTime(processors, p);
                //[C]
                if(f != -1){
                    deleteFinished(toFinish, processors, p, &f);
                }
                //[I]
                interrupt(processors, execution, cicle, p);
                //[A]
                add(execution, waiting, &w);
                //[D]
                despatch(processors, execution, p);

                nCicles++;
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

    No *execution = new No();
    
    string *waiting = NULL, *toFinish = NULL;
    
    execution->next = NULL;             
    execution->id = "empty";             
    execution->time = 0;            

    menu(execution, waiting, toFinish);

}

// g++ RoundRobin.cpp -o main -Wall
//./main < entrada.in > saida.out