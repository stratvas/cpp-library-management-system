#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class CopyNode{
public:

int copyID;
string status;
CopyNode* next;

CopyNode( int c, string st){
    copyID= c;
    status= st;
    next = nullptr;
}

};

class BookNode{
public:
    string ISBN;
    string title;
    string author;
 
CopyNode* copiesHead;
BookNode* next;

BookNode(string i, string t, string a){
    ISBN = i;
    title = t;
    author = a;
    copiesHead = nullptr;
    next = nullptr; 
}

~BookNode(){
CopyNode* current = copiesHead;
while (current != nullptr){
    CopyNode* nextNode = current->next; //πηγαινε στο επομενο
    delete current; // διεγραψε το
    current = nextNode;
}
}
//Ορισμος και δομιση της addCopy
void addCopy(int copyID,string status= "available"){

CopyNode* newNode = new CopyNode(copyID, status); //δεσμευση μνημησ για νεο copy

if ((copiesHead == nullptr) || (copyID < copiesHead->copyID)) { //αν η λιστα ειναι αδεια ή το πρωτο id ειναι μεγαλυτερο απο αυτο του newNode
    
    newNode->next = copiesHead; //το new copy παιρνει την πρωτη διευθυνση
    copiesHead = newNode;
} else {
    CopyNode* current = copiesHead;
    while((current->next != nullptr) && (current->next->copyID<copyID)){
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}
};
int countAvailable(){
CopyNode* current = copiesHead;
int count=0;

while(current != nullptr){
if (current->status == "available"){
    count++;
}
current = current->next;
}

return count;
};
};


//Ορισμος και δομιση της parseLine
vector<string> parseLine(const string& line, char delim = '|') {
vector<string> tokens;
stringstream ss(line);
string token;
while (getline(ss, token, delim)) {
tokens.push_back(token);
}
return tokens;
}


class Library {
public:

BookNode* booksHead; //pointer για την αρχη της LOB

Library(){    
    booksHead = nullptr;
}


~Library(){
    BookNode* current = booksHead;
    while(current !=nullptr){
        BookNode* nextBook = current->next; //πιανουμε το επομενο βιβλιο
        delete current; //διαγραφουμε το τωρινο που εχουμε
        current = nextBook; //το τωρινο που εχουμε ειναι πλεον το επομενο που κρατησαμε πριν την διαγραφη του προηγουμενου τωρινου
    }
}


BookNode* addBook(string title, string author, string isbn) {

    BookNode* newNode = new BookNode (isbn, title, author);
    if ((booksHead == nullptr) || (isbn < booksHead->ISBN)) { //αν η λιστα ειναι αδεια ή το πρωτο id ειναι μεγαλυτερο απο αυτο του newNode
    
    newNode->next = booksHead; //το new copy παιρνει την πρωτη διευθυνση
    booksHead = newNode;
} else {
    BookNode* current = booksHead;
    while((current->next != nullptr) && (current->next->ISBN<isbn)){
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}
return newNode;
};

    void saveToFile(const string& filename){
        ofstream file(filename); //ανοιγμα του library.txt
        if (!file.is_open()) { //αν δεν ανοιγει το file δωσε αντιστοιχο μηνυμα
            cout << "Couldn't open file." << endl;
            return;
        }
        BookNode* currentBook = booksHead;
        while (currentBook != nullptr) {
            //εισαγουμε τα στοιχεια του copy μεσα στο file με το format του file
            file << "BOOK|" << currentBook->ISBN << "|" << currentBook->title << "|" << currentBook->author << endl;
         

        CopyNode* currentCopy = currentBook->copiesHead;
        while (currentCopy != nullptr){
        file << "COPY|" << currentCopy->copyID << "|" << currentCopy->status << endl;
        currentCopy = currentCopy->next; //προχωραει στο επομενο αντιτυπο
        };

            //μετα απο ολα τα αντιτυπα προχωραμε στο επομενο βιβλιο
            currentBook = currentBook->next;
        }
        file.close();
    }      


    
    void loadFromFile(const string& filename){

        ifstream file(filename);
        if (!file.is_open()){
        cout<< "the file cant be opened"<<endl;
        return;
        }

        string line;
        BookNode*previousBook = nullptr;

        while(getline(file, line)){
        if (line.empty()){
            continue;
        }
        
        vector<string> tokens = parseLine(line);

        if (tokens[0] == "BOOK"){
        previousBook = addBook(tokens[2], tokens[3], tokens [1]); //title, author, ISBN
        } else if (tokens[0] == "COPY"){
        int id = stoi(tokens[1]);
        string status = tokens[2];
        if (previousBook != nullptr){
            previousBook->addCopy(id, status);
        }

        }
    }
    file.close();
    }
};

int main() {
    Library bookLibrary;

    bookLibrary.loadFromFile("library.txt");

    return 0;
}