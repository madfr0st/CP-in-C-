#include <bits/stdc++.h>
using namespace std;

vector<string> getUsernameStrength(vector<string> usernames, vector<string> commonWords) {
    unordered_set<string> dict(commonWords.begin(), commonWords.end());
    vector<string> result;

    for (string &u : usernames) {
        bool weak = false;

        // Rule 1: Username exactly in dictionary
        if (dict.count(u)) {
            weak = true;
        }

        // Rule 2: Any substring in dictionary
        if (!weak) {
            for (auto &w : dict) {
                if (u.find(w) != string::npos) {
                    weak = true;
                    break;
                }
            }
        }

        // Rule 3: Only digits
        if (!weak && all_of(u.begin(), u.end(), ::isdigit)) {
            weak = true;
        }

        // Rule 4: All lowercase or all uppercase
        if (!weak) {
            if (all_of(u.begin(), u.end(), ::islower) || all_of(u.begin(), u.end(), ::isupper)) {
                weak = true;
            }
        }

        // Rule 5: Shorter than 6 chars
        if (!weak && u.size() < 6) {
            weak = true;
        }

        result.push_back(weak ? "weak" : "strong");
    }

    return result;
}

bool check() {
    return false;
}

int main() {
   if (check && false) {
       cout << "logic" << endl;
   }
    else {
        cout << "error" << endl;
    }
}

