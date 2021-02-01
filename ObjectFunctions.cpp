// OBJECT FUNCTIONS

#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

class Student {
    public:                             
        string name;
        string major;
        double gpa;

        Student(string aName, string aMajor, double aGpa){ 
            name = aName;
            major = aMajor;
            gpa = aGpa;

            cout << "A Student was added:" << endl;
            cout << name << " - " << major << " - " << gpa << endl;
        }

        bool hasHonors() {
            if(gpa >= 3.5) {
                return true;
            }
            return false;
        }
};

/*

------> OBJECT FUNCTIONS

1. we can create functions within the class that will use an onject's atributes to provide information
2. in this case, we'll build a function that will tell us wether an student is on the honor roll or not
3. if you have a gpa of 3.5 or greater that means you're on the honor roll

*/

int main() {

    Student student1("Jim", "Business", 2.4);
    Student student2("Pam", "Art", 3.6);

    cout << "The student1 is in the honor roll?" << " ";
    
    if(student1.hasHonors() == true){
        cout << "Yes." << endl;
    }else {
        cout << "No." << endl;
    }

}
