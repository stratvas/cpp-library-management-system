#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <conio.h>
using namespace std;

class CopyNode{
    public:
        int copyID; 
        string status; 
        CopyNode* next; 
    //copyNode constructor
    CopyNode( int c, string st){
        copyID= c;
        status= st;
        next = nullptr; 
    };
};
class BookNode{
    public:
        string ISBN; 
        string title; 
        string author; 
    //δημμιουργία constructor (BookNode) και pointers στην κεφαλή της LOC και στο αμέσως επόμεννο της κεφαλής
    CopyNode* copiesHead;
    BookNode* next;

    BookNode(string i, string t, string a){
        ISBN = i; 
        title = t;
        author = a;
        copiesHead = nullptr;
        next = nullptr; 
    };
    //destructor BookNode
    ~BookNode(){ 
        CopyNode* current = copiesHead; //διαγραφή κάθε αντιτύπου
        while (current != nullptr){
            CopyNode* nextNode = current->next; 
            delete current; 
            current = nextNode; 
            };
    };
    //ορισμός και δόμιση της addCopy
    void addCopy(int copyID,string status= "available"){
         CopyNode* newNode = new CopyNode(copyID, status); //δέσμευση μνήμης για νέο copy
        if ((copiesHead == nullptr) || (copyID < copiesHead->copyID)) { //προσθήκη νέου copy και ταξινόμηση αυτού σε περίπτωση που η LOC είναι κενή
            newNode->next = copiesHead; 
            copiesHead = newNode; 
        }
        else {
            CopyNode* current = copiesHead; 
            while((current->next != nullptr) && (current->next->copyID<copyID)){ //προσθήκη νέου copy και ταξινόμηση αυτού σε γεμάτη λίστα
                current = current->next; 
            }
            newNode->next = current->next;  //επανασύνδεση λίστας
            current->next = newNode; 
        };
    };
    //ορισμός και δόμιση της removeCopy
    //διάκριση 3 περιπτώσεων
    //1. κενή LOC: επιστροφή στην ροή της main
    //2. το copyID της κεφαλής της LOC == με το δοσμένο id: δημιουργία temp pointer όπου γίνετε assign το παλίο copiesHead pointer. 
    //Ενημέρωση του copiesHead να δείχνει τον επόμενο κόμβο και διαγραφεί temp.
    //3. copyID να βρίσκεται κάπου στο μέσο της λίστας ή να μην υπάρχει: προσπέλαση LOC, αν βρεθεί διαγραφή και ενημέρωση σειράς κόμβων
    void removeCopy(int id){
        if (copiesHead == nullptr) return; 
        if (copiesHead->copyID == id) { 
            CopyNode* temp = copiesHead; 
            copiesHead = copiesHead->next; 
            delete temp; 
            return;
        };
        CopyNode* last = copiesHead; 
        CopyNode* current = copiesHead->next; 
        while (current != nullptr){ 
            if (current->copyID ==  id) { 
                last->next = current->next; 
                delete current; 
                return;
            };
            last = current;
            current = current->next;
        };
    };
    //ορισμός και δόμιση της borrowCopy
    //προσπέλαση της LOC με δοσμένο copyID και ενημέρωση αν βρεθεί όταν βρεθεί της κατάστασης του σε status="borrowed".
    bool borrowCopy(int copyID) {
        CopyNode* current = copiesHead; 
        while (current != nullptr) { 
            if (current->copyID == copyID && current->status == "available") { 
                current->status = "borrowed"; 
                return true; 
            };
            current = current->next; 
        };
        return false; 
    };
    //ορισμός και δόμιση της returnCopy
    //προσπέλαση των αντιτύπων και εύρεση δοσμένου copyID για την επιστροφή του (πρέπει να έχει status="borrowed") και ενημέρωση status σε damaged ή όχι ανάλογα με την τιμή του isDamaged. 
    //Σε διαφορετική περίπτωση εμφάνιση σφάλματος
    void returnCopy(int copyID,int isDamaged) {
        CopyNode* current = copiesHead;
        while (current!=nullptr) { 
            if (copyID==current->copyID) {
                if (current->status!="borrowed") {
                    if (current->status=="available") {
                        cout<<"The copy with ID: "<<copyID<<" has status available. The return failed."<<endl;
                    }
                    else {
                        cout<<"The copy with ID: "<<copyID<<" has status damaged. The return failed."<<endl;
                    };
                    break;
                }
                else {
                    if (isDamaged==1) {
                        current->status="damaged";
                        cout<<"The copy return was successful. The copy with ID: "<<copyID<<" has status damaged."<<endl;
                    }
                    else {
                        current->status ="available";
                        cout<<"The copy return was successful. The copy with ID: "<<copyID<<" has status available."<<endl;
                    };
                    break;  
                };
            }
            else {
                current = current->next;
            }; 
        };
    };
    //πρόσθετη μέθοδος: ορισμός και δόμιση της findCopy, προσπέλαση της LOC για την εύρεση ενός αντιτύπου
        bool findCopy(int copyID) {
        CopyNode* current = copiesHead;
        while (current!=nullptr) {
            if (current->copyID==copyID) {
                return true;
           };
           current=current->next;
        };
        return false;
    };
    //ορισμός και δόμιση της countAvailable, μετρά τα αντίτυπα ενός βιβλίου με status="avalable"
    int countAvailable(){
        CopyNode* current = copiesHead;
        int count=0;
        while(current != nullptr){
            if (current->status == "available"){
                count++;
            };
            current = current->next;
        };
        return count;
    };
    //πρόσθετη μέθοδος: ορισμός και δόμηση της countCopies, μετρά τα συνολικά αντίγραφα ανεξαρτήτως status
    int countCopies() {
        CopyNode* current = copiesHead;
        int count=0;
        while (current!=nullptr) {
            count++;
            current=current->next;
        };
        return count;
    };
};
//ορισμός και δόμιση της parseLine
vector<string> parseLine(const string& line, char delim = '|') {
    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (getline(ss, token, delim)) {
        tokens.push_back(token);
    };
    return tokens;
};
class Library {
    public:
        BookNode* booksHead; //pointer για την αρχή της LOB

