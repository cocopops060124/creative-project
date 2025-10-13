#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

string encryptCaesar(string text, int shift);
string decryptCaesar(string text, int shift);
string reverseText(string text);
void saveToFile(string fileName, string data);
string loadFromFile(string fileName);
void menu();

int main() {
    int choice;
    string text, result;
    int shift;
    bool running = true;

    while (running) {
        menu();
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

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
                cout << "\nEnter file name to load (encrypted.txt or decrypted.txt): ";
                getline(cin, text);
                result = loadFromFile(text);
                cout << "\nFile Contents:\n" << result << endl;

                
                if (result == "Error: File not found.") { // don't ask to encrypt/decrypt if file not found
                    cout << "\nCannot process file since it was not found.\n";
                    break;
                }

                char option; // option to encrypt or decrypt text file
                cout << "\nDo you want to Encrypt or Decrypt this text? (Enter E, D or N for none): ";
                cin >> option;
                option = toupper(option);

                if (option == 'E' || option == 'D') {
                    cout << "Enter shift amount: ";
                    cin >> shift;
                    cin.ignore();
                    string processed;

                    if (option == 'E') {
                        processed = encryptCaesar(result, shift);
                        cout << "\nEncrypted Text:\n" << processed << endl;
                        saveToFile("loaded_encrypted.txt", processed);
                    } else {
                        processed = decryptCaesar(result, shift);
                        cout << "\nDecrypted Text:\n" << processed << endl;
                        saveToFile("loaded_decrypted.txt", processed);
                    }
                } else {
                    cout << "\nNo encryption/decryption chosen.\n";
                }
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
    cout << "\n===== Encryption Tool =====\n";
    cout << "1. Encrypt Message\n";
    cout << "2. Decrypt Message\n";
    cout << "3. Reverse Message\n";
    cout << "4. Load Message from File\n";
    cout << "5. Exit\n";
    cout << "==========================\n";
}

string encryptCaesar(string text, int shift) { // Caesar Cipher it just changes the letter to a the next letter in the alphabet by the shift amount
    string result = "";                        // a shifter by 2 is c
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

string decryptCaesar(string text, int shift) { // changes the letters by input shift amount
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

string reverseText(string text) { // writes it backwards
    string result = "";
    for (int i = text.length() - 1; i >= 0; i--) {
        result += text[i];
    }
    return result;
}

void saveToFile(string fileName, string data) { // saves input in a text file so you can see what you input or send it to a friend so they can decrypt the message
    ofstream file(fileName);                    // you also gotta tell em the shift amount
    if (file.is_open()) {
        file << data;
        file.close();
        cout << "\nSaved to " << fileName << endl;
    } else {
        cout << "\nError saving file.\n";
    }
}

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




