/*
 * CS-250 Data Structure and Algorithms
 * Lab 3 - Task 1: Strings in C++
 * Task: Palindrome check using an iterative method
 *
 * Name : Mohammad Haroon Ahmadzai
 * CMS ID: 578328
 * Class : BSDS 3A
 */
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Removes everything that is not a letter/digit and converts
// the remaining characters to lower case so that spaces,
// punctuation and case do not affect the palindrome check.
string cleanString(const string &input)
{
    string cleaned = "";
    for (int i = 0; i < (int)input.length(); i++)
    {
        if (isalnum(input[i]))
        {
            cleaned += tolower(input[i]);
        }
    }
    return cleaned;
}

// Iterative palindrome check using the classic two-pointer approach:
// one pointer starts at the front, the other at the back, and they
// move towards each other comparing characters at every step.
bool isPalindromeIterative(const string &input)
{
    string s = cleanString(input);
    int left = 0;
    int right = (int)s.length() - 1;

    while (left < right)
    {
        if (s[left] != s[right])
        {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

int main()
{
    string userInput;
    char choice;

    cout << "=================================================\n";
    cout << " Lab 3 - Task 1 : Palindrome Checker (Iterative)\n";
    cout << " Submitted by : Mohammad Haroon Ahmadzai (578328)\n";
    cout << "=================================================\n";

    do
    {
        cout << "\nEnter a string to check: ";
        getline(cin, userInput);

        if (isPalindromeIterative(userInput))
        {
            cout << "\"" << userInput << "\" IS a palindrome.\n";
        }
        else
        {
            cout << "\"" << userInput << "\" is NOT a palindrome.\n";
        }

        cout << "\nDo you want to check another string? (y/n): ";
        cin >> choice;
        cin.ignore();   // clear the leftover newline from the buffer
    } while (choice == 'y' || choice == 'Y');

    cout << "\nProgram ended. Thank you!\n";
    return 0;
}
