# Venetis_erg
# README (Ελληνική Έκδοση)

## Σύστημα Διαχείρισης Βιβλιοθήκης σε C++

### Περιγραφή

Η παρούσα εργασία υλοποιεί ένα απλό σύστημα διαχείρισης βιβλιοθήκης σε γλώσσα C++, με χρήση δυναμικής μνήμης και συνδεδεμένων λιστών. Στόχος του προγράμματος είναι η αποθήκευση, αναζήτηση και διαχείριση βιβλίων και των αντιτύπων τους, σύμφωνα με τις απαιτήσεις της εκφώνησης του μαθήματος.

Η εφαρμογή βασίζεται στη δομή λίστα από λίστες:

-> LOB (List Of Books): κύρια λίστα βιβλίων
-> LOC (List Of Copies): λίστα αντιτύπων για κάθε βιβλίο

Κάθε βιβλίο περιέχει τα στοιχεία του (τίτλος, συγγραφέας, ISBN) και συνδέεται με τη δική του λίστα αντιτύπων.

---

## Δομή Κλάσεων

### `CopyNode`

Αναπαριστά ένα αντίτυπο βιβλίου.

Πεδία:

* `copyID`
* `status` (`available`, `borrowed`, `damaged`)
* `next`

### `BookNode`

Αναπαριστά ένα βιβλίο.

Πεδία:

* `title`
* `author`
* `ISBN`
* `copiesHead`
* `next`

### `Library`

Αναπαριστά ολόκληρη τη βιβλιοθήκη.

Πεδία:

* `booksHead`

---

## Βασικές Λειτουργίες

Το πρόγραμμα παρέχει menu επιλογών:

1. Φόρτωση βιβλιοθήκης από αρχείο
2. Αποθήκευση βιβλιοθήκης σε αρχείο
3. Εμφάνιση όλων των βιβλίων
4. Αναζήτηση βιβλίου με ISBN
5. Προσθήκη νέου βιβλίου
6. Διαγραφή βιβλίου
7. Προσθήκη αντιτύπου
8. Διαγραφή αντιτύπου
9. Δανεισμός αντιτύπου
10. Επιστροφή αντιτύπου
11. Εμφάνιση διαθέσιμων αντιτύπων
12. Έξοδος

---

## Τεχνικά Χαρακτηριστικά

* Χρήση **δυναμικής δέσμευσης μνήμης (`new/delete`)**
* Χρήση **destructors** για σωστή αποδέσμευση μνήμης
* Ταξινομημένη εισαγωγή βιβλίων βάσει τίτλου
* Ταξινομημένη εισαγωγή αντιτύπων βάσει `copyID`
* Ανάγνωση και εγγραφή δεδομένων από/σε αρχείο `library.txt`
* Έλεγχος εγκυρότητας ενεργειών μέσω κατάλληλων περιορισμών

---

## Διαχείριση Μνήμης

Ιδιαίτερη έμφαση δόθηκε στη σωστή χρήση δυναμικής μνήμης.

* Ο destructor της `Library` διαγράφει όλα τα βιβλία.
* Ο destructor της `BookNode` διαγράφει όλα τα αντίτυπα του βιβλίου.
* Με αυτόν τον τρόπο αποφεύγονται memory leaks.

---

## Σκοπός Εργασίας

Η εργασία στοχεύει στην πρακτική εξάσκηση σε:

* Συνδεδεμένες λίστες
* Δείκτες
* Κλάσεις και αντικειμενοστραφή προγραμματισμό
* Διαχείριση δυναμικής μνήμης
* Ανάγνωση / εγγραφή αρχείων
* Σχεδίαση ολοκληρωμένου προγράμματος σε C++

---

## Στοιχεία Φοιτητών

Έλενα Παλαιοκώστα
Ευστράτιος Βαασιλέλλης

Τμήμα Πληροφορικής
Πανεπιστήμιο Πειραιώς
1ο Έτος – 2ο Εξάμηνο

---

# README (English Version)

## Library Management System in C++

### Description

This project implements a basic Library Management System in C++, using dynamic memory allocation and linked lists. The purpose of the program is to store, search and manage books and their copies according to the assignment specifications.

The application is based on a list of lists structure:

-> LOB (List Of Books): main list of books
-> LOC (List Of Copies): list of copies for each book

Each book stores its information (title, author, ISBN) and points to its own list of copies.

---

## Class Structure

### `CopyNode`

Represents a book copy.

Fields:

* `copyID`
* `status` (`available`, `borrowed`, `damaged`)
* `next`

### `BookNode`

Represents a book.

Fields:

* `title`
* `author`
* `ISBN`
* `copiesHead`
* `next`

### `Library`

Represents the whole library.

Fields:

* `booksHead`

---

## Main Features

The program provides a menu with the following options:

1. Load library from file
2. Save library to file
3. Display all books
4. Search book by ISBN
5. Add new book
6. Delete book
7. Add copy
8. Delete copy
9. Borrow copy
10. Return copy
11. Show available copies
12. Exit

---

## Technical Characteristics

* Use of **dynamic memory allocation (`new/delete`)**
* Use of **destructors** for proper memory cleanup
* Sorted insertion of books by title
* Sorted insertion of copies by `copyID`
* File input/output using `library.txt`
* Validation rules for all actions

---

## Memory Management

Special attention was given to memory handling.

* `Library` destructor deletes all books.
* `BookNode` destructor deletes all copies of each book.
* This prevents memory leaks.

---

## Educational Purpose

This assignment focuses on practical understanding of:

* Linked Lists
* Pointers
* Classes and Object-Oriented Programming
* Dynamic Memory Management
* File Handling
* Complete C++ Program Design

---

## Student Information

Elena Palaiokosta
Efstratios Vasilellis

Department of Informatics
University of Piraeus
1st Year – 2nd Semester
