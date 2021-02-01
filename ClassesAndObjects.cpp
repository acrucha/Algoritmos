// CLASSES, OBJECTS AND CONSTRUCTOR FUNCTIONS

#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

/* 

------> CLASSES AND OBJECTS

1. classes are representations for new data types 
2. objects are the instances of a class
3. you can create a representation of a real-world entity in your program
4. a template/model for an objects that i'm going to create
5. i will build a model and give them attributes that will be the same on all objects of this class

*/

// in this case, it's just a specification of what a book is, i'm actually mapping out the blueprint/layout
class Book {
    public:                             
        string title;
        string author;
        int pages;

        // default attributes
        Book(){
            title = "no title";
            author = "no author";
            pages = 0;
        }

        // whenever i create an object, i must pass these arguments through the parameters
        Book(string aTitle, string aAuthor, int aPages){ 
            title = aTitle;
            author = aAuthor;
            pages = aPages;

            cout << "A book was created." << endl;
            cout << title << " by " << author << " (" << pages << " pages)." << endl;
        }
};

/*

------> CONSTRUCTOR FUNCTIONS

1. constructor functions can initialize attributes for us
2. we can do this by passing these attributes through the parameters 
3. and that reduces the number of times we rewrite the same piece of code
4. it’s always good to have default attributes in case we don’t pass parameters

*/

int main() {

    /* 
    
    CODE WITHOUT THE CONSTRUCTOR FUNCTION

    Book book1, book2;

    book1.title = "Harry Potter and the philosopher's stone";
    book1.author = "JK Rowling";
    book1.pages = 240;

    book2.title = "Harry Potter and the chamber of secrets";
    book2.author = "JK Rowling";
    book2.pages = 300;

    cout << book1.title << endl;
    cout << book2.title << endl;

    */

   // CODE WITH THE CONSTRUCTOR FUNCTION

   Book book1("Harry Potter and the philosopher's stone", "JK Rowling", 240);
   Book book2("Harry Potter and the chamber of secrets", "JK Rowling", 300);

}
