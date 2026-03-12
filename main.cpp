#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int findAlphabetIndex(char letter, const char alphabet[], int size);
string encryptedBasic(string text, string key, const char alphabet[], int size);
string decryptedBasic(string text, string key, const char alphabet[], int size);

string encryptExtended(string text, string key);
string decryptExtended(string text, string key);

int main() {

    char alphabet[26] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
        'W', 'X', 'Y', 'Z'
    };

    int choice;
    string text;
    string key;

    while (true) {
        cout << "1 - Pagrindinis rezimas." << endl;
        cout << "2 - Isplestinis rezimas." << endl;
        cout << "0 - Pabaigti programa." << endl;
        cout << "Pasirinkite 0, 1 arba 2: ";
        cin >> choice;

        cin.ignore();

        if (choice == 0) {
            cout << "Programa baigta." << endl;
            return 0;
        }

        if (choice == 1) {
            cout << "Iveskite teksta: " << endl;
            getline(cin, text);

            cout << "Iveskite rakta: " << endl;
            getline(cin, key);

            if (key.empty()) {
                cout << "Raktas negali buti tuscias." << endl;
                continue;
            }

            string encrypted = encryptedBasic(text, key, alphabet, 26);
            cout << "Uzsifruotas tekstas: " << encrypted << endl;

            string decrypted = decryptedBasic(encrypted, key, alphabet, 26);
            cout << "Desifruotas tekstas: " << decrypted << endl;
        } else if (choice == 2) {
            cout << "Iveskite teksta: " << endl;
            getline(cin, text);

            cout << "Iveskite rakta: " << endl;
            getline(cin, key);

            if (key.empty()) {
                cout << "Raktas negali buti tuscias." << endl;
                continue;
            }

            string encrypted = encryptExtended(text, key);
            cout << "Uzsifruotas tekstas: " << encrypted << endl;

            string decrypted = decryptExtended(encrypted, key);
            cout << "Desifruotas tekstas: " << decrypted << endl;
        } else {
            cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
        }

        cout << endl;
    }
}

int findAlphabetIndex(char letter, const char alphabet[], int size) {
    char upperLetter = toupper((unsigned char)letter);

    for (int i = 0; i < size; i++) {
        if (alphabet[i] == upperLetter) {
            return i;
        }
    }

    return -1;
}

// Pagrindinis rezimas

string encryptedBasic(string text, string key, const char alphabet[], int size) {
    string result = text;
    int keyIndex = 0;

    for (int i = 0; i < (int)text.length(); i++) {
        char letter = text[i];

        if (isalpha((unsigned char)letter)) {
            char keyLetter = key[keyIndex % key.length()];
            int textIndex = findAlphabetIndex(letter, alphabet, size);
            int keyShift = findAlphabetIndex(keyLetter, alphabet, size);

            if (textIndex == -1 || keyShift == -1) {
                result[i] = letter;
            } else {
                char encryptedLetter = alphabet[(textIndex + keyShift) % size];

                if (islower((unsigned char)letter)) {
                    encryptedLetter = tolower((unsigned char)encryptedLetter);
                }

                result[i] = encryptedLetter;
                keyIndex++;
            }
        } else {
            result[i] = letter;
        }
    }
    return result;
}

string decryptedBasic(string text, string key, const char alphabet[], int size) {
    string result = text;
    int keyIndex = 0;

    for (int i = 0; i < (int)text.length(); i++) {
        char letter = text[i];

        if (isalpha((unsigned char)letter)) {
            char keyLetter = key[keyIndex % key.length()];
            int textIndex = findAlphabetIndex(letter, alphabet, size);
            int keyShift = findAlphabetIndex(keyLetter, alphabet, size);

            if (textIndex == -1 || keyShift == -1) {
                result[i] = letter;
            } else {
                char decryptedLetter = alphabet[(textIndex - keyShift + size) % size];

                if (islower((unsigned char)letter)) {
                    decryptedLetter = tolower((unsigned char)decryptedLetter);
                }

                result[i] = decryptedLetter;
                keyIndex++;
            }
        } else {
            result[i] = letter;
        }
    }
    return result;
}

// Isplestinis rezimas

string encryptExtended(string text, string key) {
    string result = text;

    const int ASCII_START = 32;
    const int ASCII_END = 126;
    const int RANGE = ASCII_END - ASCII_START + 1;

    for (int i = 0; i < (int) text.length(); i++) {
        unsigned char ch = (unsigned char)text[i];
        unsigned char k = (unsigned char)key[i % key.length()];

        if (ch < ASCII_START || ch > ASCII_END) {
            result[i] = text[i];
            continue;
        }

        int idx = ch - ASCII_START;
        int shift = k - ASCII_START;

        result[i] = (char)(ASCII_START + ((idx + shift) % RANGE));
    }
    return result;
}

string decryptExtended(string text, string key) {
    string result = text;

    const int ASCII_START = 32;
    const int ASCII_END = 126;
    const int RANGE = ASCII_END - ASCII_START + 1;

    for (int i = 0; i < (int) text.length(); i++) {
        unsigned char ch = (unsigned char)text[i];
        unsigned char k = (unsigned char)key[i % key.length()];

        if (ch < ASCII_START || ch > ASCII_END) {
            result[i] = text[i];
            continue;
        }

        int idx = ch - ASCII_START;
        int shift = k - ASCII_START;

        result[i] = (char)(ASCII_START + ((idx - shift + RANGE) % RANGE));
    }
    return result;
}
