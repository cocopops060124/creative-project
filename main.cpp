#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

// function prototypes
string encryptCaesar(string text, int shift);
string decryptCaesar(string text, int shift);
string reverseText(string text);
void saveToFile(string fileName, string data);
string loadFromFile(string fileName);
void menu();

// main
int main() {
    int choice;
    string text, result;
    int shift;
    bool running = true;

    while (running) {
        menu();
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // clear input buffer

        switch (choice) {
            case 1:
                cout << "\nEnter text to encrypt: ";
                getline(cin, text);
                cout << "Enter shift amount: ";
                cin >> shift;
                cin.ignore();
                result = encryptCaesar(text, shift);
                cout << "\nEncrypted Text: " << result << endl;
                saveToFile("encrypted.txt", result);
                break;

            case 2:
                cout << "\nEnter text to decrypt: ";
                getline(cin, text);
                cout << "Enter shift amount used: ";
                cin >> shift;
                cin.ignore();
                result = decryptCaesar(text, shift);
                cout << "\nDecrypted Text: " << result << endl;
                saveToFile("decrypted.txt", result);
                break;

            case 3:
                cout << "\nEnter text to reverse: ";
                getline(cin, text);
                result = reverseText(text);
                cout << "\nReversed Text: " << result << endl;
                saveToFile("reversed.txt", result);
                break;

            case 4:
                cout << "\nEnter file name to load (ex: encrypted.txt): ";
                getline(cin, text);
                result = loadFromFile(text);
                cout << "\nFile Contents:\n" << result << endl;
                break;

            case 5:
                cout << "\nExiting program...\n";
                running = false;
                break;

            default:
                cout << "\nInvalid option. Try again.\n";
        }

        cout << "\n-----------------------------\n";
    }

    return 0;
}

// show menu
void menu() {
    cout << "\n===== CipherCrafter =====\n";
    cout << "1. Encrypt Message (Caesar Cipher)\n";
    cout << "2. Decrypt Message (Caesar Cipher)\n";
    cout << "3. Reverse Message\n";
    cout << "4. Load Message from File\n";
    cout << "5. Exit\n";
    cout << "==========================\n";
}

// encrypt using Caesar Cipher
string encryptCaesar(string text, int shift) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += (c - base + shift) % 26 + base;
        } else {
            result += c;
        }
    }
    return result;
}

// decrypt using Caesar Cipher
string decryptCaesar(string text, int shift) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += (c - base - shift + 26) % 26 + base;
        } else {
            result += c;
        }
    }
    return result;
}

// reverse text
string reverseText(string text) {
    string result = "";
    for (int i = text.length() - 1; i >= 0; i--) {
        result += text[i];
    }
    return result;
}

// save to file
void saveToFile(string fileName, string data) {
    ofstream file(fileName);
    if (file.is_open()) {
        file << data;
        file.close();
        cout << "\nSaved to " << fileName << endl;
    } else {
        cout << "\nError saving file.\n";
    }
}

// load from file
string loadFromFile(string fileName) {
    ifstream file(fileName);
    string line, data = "";
    if (file.is_open()) {
        while (getline(file, line)) {
            data += line + "\n";
        }
        file.close();
    } else {
        data = "Error: File not found.";
    }
    return data;
}
