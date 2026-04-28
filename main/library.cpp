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
                        cout<<"Το αντίτυπο με κωδικό: "<<copyID<<" έχει κατάσταση available. Η επιστροφή απέτυχε."<<endl;
                    }
                    else {
                        cout<<"Το αντίτυπο με κωδικό: "<<copyID<<" έχει κατάσταση damaged. Η επιστροφή απέτυχε."<<endl;
                    };
                    break;
                }
                else {
                    if (isDamaged==1) {
                        current->status="damaged";
                        cout<<"Η επιστροφή του αντιτύπου εκτελέστηκε με επιτυχία. Το αντίτυπο με κωδικό: "<<copyID<<" έχει κατάσταση  damaged."<<endl;
                    }
                    else {
                        current->status ="available";
                        cout<<"Η επιστροφή του αντιτύπου εκτελέστηκε με επιτυχία. Το αντίτυπο με κωδικό: "<<copyID<<" έχει κατάσταση  available."<<endl;
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
        cout << "Τίτλος | Συγγραφέας | ISBN | Διαθέσιμα Αντίτυπα | Συνολικά Αντίτυπα " << endl;
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
            cout<< "the file cant be opened"<<endl;
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
    cout<<"Πατήστε οποιδήποτε πλήκτρο για να επιστρέψετε στο menu."<<endl;
    _getch();
};

int main() {
    Library bookLibrary;//δημιουργία βιβλιοθήκης
    bookLibrary.loadFromFile("library.txt");//φόρτωση βιβλιοθήκης στο πρόγραμμα
    //menu και λειτουργίες επιλογών
    bool exit = false; 
    while (exit==false) {
        cout<<"====== ΒΙΒΛΙΟΘΗΚΗ - ΚΕΝΤΡΙΚΟ MENU ======\n";
        cout<<"  1. Φόρτωση βιβλιοθήκης από αρχείο\n";
        cout<<"  2. Αποθήκευση βιβλιοθήκης σε αρχείο\n";
        cout<<"  3. Εμφάνιση όλων των βιβλίων\n";
        cout<<"  4. Αναζήτηση βιβλίου (με ISBN)\n";
        cout<<"  5. Προσθήκη νέου βιβλίου\n";
        cout<<"  6. Διαγραφή βιβλίου\n";
        cout<<"  7. Προσθήκη αντιτύπου σε βιβλίο\n";
        cout<<"  8. Διαγραφή αντιτύπου από βιβλίο\n";
        cout<<"  9. Δανεισμός αντιτύπου\n";
        cout<<"  10. Επιστροφή αντιτύπου\n";
        cout<<"  11. Εμφάνιση διαθέσιμων αντιτύπων βιβλίου\n";
        cout<<"  0. Έξοδος\n";
        cout<<"=========================================\n";
        cout<<"Παρακαλώ διαλέξετε μία από τις παραπάνω επιλογές: \n";
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
                    cout<<"Υπάρχει ήδη μία βιβλιοθήκη φορτωμένη, θέλετε να φορτώσετε μία καινούρια; (Τα δεδομένα της παλιάς θα διαγραφούν) [YES]/[NO]"<<endl;//warning για τον χρήστη
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
                        cout<<"Φόρτωση νέας βιβλιοθήκης επιτυχής."<<endl<<"Επιστροφή στο κεντρικό menu."<<endl;
                    } 
                    else {
                        cout<<"Επιστροφή στο κεντρικό menu."<<endl;
                    };
                };  
                break;
            };
            case 2: {
                if (bookLibrary.booksHead!=nullptr) {//έλεγχος περίπτωσης άδειας βιβλιοθήκης
                    bookLibrary.saveToFile("library.txt");//359-360 απλή αποθήκευση στο ήδη υπάρχον txt
                    cout <<"Αποθήκευση βιβλιοθήκης επιτυχής."<<endl;
                    cout <<"Θέλετε να επιστρέψετε στο κεντρικό menu ή να πραγματοποιηθεί έξοδος; [MENU]/[EXIT]"<<endl;//διευκόληνση του navigation
                    string ans;
                    getline(cin,ans);
                    while (ans!="MENU" && ans!="EXIT") {//answer vaidation check
                        cout<<"Please input a valid option."<<endl;
                        getline(cin,ans);
                    };
                    if (ans=="EXIT")  {
                        cout<<"Καλή συνέχεια!"<<endl;
                        exit = true;
                    }
                    else {
                        cout<<"Επιστροφή στο κεντρικό menu."<<endl;
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
                cout <<"Παρακαλώ εισάγετε τον κωδικό του βιβλίου (ISBN) που αναζητάτε.Ο κωδικός να είναι της μορφής (xxx-xxx-xx-xxxx-x):"<<endl;      
                cin>>input_isbn;
                cin.ignore();
                BookNode* finder = bookLibrary.findBook(input_isbn);//έλεγχος ύπαρξης βιβλίου
                if (finder!=nullptr) {
                    CopyNode* current_copy = finder->copiesHead;//προσπέλαση της LOC του βιβλίου με input_isb και εκτύπωση πλήρης λίστας αντιτύπων του βιβλίου
                    cout <<"Το βιβλίο και τα αντίτυπα σχετικά με τον κωδικό "<<input_isbn<<" ειναι τα εξής:"<<endl;
                    cout<<"--------------------------------------------------"<<endl;
                    cout<<"ΕΙΔΟΣ | ΚΩΔΙΚΟΣ ΒΙΒΛΙΟΥ ISBN | ΤΙΤΛΟΣ | ΣΥΓΓΡΑΦΕΑΣ"<<endl;
                    cout<<"=================================================="<<endl;
                    cout <<"BOOK | "<<finder->ISBN<<" | "<<finder->title<<" | "<<finder->author<<endl;
                    cout<<"--------------------------------------------------"<<endl;
                    cout<<"ΕΙΔΟΣ | ΚΩΔΙΚΟΣ ΑΝΤΙΤΥΠΟΥ COPYID | ΚΑΤΑΣΤΑΣΗ"<<endl;
                    cout<<"============================================"<<endl;
                    while (current_copy!=nullptr) {
                        cout<<"COPY"<<" | "<<current_copy->copyID<<" | "<<current_copy->status<<endl;
                        current_copy = current_copy->next;
                    };
                }
                else {
                    cout<<"Το βιβλίο με κωδικό: "<<input_isbn<<" δεν βρέθηκε."<<endl;
                };
                continuity();
                break;
            };
            case 5: {
                cout<<"Παρακαλώ εισάγετε τον κωδικό του βιβλίου (ISBN) που θέλετε να προσθέσετε. Ο κωδικός να είναι της μορφής (xxx-xxx-xx-xxxx-x):"<<endl;
                string new_isbn;
                cin>>new_isbn;
                cin.ignore();
                BookNode* check_ISBN=bookLibrary.findBook(new_isbn); //έλεγχος περίπτωσης ύπαρξης βιβλίου με ίδιο ISBN με την νέα προσθήκη
                if (check_ISBN==nullptr) {
                    cout<<"Παρακαλώ εισάγετε τον τίτλο του βιβλίου:"<<endl;//εισαγωγή νέων στοιχείων βιβλίου
                    string new_title;
                    getline(cin,new_title);
                    cout<<"Παρακαλώ εισάγετε τον συγγραφέα του βιβλίου:"<<endl;
                    string new_author;
                    getline(cin,new_author);
                    bookLibrary.addBook(new_title,new_author,new_isbn);
                    cout<<"Το βιβλίο προστέθηκε επιτυχώς."<<endl;
                }
                else {
                    cout<<"Το βιβλίο με κωδικό: "<<new_isbn<<" υπάρχει ήδη στην βιβλιοθήκη. Η προσθήκη βιβλίου ακυρώνεται."<<endl;
                };
                continuity();
                break;
            };
            case 6: {
                cout<<"Παρακαλώ εισάγετε τον κωδικό του βιβλίου (ISBN) που θέλετε να διαγράψετε. Ο κωδικός να είναι της μορφής (xxx-xxx-xx-xxxx-x):  "<<endl;
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
                        cout<<"Υπάρχει αντίτυπο με κατάσταση borrowed, η διαγραφή βιβλίου ακυρώνεται."<<endl;
                    }
                    else {
                        bookLibrary.removeBook(delete_isbn); //διαγραφή βιβλίου
                        cout<<"Το βιβλίο με κωδικό: "<<delete_isbn<<" διαγράφτηκε επιτυχώς μαζί με τα αντίτυπα του."<<endl;
                    };
                }
                else {
                    cout<<"Το βιβλίο με κωδικό: "<<delete_isbn<<" δεν υπάρχει. Η διαγραφή βιβλίου ακυρωνεται."<<endl;
                };
                continuity();
                break;
            };
            case 7: {
                cout<<"Παρακαλώ εισάγετε τον κωδικό του βιβλίου (ISBN) στο οποίο θέλετε να προσθέσετε αντίτυπο. Ο κωδικός να είναι της μορφής (xxx-xxx-xx-xxxx-x): "<<endl;
                string new_copy_isbn;
                cin>>new_copy_isbn;
                cin.ignore();
                BookNode* check_ISBN=bookLibrary.findBook(new_copy_isbn);//έλεγχος ύπαρξης βιβλίου
                if (check_ISBN!=nullptr) {
                    cout<<"Παρακαλώ εισάγετε τον κωδικό αντιτύπου (CopyID). Ο κωδικός να είναι της μορφής (x): "<<endl;
                    int new_copyid;
                    cin>>new_copyid;
                    cin.ignore();
                    CopyNode* current_copy = check_ISBN->copiesHead;
                    bool ans = check_ISBN->findCopy(new_copyid); //εύρεση αντιτύπου
                    if (ans) {
                        cout<<"Υπάρχει ήδη αντίτυπο με κωδικό: "<<new_copyid<<". Η προσθήκη αντιτύπου ακυρώνεται."<<endl;
                    }    
                    else {
                        check_ISBN->addCopy(new_copyid); //προσθήκη νέου αντιτύπου
                        cout<<"Το αντίτυπο με κωδικό: "<<new_copyid<<" προστέθηκε επιτυχώς."<<endl;
                    };
                }
                else {
                    cout<<"Το βιβλίο με κωδικό: "<<new_copy_isbn<<" δεν υπάρχει. Η προσθήκη αντιτύπου ακυρώνεται."<<endl;
                };
                continuity();
                break;
            };
            case 8: {
                cout<<"Παρακαλώ εισάγετε τον κωδικό του βιβλίου (ISBN) στο οποίο θέλετε να διαγράψετε αντίτυπο. Ο κωδικός να είναι της μορφής (xxx-xxx-xx-xxxx-x): "<<endl;
                string remove_copy_isbn;
                cin>>remove_copy_isbn;
                cin.ignore();
                BookNode* check_ISBN=bookLibrary.findBook(remove_copy_isbn); //έλεγχος ύπαρξης βιβλίου
                if (check_ISBN!=nullptr) {
                    cout<<"Παρακαλώ εισάγετε τον κωδικό αντιτύπου (CopyID) που θέλετε να διαγράψετε. Ο κωδικός να είναι της μορφής (x): "<<endl;
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
                                cout<<"Η διαγραφή αντιτύπου με κωδικό: "<<remove_copyid<<" ολοκληρώθηκε επιτυχώς."<<endl;
                                break;
                            }
                            else { //περίπτωση borrowed , ακύρωση διαγραφής
                                cout<<"Το αντίτυπο με κωδικό: "<<remove_copyid<<" έχει κατάσταση borrowed. Η διαγραφή αντιτύπου ακυρώνεται."<<endl;
                                break;
                            };
                        }
                        else {
                            check_borrowed = check_borrowed->next;
                        };
                    };
                    if (exist==false) {
                        cout <<"Το αντίτυπο με κωδικό: "<<remove_copyid<<" δεν υπάρχει. Η διαγραφή αντιτύπου ακυρώνεται."<<endl;
                    };
                }
                else {
                    cout<<"Το βιβλίο με κωδικό: "<<remove_copy_isbn<<" δεν υπάρχει. Η διαγραφή αντιτύπου ακυρώνεται."<<endl;
                };
                continuity();
                break;
            };
            case 9: {
                cout<<"Παρακαλώ εισάγετε τον κωδικό του βιβλίου (ISBN) του οποίου θέλετε να δανειστείτε αντίτυπο. Ο κωδικός να είναι της μορφής (xxx-xxx-xx-xxxx-x): "<<endl;
                string borrow_copy_isbn;
                cin>> borrow_copy_isbn;
                cin.ignore();
                BookNode* check_ISBN=bookLibrary.findBook(borrow_copy_isbn); //έλεγχος ύπαρξης βιβλίου
                if (check_ISBN!=nullptr) {
                    cout<<"Παρακαλώ εισάγετε τον κωδικό αντιτύπου (CopyID) που θέλετε να δανειστείτε. Ο κωδικός να είναι της μορφής (x): "<<endl;
                    int borrow_copyid;
                    cin>>borrow_copyid;
                    cin.ignore();
                    bool complete = check_ISBN->borrowCopy(borrow_copyid); //δανεισμός βιβλίου με ενσωματωμένη αναζήτηση αντιτύπου
                    if (complete) {
                        cout<<"Ο δανεισμός αντιτύπου ολοκληρώθηκε με επιτυχία. Η νέα κατάσταση του αντιτύπου με κωδικό: "<<borrow_copyid<<" ορίστηκε σε borrowed."<<endl;
                        int available_copies = check_ISBN->countAvailable(); //545-546 εύρεση και εκτύπωση διαθέσιμων αντιτύπων με τη βοήθεια της countAvailable
                        cout <<"Ο ενημερωμένος αριθμός διαθέσιμων αντιτύπων είναι: "<<available_copies<<endl;
                    }
                    else {
                        cout<<"Ο δανεισμός αντιτύπου απέτυχε, το αντίτυπο με κωδικό: "<<borrow_copyid<<" δεν έχει κατάσταση available ή δεν υπάρχει."<<endl;
                    };
                }
                else {
                    cout<<"Το βιβλίο με κωδικό: "<<borrow_copy_isbn<<" δεν υπάρχει. Ο δανεισμός αντιτύπου ακυρώνεται."<<endl;
                };
                continuity();
                break;
            };
            case 10: {
                cout<<"Παρακαλώ εισάγετε τον κωδικό του βιβλίου (ISBN) του οποίου θέλετε να επιστρέψετε αντίτυπο. Ο κωδικός να είναι της μορφής (xxx-xxx-xx-xxxx-x): "<<endl;
                string return_copy_isbn;
                cin>> return_copy_isbn;
                cin.ignore();
                BookNode* check_isbn = bookLibrary.findBook(return_copy_isbn); //έλεγχος ύπαρξης βιβλίου
                if (check_isbn!=nullptr) {
                    cout<<"Παρακαλώ εισάγετε τον κωδικό (CopyID) του αντιτύπου που θέλετε να επιστρέψετε. Ο κωδικός να είναι της μορφής (x): "<<endl; 
                    int return_copyid;
                    cin>>return_copyid;
                    cin.ignore();
                    bool check_copyid = check_isbn->findCopy(return_copyid); //έλεγχος ύπαρξης αντιτύπου
                    if (check_copyid) {    
                        cout<<"Παρακαλώ εισάγετε την κατάσταση του αντιτύπου που επιστρέφετε [1. damaged]/[2. not damaged]"<<endl; //571-578 έλεγχος νέας κατάστασης
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
                        cout<<"Το αντίτυπο με κωδικό: "<<return_copyid<<" δεν υπάρχει. Η επιστροφή αντιτύπου ακυρώνεται."<<endl;
                    };
                }
                else {
                    cout<<"Το βιβλίο με κωδικό: "<<return_copy_isbn<<" δεν υπάρχει. Η επιστροφή ακυρώνεται."<<endl;
                };
                continuity();
                break;
            };
            case 11: {
                cout<<"Παρακαλώ εισάγετε τον κωδικό του βιβλίου (ISBN) του οποίου θέλετε να δείτε τα διαθέσιμα αντίτυπα. Ο κωδικός να είναι της μορφής (xxx-xxx-xx-xxxx-x): "<<endl;
                string avail_copies;
                cin>> avail_copies;
                cin.ignore();
                BookNode* check_isbn = bookLibrary.findBook(avail_copies); //έλεγχος ύπαρξης βιβλίου
                if (check_isbn!=nullptr) {
                    CopyNode* current_copy = check_isbn->copiesHead;
                    while (current_copy!=nullptr) { //599-607 προσπέλαση LOC του βιβλίου με κωδικό avail_copies για εκτύπωση διαθέσιμων του αντιτύπων           
                        if (current_copy->status=="available") {
                            cout<<"ΕΙΔΟΣ | ΚΩΔΙΚΟΣ ΑΝΤΙΤΥΠΟΥ COPYID | ΚΑΤΑΣΤΑΣΗ"<<endl;
                            cout<<"============================================"<<endl;
                            cout<<"COPY | "<<current_copy->copyID<<" | "<<current_copy->status<<endl;
                            cout<<"---------------------------------------------"<<endl;
                        };
                        current_copy=current_copy->next;
                    };
                    cout<<"Συνολικά  αντίτυπα με κατάσταση available: "<<check_isbn->countAvailable()<<endl;
                }
                else {
                    cout<<"Το βιβλίο με κωδικό: "<<avail_copies<<"  δεν υπάρχει. Η εκτύπωση διαθέσιμων αντιτύπων απέτυχε."<<endl;
                };
                continuity();
                break;
            };
            case 0: {
                string ans;
                cout<<"Θέλετε να πραγματοποιήσετε αποθήκευση πριν την έξοδο σας; [YES]/[NO]"<<endl;
                getline(cin,ans);
                while (ans!="YES" && ans!="NO") { //input validation
                    cout <<"Please type a valid answer."<<endl;
                    getline(cin,ans);
                };
                if (ans=="YES")  { //αν ans=="yes" πρώτα αποθήκευση και μετά έξοδος αλλιώς απλά έξοδος
                    bookLibrary.saveToFile("library.txt");
                };
                cout<<"Καλή συνέχεια!"<<endl;
                exit = true;
                break;
            };
        };
    };
    return 0;
}