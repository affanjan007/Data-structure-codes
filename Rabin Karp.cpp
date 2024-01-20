#include <iostream>
#include <string>
using namespace std;

const int prime = 101; 

void searchRabinKarp(string pattern, string text) {
    int patternLength = pattern.length();
    int textLength = text.length();

    int hashPattern = 0;
    int hashText = 0;

    for (int i = 0; i < patternLength; i++) {
        hashPattern = (hashPattern * 256 + pattern[i]) % prime;
        hashText = (hashText * 256 + text[i]) % prime;
    }

    for (int i = 0; i <= textLength - patternLength; i++) {
        if (hashPattern == hashText) {
        	
            bool match = true;
            for (int j = 0; j < patternLength; j++) {
                if (pattern[j] != text[i + j]) {
                    match = false;
                    break;
                }
            }

            if (match) {
                cout << "Pattern found!" << endl;
            }
        }

        if (i < textLength - patternLength) {
            hashText = (256 * (hashText - text[i] * 256) + text[i + patternLength]) % prime;

            if (hashText < 0) {
                hashText += prime;
            }
        }
    }
}

int main() {
    string text = "ABABCABABABCABABC";
    string pattern = "ABABC";

    cout << "Text: " << text << endl;
    cout << "Pattern: " << pattern << endl;

    searchRabinKarp(pattern, text);

    return 0;
}
