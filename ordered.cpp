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
    //Ορισμος και δομιση της remnoveCopy
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
        while (current!=nullptr && current->ISBN!=given_isbn) {
            prev = current;
            current=current->next;
        };
        while (current==nullptr) {
            CopyNode* tempCopy = current->copiesHead;

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
        BookNode* current = booksHead;
        cout << "Τίτλος | Συγγραφέας | ISBN | Διαθέσιμα Αντίτυπα | Συνολικά Αντίτυπα " << endl;
        cout << "---------------------------------------------------" << endl;  
        while (current!=nullptr) {
            cout <<current->title<<" | "<<current->author<<" | "<<current->ISBN<<" | "<<current->countAvailable()<<" | "<<current->countCopies()<<endl;
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
        switch (menu_choice){
            case  1:                
            string ans;
                if (bookLibrary.booksHead != nullptr) {
                    cout<<"Υπάρχει ήδη μία βιλιοθήκη φορτωμένη, θέλετε να φορτώσετε μία καινούρια; (Τα αρχεία της παλαιάς βιβλιοθήκης θα χαθούν.[ΝΑΙ]/[ΟΧΙ])\n";
                    getline(cin,ans);
                };
                if (ans=="ΝΑΙ"){ 

                };
        };
    };
    return 0;
};
