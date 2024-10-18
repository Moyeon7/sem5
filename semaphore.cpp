#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;
class CircularQueue {
public:
    vector<string> buffer; 
    int head;
    int tail;
    int itemCount;
    int capacity;
    CircularQueue(int size) : head(0), tail(0), itemCount(0), capacity(size) {
        buffer.resize(size);
    }
    bool isFull() const {
        return itemCount == capacity;
    }
    bool isEmpty() const {
        return itemCount == 0;
    }
};
int lock = 1, availableSpace, occupiedSpace = 0;  
int inptr=0, outptr=-1;
int choice, bufferSize;
CircularQueue myQueue(0);  
void ProduceItem();
void ConsumeItem();
int wait(int);
int signal(int);
void display();
int wait(int s) {
    return (--s);
}
int signal(int s) {
    return (++s);
}
void ProduceItem() {
    outptr++;
    if(outptr==bufferSize){
        outptr=0;
    }
    string item;
    cout << "\nEnter item to produce: ";
    cin >> item;
    lock = wait(lock);
    availableSpace--; 
    occupiedSpace++; 
    myQueue.buffer[myQueue.tail] = item;
    myQueue.tail = (myQueue.tail + 1) % myQueue.capacity;
    myQueue.itemCount++;
    cout << "Item '" << item << "' produced." << endl;
    lock = signal(lock);
}
void ConsumeItem() {
    inptr++;
    if(inptr==bufferSize){
        inptr=0;
    }
    if (myQueue.isEmpty()) {
        cout << "Queue is empty!" << endl;
        return;
    }
    lock = wait(lock);
    occupiedSpace--; 
    availableSpace++; 
    string item = myQueue.buffer[myQueue.head];
    myQueue.buffer[myQueue.head] = "";  
    myQueue.head = (myQueue.head + 1) % myQueue.capacity;
    myQueue.itemCount--;
    cout << "Item '" << item << "' consumed." << endl;
    lock = signal(lock);
    if (myQueue.isEmpty()) {
        inptr=-1, outptr=-1;
        return;
    }
}
void display() {
    cout << "\nQueue Status\t" << endl;
    for (int i = 0; i < myQueue.capacity; i++) {
        if (!myQueue.buffer[i].empty()) {  
            cout << " | " << setw(10) << myQueue.buffer[i] ;
        } else {
            cout << " | " << setw(10) << "EMPTY"  ;
        }
    }
    cout<<" | "<<endl;
    cout << "In: " << inptr << endl;
    cout << "Out: " << outptr << endl;
}
int main() {
    cout << "Set buffer size: ";
    cin >> bufferSize;
    // Initialize the circular queue
    myQueue = CircularQueue(bufferSize);
    availableSpace = bufferSize;
    while (true) {
        cout << "\n1) Produce Item\n2) Consume Item\n3) View Queue\n4) Quit\n";
        cout << "\nYour choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                if ((lock == 1) && (availableSpace != 0)) {
                    ProduceItem();  
                } else {
                    cout << "Queue full! Please wait...\n";
                }
                break;
            case 2:
                if ((lock == 1) && (occupiedSpace != 0)) {
                    ConsumeItem();  
                } else {
                    cout << "Queue empty!\n";
                }
                break;
            case 3:
                display();  
                break;
            case 4:
                cout << "Exiting...\n";
                exit(0);
            default:
                cout << "Invalid option! Please try again.\n";
        }
    }
    return 0;
}