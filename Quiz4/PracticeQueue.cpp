#include <iostream>

using std::cin;
using std::cout;
using std::endl;

/*
  Summary of leak fixes
  1. Added destructor to Queue class
  2. Added delete after calling dequeue() in main()
  3. replaced various instances of NULL with nullptr
  4. removed unnecessary creations of Node pointers throughout
*/

class Node
{
public:
  int key;
  int data; // value
  Node *next;

  Node()
  {
    key = 0;
    data = 0;
    next = nullptr;
  }
  Node(int k, int d)
  {
    key = k;
    data = d;
    next = nullptr;
  }
};

class Queue
{
public:
  Node *front;
  Node *rear;

  Queue()
  {
    front = nullptr;
    rear = nullptr;
  }

  //
  // Memory leak fix here
  // added destructor
  //
  ~Queue() {
    Node *temp = front;
    while (temp != nullptr) {
      Node *next = temp->next;
      delete temp;
      temp = next;
    }
  }

  bool isEmpty()
  {
    return front == nullptr && rear == nullptr;
  }

  bool checkIfNodeExist(int key)
  {
    Node *temp = front;
    while (temp != nullptr)
    {
      if (temp->key == key)
      {
        return true;
      }
      temp = temp->next;
    }
    return false;
  }

  void enqueue(int key, int data)
  {
    if (checkIfNodeExist(key))
    {
      cout << "Node already exist with this Key value."
           << "Enter different Key value" << endl;
      return;
    }

    Node *n = new Node(key, data);
    if (isEmpty())
    {
      front = n;
    }
    else
    {
      rear->next = n;
    }
    rear = n;
    cout << "Node  ENQUEUED successfully" << endl;
  }

  Node *dequeue()
  {
    Node *temp = nullptr;
    if (isEmpty())
    {
      cout << "Queue is Empty" << endl;
      return nullptr;
    }

    temp = front;
    if (front == rear)
    {
      front = nullptr;
      rear = nullptr;
    }
    else
    {
      front = front->next;
    }
    return temp;
  }

  int count()
  {
    int count = 0;
    Node *temp = front;
    while (temp != nullptr)
    {
      count++;
      temp = temp->next;
    }
    return count;
  }

  void display()
  {
    if (isEmpty())
    {
      cout << "Queue is Empty" << endl;
    }
    else
    {
      cout << "All values in the Queue are :" << endl;
      Node *temp = front;
      while (temp != nullptr)
      {
        cout << "(" << temp->key << "," << temp->data << ")"
             << " -> ";
        temp = temp->next;
      }
      cout << endl;
    }
  }
};

int main()
{
  Queue q;
  int option, key, data;

  do
  {
    cout << "What operation do you want to perform?"
         << "Select Option number. Enter 0 to exit." << endl;
    cout << "1. Enqueue()" << endl;
    cout << "2. Dequeue()" << endl;
    cout << "3. isEmpty()" << endl;
    cout << "4. count()" << endl;
    cout << "5. display()" << endl;
    cout << "6. Clear Screen" << endl
         << endl;
    cin >> option;

    Node *new_node = nullptr;

    switch (option)
    {
    case 0:
      break;
    case 1:
      cout << "ENQUEUE Function Called -" << endl;
      cout << "Enter KEY and VALUE of NODE to ENQUEUE "
           << "in the Queue"
           << endl;
      cin >> key;
      cin >> data;
      q.enqueue(key, data);
      break;
    case 2:
      cout << "DEQUEUE Function Called - " << endl;
      new_node = q.dequeue();
      cout << "Dequeued Value is: (" << new_node->key << ","
           << new_node->data << ")";
      cout << endl;
      //
      // Memory leak fix here
      // delete the node after dequeue
      //
      delete new_node;
      break;
    case 3:
      cout << "isEmpty Function Called - " << endl;
      if (q.isEmpty())
        cout << "Queue is Empty" << endl;
      else
        cout << "Queue is NOT Empty" << endl;
      break;
    case 4:
      cout << "Count Function Called - " << endl;
      cout << "No of nodes in the Queue: " << q.count()
           << endl;
      break;
    case 5:
      cout << "Display Function Called - " << endl;
      q.display();
      cout << endl;
      break;

    case 6:
      system("cls");
      break;
    default:
      cout << "Enter Proper Option number " << endl;
    }

  } while (option != 0);

  return 0;
}