    Library(){    
        booksHead = nullptr;
    };
    //destructor της Library
    ~Library(){
        BookNode* current = booksHead;
        while(current !=nullptr){//προσπέλαση στην LOB και διαγραφή κάθε βιβλίου(λόγω του BookNode* current,delete current διαγράφονται αυτόματα και όλα τα αντίτυπα)
            BookNode* nextBook = current->next; 
            delete current;
            current = nextBook; 
        };
    };
    //ορισμός και δόμηση της addBook
    BookNode* addBook(string title, string author, string isbn) {
        BookNode* newNode = new BookNode (isbn, title, author);
        if ((booksHead == nullptr) || (title < booksHead->title)) { //περίπωτση άδειας λίστα και ταξινόμηση 
            newNode->next = booksHead; //το new copy παίρνει την πρώτη διεύθυνση
            booksHead = newNode;
        } else {
            BookNode* current = booksHead;
            while((current->next != nullptr) && (current->next->title<title)){//περίπτωση γεμάτης λίστας και ταξινόμηση
                current = current->next;
            };
            newNode->next = current->next;
            current->next = newNode;
        };
        return newNode;
    };
    //ορισμός και δόμηση της removeBook
    void removeBook(string given_isbn) {
        BookNode* current = booksHead;
        BookNode* prev = nullptr;
        while (current != nullptr) {//προσπέλαση λίστας LOB για την εύρεση του βιβλίου
            if (current->ISBN == given_isbn) {//διαγραφή του βιβλίου αν αυτό βρεθεί και επανασύνδεση λίστας LOB prev με next
                BookNode* toDelete = current;
                if (prev == nullptr)   {
                    booksHead = current->next;
                }
                else {
                    prev->next = current->next;
                };
                delete toDelete;
                return;
            };
            prev = current;
            current = current->next;
        };
    };
    //ορισμός και δόμηση της findBook
    BookNode* findBook(string given_isbn) {
        BookNode* current = booksHead ;
        while (current !=nullptr) {//προσπέελασητης LOB μέχρι να βρεθεί βιβλίο με ίδιο ISBN με το δοσμένο
            if (current->ISBN==given_isbn) {
                return current;
            } else {
                current=current->next;
            }; 
        };
        return nullptr;
    };
    //ορισμός και δόμηση της priintAll
    void printAll() {
        BookNode* current = booksHead;//εισαγωγή τίτλων για ευκολότερη ανάγνωση
        cout << "Title | Author | ISBN | Available Copies | Total Copies " << endl;
        cout << "====================================================================" << endl;  
        while (current!=nullptr) {//προσπέλαση όλων των βιβλίων της LOB και εκτύπωση αυτών
            cout <<current->title<<" | "<<current->author<<" | "<<current->ISBN<<" | "<<current->countAvailable()<<" | "<<current->countCopies()<<endl;
            cout <<"=================================================================================="<<endl;
            current=current->next;
        };
    };
    //ορισμός και δόμηση της savetofille
    void saveToFile(const string& filename){
        ofstream file(filename); //άνοιγμα αρχείου
        if (!file.is_open()) { //περίπτωση σφάλματος δώσε αντίστοιχο μύνημα
            cout << "Couldn't open file." << endl;
            return;
        };
        BookNode* currentBook = booksHead;
        while (currentBook != nullptr) { // προσπέλαση της LOB  και της LOC και αντιγραφή δεδομένων στο file
            file << "BOOK|" << currentBook->ISBN << "|" << currentBook->title << "|" << currentBook->author << endl;
            CopyNode* currentCopy = currentBook->copiesHead;
            while (currentCopy != nullptr){
                file << "COPY|" << currentCopy->copyID << "|" << currentCopy->status << endl;
                currentCopy = currentCopy->next; 
            };
            currentBook = currentBook->next;
        };
        file.close(); //κλείσιμο φακέλου
    };     
    //χρήση έτοιμης loadfromfile με μερικές προσθήκες
    void loadFromFile(const string& filename){ 
        ifstream file(filename);
        if (!file.is_open()){
            cout<< "The file can't be opened."<<endl;
            return;
        };
        string line;
        BookNode*previousBook = nullptr;
        while(getline(file, line)){
            if (line.empty()){
                continue;
            };
            vector<string> tokens = parseLine(line);
            if (tokens[0] == "BOOK"){
                previousBook = addBook(tokens[2], tokens[3], tokens [1]); //title, author, ISBN
            }
            else if (tokens[0] == "COPY"){
                int id = stoi(tokens[1]);
                string status = tokens[2];
                if (previousBook != nullptr){
                    previousBook->addCopy(id, status);
                }
            }
        }
        file.close();
    };
};
//απλή συνάρτηση για ευκολότερο navigation στο menu και την αποφυγή του repeated code
void continuity() { 
    cout<<"Press any key to return to the menu."<<endl;
    _getch();
};

