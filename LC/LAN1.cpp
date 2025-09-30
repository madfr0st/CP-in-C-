#include <iostream>
#include <string>
#include <stack>
using namespace std;

string funcPatternExpander(string inputStr) {
    stack<string> strStack;
    string current = "";
    int n = inputStr.size();

    for (int i = 0; i < n; i++) {
        char ch = inputStr[i];

        if (ch == '(') {
            // push current string into stack
            strStack.push(current);
            current = "";
        }
        else if (ch == ')') {
            // finished pattern, check if {number} follows
            string pattern = current;
            current = strStack.top();
            strStack.pop();

            int repeat = 1;  // default
            if (i + 1 < n && inputStr[i+1] == '{') {
                i += 2; // skip "{"
                repeat = 0;
                while (i < n && inputStr[i] != '}') {
                    repeat = repeat * 10 + (inputStr[i] - '0');
                    i++;
                }
            }

            // expand
            for (int j = 0; j < repeat; j++) {
                current += pattern;
            }
        }
        else {
            current.push_back(ch);
        }
    }
    return current;
}

int main() {
    string inputStr;
    getline(cin, inputStr);

    string result = funcPatternExpander(inputStr);
    cout << result;
    return 0;
}