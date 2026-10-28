/*
 * CS-250 Data Structure and Algorithms
 * Lab 3 - Task 2: Handling Dangling Pointers in Strings with OOP Recap
 * Task: StringPool class - detect and fix a memory leak
 *
 * Name : Mohammad Haroon Ahmadzai
 * CMS ID: 578328
 * Class : BSDS 3A
 */
#include <iostream>
#include <string>
using namespace std;

class StringPool
{
private:
    string *stringPool;   // dynamic array of strings
    int currentSize;      // current number of strings in the pool
    int maxSize;          // maximum size of the pool (set to 5)

public:
    // Constructor - initializes the pool fields
    StringPool()
    {
        maxSize = 5;
        currentSize = 0;
        stringPool = new string[maxSize];
        cout << "[Constructor] StringPool created with capacity " << maxSize << ".\n";
    }

    // Adds a string to the pool if space is available
    void addString(const string &value)
    {
        if (currentSize >= maxSize)
        {
            cout << "[addString] Pool is full, cannot add \"" << value << "\".\n";
            return;
        }
        stringPool[currentSize] = value;
        currentSize++;
        cout << "[addString] Added \"" << value << "\" -> pool size = " << currentSize << "\n";
    }

    // BUGGY VERSION (kept here on purpose to show the leak):
    // This version removes a string from the logical pool but never frees
    // any dynamically allocated memory associated with it, and it simply
    // shifts the size counter down without deleting anything -> this is
    // where a leak would occur if the strings were allocated on the heap
    // individually (e.g. with new string(value)) instead of value objects.
    void removeStringLeaky(int index)
    {
        if (index < 0 || index >= currentSize)
        {
            cout << "[removeStringLeaky] Invalid index.\n";
            return;
        }
        cout << "[removeStringLeaky] Removing \"" << stringPool[index]
             << "\" WITHOUT freeing its memory (leak!).\n";

        // Shift remaining elements left, but the memory of the removed
        // element (if it were heap-allocated separately) is never released.
        for (int i = index; i < currentSize - 1; i++)
        {
            stringPool[i] = stringPool[i + 1];
        }
        currentSize--;
        // NOTE: no delete/free here - this is the intentional bug.
    }

    // FIXED VERSION: properly clears the slot before shifting, and if the
    // pool were storing raw pointers (string*) this is where "delete" would
    // be called to release the heap memory before it becomes unreachable.
    void removeString(int index)
    {
        if (index < 0 || index >= currentSize)
        {
            cout << "[removeString] Invalid index.\n";
            return;
        }
        cout << "[removeString] Removing \"" << stringPool[index]
             << "\" and freeing its slot properly.\n";

        // Explicitly clear the slot's contents (releases the string's
        // internal heap buffer held by std::string) before shifting.
        stringPool[index].clear();

        for (int i = index; i < currentSize - 1; i++)
        {
            stringPool[i] = stringPool[i + 1];
        }
        stringPool[currentSize - 1].clear();   // clear the now-duplicate last slot
        currentSize--;
    }

    // Displays the current status of the pool
    void displayPool() const
    {
        cout << "\n---------- Pool Status ----------\n";
        cout << "Current Size : " << currentSize << " / " << maxSize << "\n";
        for (int i = 0; i < currentSize; i++)
        {
            cout << "  [" << i << "] " << stringPool[i] << "\n";
        }
        cout << "----------------------------------\n";
    }

    // Destructor - releases the dynamically allocated array itself,
    // so the program does not leak the array on exit.
    ~StringPool()
    {
        delete[] stringPool;
        cout << "[Destructor] StringPool memory released.\n";
    }
};

int main()
{
    cout << "=====================================================\n";
    cout << " Lab 3 - Task 2 : StringPool Memory Leak Demo\n";
    cout << " Submitted by : Mohammad Haroon Ahmadzai (578328)\n";
    cout << "=====================================================\n\n";

    StringPool pool;
    string entry;

    // Add multiple strings to the pool (taken from the user)
    cout << "Pool capacity is 5. Enter up to 5 strings to add to the pool.\n";
    cout << "(Type 'stop' at any time to stop adding early.)\n\n";

    for (int i = 0; i < 5; i++)
    {
        cout << "Enter string #" << (i + 1) << ": ";
        getline(cin, entry);
        if (entry == "stop")
        {
            break;
        }
        pool.addString(entry);
    }
    pool.displayPool();

    // Remove a string WITHOUT freeing memory (buggy behaviour shown)
    int leakyIndex;
    cout << "\n--- Demonstrating the LEAKY remove (before the fix) ---\n";
    cout << "Enter the index of the string to remove (leaky): ";
    cin >> leakyIndex;
    pool.removeStringLeaky(leakyIndex);
    pool.displayPool();

    // Detect and fix the leak using the corrected removeString()
    int fixedIndex;
    cout << "\n--- Demonstrating the FIXED remove (after the fix) ---\n";
    cout << "Enter the index of the string to remove (fixed): ";
    cin >> fixedIndex;
    pool.removeString(fixedIndex);
    pool.displayPool();

    cout << "\nProgram ended, destructor will now run automatically.\n";
    return 0;
}
