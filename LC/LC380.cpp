#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;


class RandomizedSet {

    private:
    unordered_map<int, int>* map;

    public:
    RandomizedSet() {
        this->map = new unordered_map<int,int>;
    }
    
    bool insert(int val) {
        (*this->map)[val] = 1;
        return true;
    }
    
    bool remove(int val) {
        
    }
    
    int getRandom() {
        
    }
};

    
int main() {


    return 0;
}

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * boolean param_1 = obj.insert(val);
 * boolean param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
