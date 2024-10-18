// 210 | Midterm #1 | Neil Orton
// IDE used: Xcode
#include <iostream>
#include <random>
#include <fstream>
#include <iomanip>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
const int W = 3;
int rand_num();

class DoublyLinkedList {
private:
    struct Node {
        string name;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            name = val;
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(string value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string name) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->name != name)
            temp = temp->next;

        if (!temp) return;

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "Line is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        cout << setw(W) << temp->name << " left the line" << endl;
        delete temp;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
            cout << setw(W) << newNode->name << " added to back of line" << endl;
        }
    }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            cout << setw(W) << newNode->name << " added to front of line" << endl;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "Lne is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        cout << setw(W) << temp->name << " helped at front of line" << endl;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "Line is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        cout << setw(W) << temp->name << " leaves the end of the line" << endl;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "Line is empty." << endl;
            return;
        }
        while (current) {
            cout << current->name << endl;
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "Line is empty." << endl;
            return;
        }
        while (current) {
            cout << current->name << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS << endl;  // dummy statement to avoid compiler warning

    fstream reader;    // file reader to get the names
    string name;    // string name to store the value of
    string fileName = "names.txt";    // name of file stored in string
    DoublyLinkedList list;    // DoublyLinked list object
    
    
    reader.open(fileName);    // file opened
    
    while (!reader) {    // Error message if file fails to open
        cout << "Error opening file." << endl;
    }

    for (int i = 0; i < 5; ++i) {    // for loop to build the first five customers in line
        reader >> name;
        list.push_back(name);
    }
    
    cout << "Starting Line:" << endl;    // Starting line outputted
        list.print();
    
    for (int i = 0; i < 20; ++i) {    // for loop to show 20 time steps
        static int step = 1;    // static int to keep track of
        
        cout << "Time step #" << step << endl;    // Time step number outputed
        int event = rand_num();    // event generated from random number function
        
        cout << "---------" << endl;    // updates message box
        cout << "Updates:" << endl;
        if (event <= 40) {    // if number generated is less or equal to 40, customer at front of line is helped
            list.pop_front();
        }
        if (event <= 60) {    // if number generated is less or equal to 60, customer added to back of line
            reader >> name;
            list.push_back(name);
        }
        if (event <= 20) {    // if number generated is less or equal to 20, customer at back of line leaves
            list.pop_back();
        }
        if (event <= 10) {    // if number generated is less or equal to 10, VIP enters and a customer leaves
            random_device randPos;
            uniform_int_distribution<int>range(1, 10);
            int pos = range(randPos);
            
            list.delete_pos(pos);
            reader >> name;
            cout << setw(W) << "(VIP) ";
            list.push_front(name);
        }
        cout << "---------" << endl;
        cout << "Resulting Line:" << endl;
        list.print();
        step++;
    }
        
    reader.close();
    
        return 0;
    }

int rand_num() {    // Function to generate random number
    random_device randNum;
    uniform_int_distribution<int>range(1, 100);
    int num = range(randNum);
    
    return num;
}

// Event A: 40%, front helped (pop front)
// Event B: 60%, joins end of line (append node)
// Event C: 20%, end of line leaves (pop back)
// Event D: 10% customer leaves (delete pos)
// Event E: 10% VIP enters and oges to front (add front)

