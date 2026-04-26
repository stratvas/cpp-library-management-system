#include <iostream>
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
    
    CopyNode* copiesHead;
    BookNode* next;

    BookNode(string i, string t, string a){
        ISBN = i;
        title = t;
        author = a;
        copiesHead = nullptr;
        next = nullptr; 
    };
    ~BookNode(){
        CopyNode* current = copiesHead;
        while (current != nullptr){
            CopyNode* nextNode = current->next; //πηγαινε στο επομενο
            delete current; // διεγραψε το
            current = nextNode;
            };
    };
    //Ορισμος και δομιση της addCopy
    void addCopy(int copyID,string status= "available"){
        CopyNode* newNode = new CopyNode(copyID, status); //δεσμευση μνημησ για νεο copy
        if ((copiesHead == nullptr) || (copyID < copiesHead->copyID)) { //αν η λιστα ειναι αδεια ή το πρωτο id ειναι μεγαλυτερο απο αυτο του newNode
            newNode->next = copiesHead; //το new copy παιρνει την πρωτη διευθυνση
            copiesHead = newNode;
        }
        else {
            CopyNode* current = copiesHead;
            while((current->next != nullptr) && (current->next->copyID<copyID)){
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        };
    };
    //Ορισμος και δομιση της removeCopy
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
    //Ορισμος και δομιση της borrowCopy
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
    bool returnCopy(int copyID,int isDamaged) {
        CopyNode* current = copiesHead;
        while (current!=nullptr) {
            if (copyID==current->copyID) {
                if (current->status!="borrowed") {
                    return false;
                };
                if (isDamaged==1) {
                    current->status="damaged";
                }
                else {
                    current->status ="available";
                };
                return true;
            }
            else {
                current = current->next;
            };
        };
        return false;
    };
    //Ορισμος και δομιση της countAvailable
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
    //Ορισμος και δομιση της countCopies (μετρα τα συνολικα αντιγραφα ενος βιβλιου ανεξαρτητα απο το status)
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
//Ορισμος και δομιση της parseLine
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
        BookNode* booksHead; //pointer για την αρχη της LOB

    Library(){    
        booksHead = nullptr;
    };
    ~Library(){
        BookNode* current = booksHead;
        while(current !=nullptr){
            BookNode* nextBook = current->next; //πιανουμε το επομενο βιβλιο
            delete current; //διαγραφουμε το τωρινο που εχουμε
            current = nextBook; //το τωρινο που εχουμε ειναι πλεον το επομενο που κρατησαμε πριν την διαγραφη του προηγουμενου τωρινου
        };
    };
    BookNode* addBook(string title, string author, string isbn) {
        BookNode* newNode = new BookNode (isbn, title, author);
        if ((booksHead == nullptr) || (title < booksHead->title)) { //αν η λιστα ειναι αδεια ή ο πρώτος τίτλος ειναι μεγαλυτερος απο αυτο του newNode
            newNode->next = booksHead; //το new copy παιρνει την πρωτη διευθυνση
            booksHead = newNode;
        } else {
            BookNode* current = booksHead;
            while((current->next != nullptr) && (current->next->title<title)){
                current = current->next;
            };
            newNode->next = current->next;
            current->next = newNode;
        };
        return newNode;
    };
    void removeBook(string given_isbn) {
        BookNode* current = booksHead;
        BookNode* prev = nullptr;
        while (current != nullptr) {
            if (current->ISBN == given_isbn) {
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
    BookNode* findBook(string given_isbn) {
        BookNode* current = booksHead ;
        while (current !=nullptr) {
            if (current->ISBN==given_isbn) {
                return current;
            } else {
                current=current->next;
            }; 
        };
        return nullptr;
    };
    void printAll() {
        cout << "DEBUG: μπήκα στην printAll()" << endl;
        BookNode* current = booksHead;
        cout << "Τίτλος | Συγγραφέας | ISBN | Διαθέσιμα Αντίτυπα | Συνολικά Αντίτυπα " << endl;
        cout << "====================================================================" << endl;  
        while (current!=nullptr) {
            cout <<current->title<<" | "<<current->author<<" | "<<current->ISBN<<" | "<<current->countAvailable()<<" | "<<current->countCopies()<<endl;
            cout <<"=================================================================================="<<endl;
            current=current->next;
        };
    };
    void saveToFile(const string& filename){
        ofstream file(filename); //ανοιγμα του library.txt
        if (!file.is_open()) { //αν δεν ανοιγει το file δωσε αντιστοιχο μηνυμα
            cout << "Couldn't open file." << endl;
            return;
        };
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
        };
        file.close();
    };     
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

void continuity() { 
    cout<<"Πατήστε οποιδήποτε πλήκτρο για να επιστρέψετε στο menu."<<endl;
    _getch();
};

int main() {
    Library bookLibrary;
    bookLibrary.loadFromFile("library.txt");
    //menu και λειτουργια επιλογων
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
        cin.ignore();
        switch (menu_choice) {
            case 1: {
                if (bookLibrary.booksHead!=nullptr) {
                    string ans="";
                    bool temp=true;
                    while (ans!="YES" && ans!="NO") {
                        if (temp==false) {
                            cout <<"Please type a valid answer."<<endl;
                        };
                        cout<<"Υπάρχει ήδη μία βιβλιοθήκη φορτωμένη, θέλετε να φορτώσετε μία καινούρια; (Τα αρχεία της παλιάς θα διαγραφούν) [YES]/[NO]"<<endl;
                        getline(cin,ans);
                        temp=false;
                    };
                    if (ans=="YES") {
                        bookLibrary = Library();
                        bookLibrary.loadFromFile("library.txt");
                        cout<<"Φόρτωση νέας βιβλιοθήκης επιτυχής."<<endl<<"Επιστροφή στο κεντρικό menu."<<endl;
                    } 
                    else {
                        cout<<"Επιστροφή στο κεντρικό menu."<<endl;
                    };
                };
                break;
            };
            case 2: {
                if (bookLibrary.booksHead!=nullptr) {
                    bookLibrary.saveToFile("library.txt");
                    cout <<"Αποθήκευση βιβλιοθήκης επιτυχής."<<endl;
                    string ans="";
                    bool temp=true;
                    while (ans!="MENU" && ans!="EXIT") {
                        if (temp==false) {
                            cout <<"Please type a valid answer."<<endl;
                        };
                        cout <<"Θέλετε να επιστρέψετε στο κεντρικό menu ή να πραγματοποιηθεί έξοδος; [MENU]/[EXIT]"<<endl;
                        getline(cin,ans);
                        if (ans=="EXIT")  {
                            exit = true;
                        }
                        else if (ans=="MENU") {
                            cout<<"Επιστροφή στο κεντρικό menu."<<endl;
                        };
                        temp=false;
                    };
                };
                break;
            };
            case 3: {
                if (bookLibrary.booksHead!=nullptr)  {
                    bookLibrary.printAll();
                    continuity();
                };
                break;
            };
            case 4: {
                string input_isbn;
                cout <<"Παρακαλώ εισάγετε τον κωδικό του βιβλίου (ISBN) που αναζητάτε."<<endl<<"Ο κωδικός να είναι της μορφής (xxx-xxx-xx-xxxx-x):"<<endl;      
                cin>>input_isbn;
                cin.ignore();
                BookNode* finder = bookLibrary.findBook(input_isbn);
                if (finder!=nullptr) {
                    CopyNode* current_copy = finder->copiesHead;
                    cout <<"Το βιβλίο και τα αντίτυπα σχετικά με τον κωδικό "<<input_isbn<<" ειναι τα εξής:"<<endl;
                    cout<<"=================================================="<<endl;
                    cout<<"ΕΙΔΟΣ"<<" | "<<"ΚΩΔΙΚΟΣ ΒΙΒΛΙΟΥ ISBN"<<" | "<<"ΤΙΤΛΟΣ"<<" | "<<"ΣΥΓΓΡΑΦΕΑΣ"<<endl;
                    cout<<"=================================================="<<endl;
                    cout <<"BOOK"<<" | "<<finder->ISBN<<" | "<<finder->title<<" | "<<finder->author<<endl;
                    cout<<"=================================================="<<endl;
                    cout<<"ΕΙΔΟΣ"<<" | "<<"ΚΩΔΙΚΟΣ ΑΝΤΙΤΥΠΟΥ COPYID"<<" | "<<"ΚΑΤΑΣΤΑΣΗ"<<endl;
                    cout<<"=================================================="<<endl;
                    while (current_copy!=nullptr) {
                        cout<<"COPY"<<" | "<<current_copy->copyID<<" | "<<current_copy->status<<endl;
                        current_copy = current_copy->next;
                    };
                    continuity();
                };
                break;
            };
            case 5: {
                cout<<"Παρακαλώ εισάγετε τον κωδικό του βιβλίου (ISBN) που θέλετε να προσθέσετε: "<<endl;
                string new_isbn;
                cin>>new_isbn;
                cin.ignore();
                BookNode* check_ISBN=bookLibrary.findBook(new_isbn);
                if (check_ISBN==nullptr) {
                    cout<<"Παρακαλώ εισάγετε τον τίτλο του βιβλίου:"<<endl;
                    string new_title;
                    getline(cin,new_title);
                    cout<<"Παρακαλώ εισάγετε τον συγγραφέα του βιβλίου:"<<endl;
                    string new_author;
                    getline(cin,new_author);
                    bookLibrary.addBook(new_title,new_author,new_isbn);
                    cout<<"Το βιβλίο προστέθηκε επιτυχώς."<<endl;
                    continuity();
                }
                else {
                    cout<<"Το βιβλίο με κωδικό: "<<new_isbn<<" υπάρχει ήδη στην βιβλιοθήκη."<<endl;
                    continuity();
                };
                break;
            };
            case 6: {
                cout<<"Παρακαλώ εισάγετε τον κωδικό του βιβλίου (ISBN) που θέλετε να διαγράψετε: "<<endl;
                string delete_isbn;
                cin>>delete_isbn;
                cin.ignore();
                BookNode* check_ISBN=bookLibrary.findBook(delete_isbn);
                if (check_ISBN!=nullptr) {
                    CopyNode* check_borrowed = check_ISBN->copiesHead;
                    bool check_ans=false;
                    while (check_borrowed!=nullptr) {
                        if (check_borrowed->status=="borrowed") {
                            check_ans=true;
                            break;
                        };
                        check_borrowed=check_borrowed->next;
                    };
                    if (check_ans) {
                        cout<<"Υπάρχει αντίτυπο με κατάσταση borrowed, η διαγραφή βιβλίου ακυρώνεται."<<endl;
                        continuity();
                    }
                    else {
                        bookLibrary.removeBook(delete_isbn);
                        cout<<"Το βιβλίο με κωδικό: "<<delete_isbn<<" διαγράφτηκε επιτυχώς μαζί με τα αντίτυπα του."<<endl;
                        continuity();
                    };
                }
                else {
                    cout<<"Το βιβλίο με κωδικό: "<<delete_isbn<<" δεν υπάρχει."<<endl;
                    continuity();
                };
            };
            case 7: {
                cout<<"Παρακαλώ εισάγετε τον κωδικό του βιβλίου (ISBN) στο οποίο θέλετε να προσθέσετε αντίτυπο: "<<endl;
                string new_copy_isbn;
                cin>>new_copy_isbn;
                cin.ignore();
                BookNode* check_ISBN=bookLibrary.findBook(new_copy_isbn);
                if (check_ISBN!=nullptr) {
                    cout<<"Παρακαλώ εισάγετε τον κωδικό αντιτύπου (CopyID):"<<endl;
                    int new_copyid;
                    cin>>new_copyid;
                    cin.ignore();
                    CopyNode* current_copy = check_ISBN->copiesHead;
                    bool ans=false;
                    while (current_copy!=nullptr) {
                        if (new_copyid==current_copy->copyID) {
                            ans=true;
                            break;
                        };
                        current_copy =  current_copy->next;
                    };
                    if (ans) {
                        cout<<"Υπάρχει ήδη αντίτυπο με κωδικό: "<<new_copyid<<endl;
                        continuity();
                    }    
                    else {
                        check_ISBN->addCopy(new_copyid);
                        cout<<"Το αντίτυπο με κωδικό: "<<new_copyid<<" προστέθηκε επιτυχώς."<<endl;
                        continuity();
                    };
                }
                else {
                    cout<<"Το βιβλίο με κωδικό: "<<new_copy_isbn<<" δεν υπάρχει."<<endl;
                    continuity();
                };
            break;
            };
            case 8: {
                cout<<"Παρακαλώ εισάγετε τον κωδικό του βιβλίου (ISBN) στο οποίο θέλετε να διαγράψετε αντίτυπο: "<<endl;
                string remove_copy_isbn;
                cin>>remove_copy_isbn;
                cin.ignore();
                BookNode* check_ISBN=bookLibrary.findBook(remove_copy_isbn);
                if (check_ISBN!=nullptr) {
                    cout<<"Παρακαλώ εισάγετε τον κωδικό αντιτύπου (CopyID) που θέλετε να διαγράψετε."<<endl;
                    int remove_copyid;
                    cin>>remove_copyid;
                    cin.ignore();
                    CopyNode* check_borrowed = check_ISBN->copiesHead;
                    bool exist = false;
                    while (check_borrowed!=nullptr) {
                        if (remove_copyid==check_borrowed->copyID) {
                            if (check_borrowed->status!="borrowed") {
                                check_ISBN->removeCopy(remove_copyid);
                                cout<<"Η διαγραφή αντιτύπου με κωδικό: "<<remove_copyid<<" ολοκληρώθηκε επιτυχώς."<<endl;
                                exist = true;
                                break;
                            }
                            else {
                                cout<<"Το αντίτυπο με κωδικό: "<<remove_copyid<<" έχει κατάσταση borrowed. Η διαγραφή ακυρώνεται."<<endl;
                                exist = true;
                                break;
                            };
                        }
                        else {
                            check_borrowed = check_borrowed->next;
                        };
                    };
                    if (exist==false) {
                        cout <<"Το αντίτυπο με κωδικό: "<<remove_copyid<<" δεν υπάρχει."<<endl;
                    };
                }
                else {
                    cout<<"Το βιβλίο με κωδικό: "<<remove_copy_isbn<<" δεν υπάρχει."<<endl;
                };
                continuity();
                break;
            };
            case 9: {
                cout<<"Παρακαλώ εισάγετε τον κωδικό του βιβλίου (ISBN) του οποίου θέλετε να δανειστείτε αντίτυπο: "<<endl;
                string borrow_copy_isbn;
                cin>> borrow_copy_isbn;
                cin.ignore();
                BookNode* check_ISBN=bookLibrary.findBook(borrow_copy_isbn);
                if (check_ISBN!=nullptr) {
                    cout<<"Παρακαλώ εισάγετε τον κωδικό αντιτύπου (CopyID) που θέλετε να δανειστείτε."<<endl;
                    int borrow_copyid;
                    cin>>borrow_copyid;
                    cin.ignore();
                    bool complete = check_ISBN->borrowCopy(borrow_copyid);
                    if (complete) {
                        cout<<"Ο δανεισμός αντιτύπου ολοκληρώθηκε με επιτυχία. Η νέα κατάσταση του αντιτύπου με κωδικό: "<<borrow_copyid<<" ορίστηκε σε borrowed."<<endl;
                        int available_copies = check_ISBN->countAvailable();
                        cout <<"Ο ενημερωμένος αριθμός διαθέσιμων αντιτύπων είναι: "<<available_copies<<endl;
                    }
                    else {
                        cout<<"Ο δανεισμός αντιτύπου απέτυχε, το αντίτυπο με κωδικό: "<<borrow_copyid<<" δεν έχει κατάσταση available ή δεν υπάρχει."<<endl;
                    };
                }
                else {
                    cout<<"Το βιβλίο με κωδικό: "<<borrow_copy_isbn<<" δεν υπάρχει."<<endl;
                };
                continuity();
                break;
            };
            case 10: {

            };
        };
    };
    return 0;
}