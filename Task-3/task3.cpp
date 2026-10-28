/*
 * CS-250 Data Structure and Algorithms
 * Lab 3 - Task 3: Singly Linked List (menu-driven)
 *
 * Name : Mohammad Haroon Ahmadzai
 * CMS ID: 578328
 * Class : BSDS 3A
 */
#include <iostream>
#include <limits>
using namespace std;

// Reads one integer safely. If the user types something that is not a
// number, cin enters a "fail state" and, without this check, every future
// read would silently fail too - making the menu look like it stops
// accepting input. This clears that fail state and discards the bad
// input so the program can keep asking normally.
bool readInt(int &out)
{
    cin >> out;
    if (cin.fail())
    {
        cin.clear();                                          // reset the fail state
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard the bad line
        return false;
    }
    return true;
}

// A single node of the list: a data field and a pointer to the next node.
struct Node
{
    int data;
    Node *next;
};

Node *head = nullptr;   // head pointer, initialized to NULL as required

// 1. Insert a new node at the head of the list
void insertAtHead(int value)
{
    Node *newNode = new Node;
    newNode->data = value;
    newNode->next = head;
    head = newNode;
    cout << "Inserted " << value << " at the head.\n";
}

// 2. Insert a new node at the 3rd position of the list
void insertAtThird(int value)
{
    Node *newNode = new Node;
    newNode->data = value;

    // Case: list has fewer than 2 nodes -> cannot really reach a "3rd"
    // position, so we insert at the end / report the situation instead.
    if (head == nullptr || head->next == nullptr)
    {
        cout << "List has fewer than 2 nodes. Inserting " << value << " at the end instead.\n";
        newNode->next = nullptr;
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            head->next = newNode;
        }
        return;
    }

    // Traverse to the 2nd node so we can insert right after it (3rd slot)
    Node *temp = head->next;   // temp is now the 2nd node
    newNode->next = temp->next;
    temp->next = newNode;
    cout << "Inserted " << value << " at the 3rd position.\n";
}

// 3. Display the entire list from head to NULL
void displayList()
{
    if (head == nullptr)
    {
        cout << "List is empty.\n";
        return;
    }
    Node *temp = head;
    cout << "List: ";
    while (temp != nullptr)
    {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL\n";
}

// 4. Delete the last node of the list
void deleteLast()
{
    if (head == nullptr)
    {
        cout << "List is empty, nothing to delete.\n";
        return;
    }

    // Special case: only one node in the list
    if (head->next == nullptr)
    {
        cout << "Deleting the only node (" << head->data << ").\n";
        delete head;
        head = nullptr;
        return;
    }

    // Traverse until 'temp' points to the second-last node
    Node *temp = head;
    while (temp->next->next != nullptr)
    {
        temp = temp->next;
    }
    cout << "Deleting last node (" << temp->next->data << ").\n";
    delete temp->next;
    temp->next = nullptr;
}

// 5. Count the number of nodes currently in the list
int countNodes()
{
    int count = 0;
    Node *temp = head;
    while (temp != nullptr)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

// 6. Reverse the linked list iteratively using three pointers
void reverseList()
{
    Node *prev = nullptr;
    Node *current = head;
    Node *nextNode = nullptr;

    while (current != nullptr)
    {
        nextNode = current->next;   // remember the rest of the list
        current->next = prev;       // reverse the current node's pointer
        prev = current;             // move prev and current one step forward
        current = nextNode;
    }
    head = prev;                    // prev is now the new head
    cout << "List reversed successfully.\n";
}

// 7. Search for a value in the list and report its position (0-indexed)
void searchValue(int target)
{
    Node *temp = head;
    int position = 0;
    while (temp != nullptr)
    {
        if (temp->data == target)
        {
            cout << "Value " << target << " found at position " << position << ".\n";
            return;
        }
        temp = temp->next;
        position++;
    }
    cout << "Value " << target << " not found in the list.\n";
}

// Frees every remaining node so the program does not leak memory on exit
void destroyList()
{
    Node *temp = head;
    while (temp != nullptr)
    {
        Node *next = temp->next;
        delete temp;
        temp = next;
    }
    head = nullptr;
}

void printMenu()
{
    cout << "\n===================== MENU =====================\n";
    cout << "1. Insert at head\n";
    cout << "2. Insert at 3rd position\n";
    cout << "3. Display list\n";
    cout << "4. Delete last node\n";
    cout << "5. Count nodes\n";
    cout << "6. Reverse list\n";
    cout << "7. Search for a value\n";
    cout << "8. Exit\n";
    cout << "=================================================\n";
    cout << "Enter your choice: ";
}

int main()
{
    cout << "=====================================================\n";
    cout << " Lab 3 - Task 3 : Singly Linked List (Menu Driven)\n";
    cout << " Submitted by : Mohammad Haroon Ahmadzai (578328)\n";
    cout << "=====================================================\n";

    int choice, value;
    bool running = true;

    while (running)
    {
        printMenu();

        if (!readInt(choice))
        {
            cout << "Invalid input. Please enter a number from the menu (1-8).\n";
            continue;   // ask again instead of getting stuck
        }

        switch (choice)
        {
        case 1:
            cout << "Enter value to insert at head: ";
            if (!readInt(value))
            {
                cout << "Invalid value, please enter a number.\n";
                break;
            }
            insertAtHead(value);
            displayList();
            break;

        case 2:
            cout << "Enter value to insert at 3rd position: ";
            if (!readInt(value))
            {
                cout << "Invalid value, please enter a number.\n";
                break;
            }
            insertAtThird(value);
            displayList();
            break;

        case 3:
            displayList();
            break;

        case 4:
            deleteLast();
            displayList();
            break;

        case 5:
            cout << "Number of nodes: " << countNodes() << "\n";
            break;

        case 6:
            reverseList();
            displayList();
            break;

        case 7:
            cout << "Enter value to search: ";
            if (!readInt(value))
            {
                cout << "Invalid value, please enter a number.\n";
                break;
            }
            searchValue(value);
            break;

        case 8:
            cout << "Exiting program...\n";
            running = false;
            break;

        default:
            cout << "Invalid choice, please try again.\n";
        }
    }

    destroyList();   // clean up all remaining nodes before the program ends
    return 0;
}
