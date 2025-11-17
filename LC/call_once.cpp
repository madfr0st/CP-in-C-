
// call_once.cpp
#include <mutex>
#include <thread>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

std::once_flag once;
int expensive_resource = 0;

void init() { expensive_resource = 12345;
    cout << "delta" <<endl; }

void use() {
    std::call_once(once, init);
    std::cout << expensive_resource << "\n";
}

int main() {
    std::thread a(use), b(use), c(use);
    a.join(); b.join(); c.join();
}
