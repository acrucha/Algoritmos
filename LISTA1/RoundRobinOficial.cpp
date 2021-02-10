#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

typedef struct No{
    string id;
    int time;
    No *next;
}No;

class Queue {
    public:
   
        No* head = NULL;
        No* tail = NULL;

        void Enqueue(string id, int time) {
            No* temp = new No();
            temp->time = time; 
            temp->id = id;
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


void deleteFinished(Queue *toFinish, Queue *processors){
    No *fin = toFinish->head;
    string id;
    bool found = false;
    
    while(fin != NULL){          
        id = fin->id;
        found = false;
        No *pro = processors->head;
        while(pro != NULL && !found){
            string id2 = pro->id;
            if(id == id2){
                cout << id2 << " " << pro->time + 1 << endl;
                pro->id = "empty";
                pro->time = 0;
                found = true;
            }
            if(found) toFinish->Dequeue();
            pro = pro->next;
        }
        fin = fin->next;
    }
}

void interrupt(Queue *processors, Queue *execution, int cicle) {
    No *cur = processors->head;
    int wasInterrupted = 0;

    while(cur != NULL){   
        cur->time++;       
        if(cur->id != "empty" && cur->time % cicle == 0 && cur->time != 0){
            execution->Enqueue(cur->id, cur->time); 
            cur->id = "empty";
            cur->time = 0;
            wasInterrupted++;
        }    
        cur = cur->next;
    }

    cout << wasInterrupted << endl;
}

void add(Queue *execution, Queue *waiting){
    No *cur = waiting->head; 
    int wasAdded = 0;

    while(cur != NULL){
        execution->Enqueue(cur->id, 0);
        wasAdded++;
        waiting->Dequeue();
        cur = cur->next;
    }
    cout << wasAdded << endl;
    
}

void despatch(Queue *processors, Queue *execution, int cicle){
    
    No *cur = processors->head;
    int wasDispatched = 0;
    while(cur != NULL){
        string id;
        id = cur->id;
        if(id == "empty" && execution->head != NULL){                 // if the processor is free to use, that is id = "empty"
            cur->id = (execution->head)->id;
            cur->time = (execution->head)->time;
            execution->Dequeue();
            wasDispatched++;
        }
        cur = cur->next;
    }
    cout << wasDispatched << endl;
}


void menu(){
    int cicle, p, nCicles = 0;
    bool escape = false;
    string command, id;
    
    Queue processors, execution, waiting, toFinish;

    cin >> p >> cicle;

    for(int i = 0; i < p; i++){
        processors.Enqueue("empty", 0);
    }

    while (escape == false){
        cin >> command; 
        switch (command[0]){
            case 'N':                   // a process will be inserted on the waitingQueue
                cin >> id;              
                waiting.Enqueue(id, 0);
                break;
            case 'T':                   // a process will be inserted on the toFinishQueue
                cin >> id;
                toFinish.Enqueue(id, 0); 
                break;
            case 'S':
                cout << "ciclo " << nCicles << endl;
                //[C]
                if(!toFinish.isEmpty()){
                  deleteFinished(&toFinish, &processors);
                }
                //[I]
                interrupt(&processors, &execution, cicle);
                //[A]
                add(&execution, &waiting);
                //[D]
                despatch(&processors, &execution, cicle);

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

    menu();

}
