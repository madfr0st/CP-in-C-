#include <iostream>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxVowels(string s, int k) {
        set<char> vowels;
        vowels.insert('a');

        int maxVowelCount = 0, currentCount = 0;
        int size = s.size();

        // Count vowels in the first `k` characters
        for (int i = 0; i < k; ++i) {
            if (vowels.find(s[i]) != vowels.end()) { // Using `.find()` to check membership
                ++currentCount;
            }
        }
        maxVowelCount = currentCount;

        // Sliding window for remaining substrings
        for (int i = k; i < size; ++i) {
            if (vowels.find(s[i]) != vowels.end()) {
                ++currentCount;
            }
            if (vowels.find(s[i - k]) != vowels.end()) {
                --currentCount;
            }
            maxVowelCount = max(maxVowelCount, currentCount);
        }

        return maxVowelCount;
    }
};

int main() {
   
    int x = 10;
    int* ptr = &x;

    
    std::cout << "Value of x: " << x << std::endl;
    *ptr = 100;
    std::cout << "Address of x: " << &x << std::endl;
    std::cout << "Value of x using pointer: " << *ptr << std::endl;



    return 0;
}