int main() {
    Library bookLibrary;//δημιουργία βιβλιοθήκης
    bookLibrary.loadFromFile("library.txt");//φόρτωση βιβλιοθήκης στο πρόγραμμα
    //menu και λειτουργίες επιλογών
    bool exit = false; 
    while (exit==false) {
        cout<<"====== LIBRARY - MAIN MENU ======\n";
        cout<<"  1. Load library from file\n";
        cout<<"  2. Save library to file\n";
        cout<<"  3. Display all books\n";
        cout<<"  4. Search book (by ISBN)\n";
        cout<<"  5. Add new book\n";
        cout<<"  6. Delete book\n";
        cout<<"  7. Add copy to book\n";
        cout<<"  8. Remove copy from book\n";
        cout<<"  9. Borrow copy\n";
        cout<<"  10. Return copy\n";
        cout<<"  11. Show available copies of book\n";
        cout<<"  0. Exit\n";
        cout<<"=========================================\n";
        cout<<"Please choose one of the options above:\n";
        int menu_choice;
        cin >> menu_choice;
        while (menu_choice<0 || menu_choice>11) {
            cout <<"Please type a valid answer."<<endl; //validation check
            cin>>menu_choice;
        };
        cin.ignore();
        switch (menu_choice) {
            case 1: {
                if (bookLibrary.booksHead!=nullptr) {
                    cout<<"A library is already loaded. Do you want to load a new one? (Old data will be deleted) [YES]/[NO]"<<endl;//warning για τον χρήστη
                    string ans;
                    getline(cin,ans);
                    while (ans!="YES" && ans!="NO") {//ansswer validation check
                        cout <<"Please type a valid answer."<<endl;
                        getline(cin,ans);
                    }
                    if (ans=="YES") {
                        bookLibrary.~Library();//διαγραφή όλων των δεδομένων της βιβλιοθήκης για δυναμική εκκαθάριση μνήμης συμπεριλαμβανομένου και του αντικειμένου
                        new (&bookLibrary) Library();//δημιουργία νέου αντικειμένου στη διεύθυνση του προηγούμενου (για εκμετάλλευση κοινής μνήμης και την αποφυγή double pointer/floating pointers)
                        bookLibrary.loadFromFile("library.txt");//333-334 απλή φόρτωση νέας βιβλιοθήκης και διευκόλυνση στο navigation
                        cout<<"New library loaded successfully."<<endl<<"Returning to the main menu."<<endl;
                    } 
                    else {
                        cout<<"Returning to the main menu."<<endl;
                    };
                };  
                break;
            };
            case 2: {
                if (bookLibrary.booksHead!=nullptr) {//έλεγχος περίπτωσης άδειας βιβλιοθήκης
                    bookLibrary.saveToFile("library.txt");//359-360 απλή αποθήκευση στο ήδη υπάρχον txt
                    cout <<"Library saved successfully."<<endl;
                    cout <<"Do you want to return to the main menu or exit? [MENU]/[EXIT]"<<endl;//διευκόληνση του navigation
                    string ans;
                    getline(cin,ans);
                    while (ans!="MENU" && ans!="EXIT") {//answer vaidation check
                        cout<<"Please input a valid option."<<endl;
                        getline(cin,ans);
                    };
                    if (ans=="EXIT")  {
                        cout<<"Goodbye!"<<endl;
                        exit = true;
                    }
                    else {
                        cout<<"Returning to the main menu."<<endl;
                    };
                };
                break;
            };
            case 3: {
                if (bookLibrary.booksHead!=nullptr)  { //εκτύπωση όλης της βιβλιοθήκης με την προυπόθεση να υπάρχει έστω ένα βιβλίο φορτωμένο σε αυτή
                    bookLibrary.printAll();
                };
                continuity();
                break;
            };
            case 4: {
                string input_isbn;
                cout <<"Please enter the ISBN of the book you are searching for. The code should have the form (xxx-xxx-xx-xxxx-x):"<<endl;      
                cin>>input_isbn;
                cin.ignore();
                BookNode* finder = bookLibrary.findBook(input_isbn);//έλεγχος ύπαρξης βιβλίου
                if (finder!=nullptr) {
                    CopyNode* current_copy = finder->copiesHead;//προσπέλαση της LOC του βιβλίου με input_isb και εκτύπωση πλήρης λίστας αντιτύπων του βιβλίου
                    cout <<"The book and copies for ISBN "<<input_isbn<<" are as follows:"<<endl;
                    cout<<"--------------------------------------------------"<<endl;
                    cout<<"TYPE | BOOK ISBN | TITLE | AUTHOR"<<endl;
                    cout<<"=================================================="<<endl;
                    cout <<"BOOK | "<<finder->ISBN<<" | "<<finder->title<<" | "<<finder->author<<endl;
                    cout<<"--------------------------------------------------"<<endl;
                    cout<<"TYPE | COPY ID | STATUS"<<endl;
                    cout<<"============================================"<<endl;
                    while (current_copy!=nullptr) {
                        cout<<"COPY"<<" | "<<current_copy->copyID<<" | "<<current_copy->status<<endl;
                        current_copy = current_copy->next;
                    };
                }
                else {
                    cout<<"The book with ISBN: "<<input_isbn<<" was not found."<<endl;
                };
                continuity();
                break;
            };
            case 5: {
                cout<<"Please enter the ISBN of the book you want to add. The code should have the form (xxx-xxx-xx-xxxx-x):"<<endl;
                string new_isbn;
                cin>>new_isbn;
                cin.ignore();
                BookNode* check_ISBN=bookLibrary.findBook(new_isbn); //έλεγχος περίπτωσης ύπαρξης βιβλίου με ίδιο ISBN με την νέα προσθήκη
                if (check_ISBN==nullptr) {
                    cout<<"Please enter the book title:"<<endl;//εισαγωγή νέων στοιχείων βιβλίου
                    string new_title;
                    getline(cin,new_title);
                    cout<<"Please enter the book author:"<<endl;
                    string new_author;
                    getline(cin,new_author);
                    bookLibrary.addBook(new_title,new_author,new_isbn);
                    cout<<"The book was added successfully."<<endl;
                }
                else {
                    cout<<"The book with ISBN: "<<new_isbn<<" already exists in the library. Adding the book is cancelled."<<endl;
                };
                continuity();
                break;
            };
            case 6: {
                cout<<"Please enter the ISBN of the book you want to delete. The code should have the form (xxx-xxx-xx-xxxx-x):  "<<endl;
                string delete_isbn;
                cin>>delete_isbn;
                cin.ignore();
                BookNode* check_ISBN=bookLibrary.findBook(delete_isbn);//έλεγχος ύπαρξης βιβλίου
                if (check_ISBN!=nullptr) {
                    CopyNode* check_borrowed = check_ISBN->copiesHead;
                    bool check_ans=false;
                    while (check_borrowed!=nullptr) { //έλεγχος για αντίτυπα του βιβλίου με κατάσταση borrowed
                        if (check_borrowed->status=="borrowed") {
                            check_ans=true;
                            break;
                        };
                        check_borrowed=check_borrowed->next;
                    };
                    if (check_ans) {
                        cout<<"There is a copy with status borrowed; deleting the book is cancelled."<<endl;
                    }
                    else {
                        bookLibrary.removeBook(delete_isbn); //διαγραφή βιβλίου
                        cout<<"The book with ISBN: "<<delete_isbn<<" was deleted successfully along with its copies."<<endl;
                    };
                }
                else {
                    cout<<"The book with ISBN: "<<delete_isbn<<" does not exist. Deleting the book is cancelled."<<endl;
                };
                continuity();
                break;
            };
            case 7: {
                cout<<"Please enter the ISBN of the book to which you want to add a copy. The code should have the form (xxx-xxx-xx-xxxx-x): "<<endl;
                string new_copy_isbn;
                cin>>new_copy_isbn;
                cin.ignore();
                BookNode* check_ISBN=bookLibrary.findBook(new_copy_isbn);//έλεγχος ύπαρξης βιβλίου
                if (check_ISBN!=nullptr) {
                    cout<<"Please enter the copy ID. The code should have the form (x): "<<endl;
                    int new_copyid;
                    cin>>new_copyid;
                    cin.ignore();
                    CopyNode* current_copy = check_ISBN->copiesHead;
                    bool ans = check_ISBN->findCopy(new_copyid); //εύρεση αντιτύπου
                    if (ans) {
                        cout<<"There is already a copy with ID: "<<new_copyid<<". Adding the copy is cancelled."<<endl;
                    }    
                    else {
                        check_ISBN->addCopy(new_copyid); //προσθήκη νέου αντιτύπου
                        cout<<"The copy with ID: "<<new_copyid<<" was added successfully."<<endl;
                    };
                }
                else {
                    cout<<"The book with ISBN: "<<new_copy_isbn<<" does not exist. Adding the copy is cancelled."<<endl;
                };
                continuity();
                break;
            };
            case 8: {
                cout<<"Please enter the ISBN of the book from which you want to remove a copy. The code should have the form (xxx-xxx-xx-xxxx-x): "<<endl;
                string remove_copy_isbn;
                cin>>remove_copy_isbn;
                cin.ignore();
                BookNode* check_ISBN=bookLibrary.findBook(remove_copy_isbn); //έλεγχος ύπαρξης βιβλίου
                if (check_ISBN!=nullptr) {
                    cout<<"Please enter the copy ID you want to remove. The code should have the form (x): "<<endl;
                    int remove_copyid;
                    cin>>remove_copyid;
                    cin.ignore();
                    CopyNode* check_borrowed = check_ISBN->copiesHead;
                    bool exist = false;
                    while (check_borrowed!=nullptr) { //έλεγχος ύπαρξης αντιτύπου , στην περίπτωση που βρεθεί ελέγχεται ταυτόχρονα και η κατάσταση του να μην είναι borrowed
                        if (remove_copyid==check_borrowed->copyID) {
                            exist = true;
                            if (check_borrowed->status!="borrowed") { //περίπτωση όχι borrowed διαγραφή αντιτύπου 
                                check_ISBN->removeCopy(remove_copyid);
                                cout<<"The copy with ID: "<<remove_copyid<<" was removed successfully."<<endl;
                                break;
                            }
                            else { //περίπτωση borrowed , ακύρωση διαγραφής
                                cout<<"The copy with ID: "<<remove_copyid<<" has status borrowed. Removing the copy is cancelled."<<endl;
                                break;
                            };
                        }
                        else {
                            check_borrowed = check_borrowed->next;
                        };
                    };
                    if (exist==false) {
                        cout <<"The copy with ID: "<<remove_copyid<<" does not exist. Removing the copy is cancelled."<<endl;
                    };
                }
                else {
                    cout<<"The book with ISBN: "<<remove_copy_isbn<<" does not exist. Removing the copy is cancelled."<<endl;
                };
                continuity();
                break;
            };
            case 9: {
                cout<<"Please enter the ISBN of the book for which you want to borrow a copy. The code should have the form (xxx-xxx-xx-xxxx-x): "<<endl;
                string borrow_copy_isbn;
                cin>> borrow_copy_isbn;
                cin.ignore();
                BookNode* check_ISBN=bookLibrary.findBook(borrow_copy_isbn); //έλεγχος ύπαρξης βιβλίου
                if (check_ISBN!=nullptr) {
                    cout<<"Please enter the copy ID you want to borrow. The code should have the form (x): "<<endl;
                    int borrow_copyid;
                    cin>>borrow_copyid;
                    cin.ignore();
                    bool complete = check_ISBN->borrowCopy(borrow_copyid); //δανεισμός βιβλίου με ενσωματωμένη αναζήτηση αντιτύπου
                    if (complete) {
                        cout<<"Copy borrowing completed successfully. The new status of copy ID: "<<borrow_copyid<<" is borrowed."<<endl;
                        int available_copies = check_ISBN->countAvailable(); //545-546 εύρεση και εκτύπωση διαθέσιμων αντιτύπων με τη βοήθεια της countAvailable
                        cout <<"The updated number of available copies is: "<<available_copies<<endl;
                    }
                    else {
                        cout<<"Copy borrowing failed. The copy with ID: "<<borrow_copyid<<" is not available or does not exist."<<endl;
                    };
                }
                else {
                    cout<<"The book with ISBN: "<<borrow_copy_isbn<<" does not exist. Copy borrowing is cancelled."<<endl;
                };
                continuity();
                break;
            };
            case 10: {
                cout<<"Please enter the ISBN of the book for which you want to return a copy. The code should have the form (xxx-xxx-xx-xxxx-x): "<<endl;
                string return_copy_isbn;
                cin>> return_copy_isbn;
                cin.ignore();
                BookNode* check_isbn = bookLibrary.findBook(return_copy_isbn); //έλεγχος ύπαρξης βιβλίου
                if (check_isbn!=nullptr) {
                    cout<<"Please enter the copy ID of the copy you want to return. The code should have the form (x): "<<endl; 
                    int return_copyid;
                    cin>>return_copyid;
                    cin.ignore();
                    bool check_copyid = check_isbn->findCopy(return_copyid); //έλεγχος ύπαρξης αντιτύπου
                    if (check_copyid) {    
                        cout<<"Please enter the condition of the copy you are returning [1. damaged]/[2. not damaged]"<<endl; //571-578 έλεγχος νέας κατάστασης
                        int is_damaged;
                        cin>>is_damaged;
                        while (is_damaged!=1 && is_damaged!=2) { // validation check
                            cout<<"Please insert a valid option."<<endl;
                            cin>>is_damaged;
                            cin.ignore();
                        };
                        check_isbn->returnCopy(return_copyid,is_damaged);//χρήση της returnCopy για την ενημέρωση της LOC και συγκεκριμένα του copy με return_copyid
                    }
                    else {
                        cout<<"The copy with ID: "<<return_copyid<<" does not exist. The return is cancelled."<<endl;
                    };
                }
                else {
                    cout<<"The book with ISBN: "<<return_copy_isbn<<" does not exist. The return is cancelled."<<endl;
                };
                continuity();
                break;
            };
            case 11: {
                cout<<"Please enter the ISBN of the book for which you want to see available copies. The code should have the form (xxx-xxx-xx-xxxx-x): "<<endl;
                string avail_copies;
                cin>> avail_copies;
                cin.ignore();
                BookNode* check_isbn = bookLibrary.findBook(avail_copies); //έλεγχος ύπαρξης βιβλίου
                if (check_isbn!=nullptr) {
                    CopyNode* current_copy = check_isbn->copiesHead;
                    cout<<"TYPE | COPY ID | STATUS"<<endl;
                    cout<<"============================================"<<endl;
                    while (current_copy!=nullptr) { //597-605 προσπέλαση LOC του βιβλίου με κωδικό avail_copies για εκτύπωση διαθέσιμων του αντιτύπων           
                        if (current_copy->status=="available") {
                            cout<<"COPY | "<<current_copy->copyID<<" | "<<current_copy->status<<endl;
                            cout<<"---------------------------------------------"<<endl;
                        };
                        current_copy=current_copy->next;
                    };
                    cout<<"Total copies with status available: "<<check_isbn->countAvailable()<<endl;
                }
                else {
                    cout<<"The book with ISBN: "<<avail_copies<<" does not exist. Printing available copies failed."<<endl;
                };
                continuity();
                break;
            };
            case 0: {
                string ans;
                cout<<"Do you want to save before exiting? [YES]/[NO]"<<endl;
                getline(cin,ans);
                while (ans!="YES" && ans!="NO") { //input validation
                    cout <<"Please type a valid answer."<<endl;
                    getline(cin,ans);
                };
                if (ans=="YES")  { //αν ans=="yes" πρώτα αποθήκευση και μετά έξοδος αλλιώς απλά έξοδος
                    bookLibrary.saveToFile("library.txt");
                };
                cout<<"Goodbye!"<<endl;
                exit = true;
                break;
            };
        };
    };
    return 0;
}