#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

typedef struct No{
    string id;
    int time;
    No *next;
}No;

int nCicles = 0;

// function that inserts a new node at the bottom of the queue
void enqueue(No *head, string id, int time){ 
    No *newNo = new No(), *cur = head;  // creating a new node and making a head's copy
    while(cur->next != NULL){           // this while runs through the entire queue to the end
        cur = cur->next;                // so the current node is at the end of the queue
    }
    newNo->id = id;                     // assigning the current id to the new node id
    newNo->time = time;
    newNo->next = cur->next;            // now, the new node is lastNode->next
}

// function that deletes the first node of the queue
void dequeue(No *head){
    No *prox = head->next;              // assigning the head next node to an auxiliary node (prox)
    head->next = prox->next;            // the new head next node is the prox next node
    delete(prox);                       // deleting the prox node and freeing memory
}

// function that deletes all nodes of the queue, that is, clean the entire queue
void clear(No *head){
    while(head->next != NULL){          // this while runs through the entire queue to the end
        dequeue(head);                  // deleting the current node
    }
}

void deleteFinished(No *toFinish, No *processors){
    No *cur1 = processors, *cur2 = toFinish;
    while(cur1->next != NULL){          
        cur1 = cur1->next;
        while(cur2->next != NULL){
            cur2 = cur2->next;
            if(cur1->id == cur2->id){
                cur1->id = " ";
                cur1->time = 0;
                cout << cur2->id << " " << cur2->time << endl;
            }
        }
    }
    clear(toFinish);
}

void interrupt(No *processors, No *execution, int cicle) {
    No *cur = processors;
    int wasInterrupted = 0;

    while(cur->next != NULL){          
        cur = cur->next;
        if(cur->time % cicle){
            enqueue(execution, cur->id, cur->time); // adding the process to the executionQueue 
            cur->id = " ";
            cur->time = 0;
            wasInterrupted++;
        }                  
    }

    cout << wasInterrupted << endl;
}

void add(No *execution, No *waiting){
    No *cur = waiting; 
    int wasAdded = 0;

    while(cur->next != NULL){
        cur = cur->next;
        enqueue(execution, cur->id, 0);
        wasAdded++;
    }
    clear(waiting);

    cout << wasAdded << endl;
}

void despatch(No *processors, No *execution){
    No *cur = processors, *prox = execution->next;
    int wasDispatched = 0;

    while(cur->next != NULL){
        cur = cur->next;
        if(cur->id == " "){                 // if the processor is free to use, that is id = " "
            processors->id = prox->id;
            processors->time = prox->time;
            dequeue(execution);
            wasDispatched++;
        }
    }
}

void sch(No *execution, No *waiting, No *toFinish, No *processors, int cicle){
    cout << "ciclo " << nCicles << endl;
    // [C]
    if(nCicles != 0 && toFinish->next != NULL){ 
        deleteFinished(toFinish, processors);
    }
    //[I]
    interrupt(processors, execution, cicle);
    //[A]
    add(execution, waiting);
    //[D]
    despatch(processors, execution);
}

// this function increments the total execution time of all programs on processors queue
void incrementTime(No *processors, int cicle){
    No *cur = processors;
    while(cur->next != NULL){
        cur = cur->next;
        cur->time += cicle;
    }
}

void menu(No *execution, No *waiting, No *toFinish){
    int cicle, p;
    bool escape = false;
    string command, id;

    No *processors = new No();

    cin >> p >> cicle;

    for(int i = 0; i < p; i++){
        enqueue(processors, " ", 0);
    }

    while (escape == false){
        cin >> command; 
        switch (command[0]){
            case 'N':                   // a process will be inserted on the waitingQueue
                cin >> id;
                enqueue(waiting, id, 0);
                break;
            case 'T':                   // a process will be inserted on the toFinishQueue
                cin >> id;
                enqueue(toFinish, id, 0);
                break;
            case 'S':
                if(nCicles != 0) incrementTime(processors, cicle);
                sch(execution, waiting, toFinish, processors, cicle);
                break;
            case 'E':
                escape = true;
                break;
            default:
                break;
        }
        nCicles++;
    }
    
    clear(processors);
    delete(processors);
}

int main() { 
    // creating the queues
    No *execution = new No(), *waiting = new No(), *toFinish = new No();

    execution->id = ' ';                // the head node doesn't really have a value, it just points to the first node
    execution->time = 0;
    execution->next = NULL;             // i assigned a values to the nodes id just to initialize it with default value (will not be used)
    
    waiting->id = ' ';
    waiting->time = 0;
    waiting->next = NULL;
    
    toFinish->id = ' ';
    toFinish->time = 0;
    toFinish->next = NULL;

    menu(execution, waiting, toFinish);

    // freeing memory 
    clear(execution);                   
    clear(waiting);                     
    clear(toFinish);                    

    delete(execution);
    delete(waiting);
    delete(toFinish);

}
