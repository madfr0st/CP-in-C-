#include <iostream>
#include <string>
using namespace std;

void funcEncode(string inputStr) {
    string result = "";

    for (int i = 0; i < inputStr.size(); i++) {
        char ch = inputStr[i];

        // Rule 1: if it's a letter, add to result
        if (isalpha(ch)) {
            result.push_back(ch);
        }
        // Rule 2: if it's a digit
        else if (isdigit(ch)) {
            int d = ch - '0';
            if (d > 1) {
                string temp = result;
                for (int j = 1; j < d; j++) {
                    result += temp;
                }
            }
            // if 0 or 1 → do nothing
        }
        // Rule 3: ignore everything else
    }

    cout << result << endl;
}

int main() {
    string inputStr;
    getline(cin, inputStr);

    funcEncode(inputStr);

    return 0;
}