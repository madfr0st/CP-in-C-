#include <iostream>
#include <queue>
#include <thread>
#include <functional>
#include <condition_variable>
#include <vector>
#include <atomic>
using namespace std;

template<typename T>
class BoundedQueue {
    mutex m;
    bool active = true;
    size_t size;
    queue<T> queue;
    condition_variable is_full, is_empty;

    function<bool()> func_1 = [this]() -> bool {
        return queue.size() < size || !active;
    };

    function<bool()> func_2 = [this]() -> bool {
        return !queue.empty() || !active;
    };

public:
    BoundedQueue(size_t n) : size(n) {};

    void close() {
        lock_guard<mutex> lock(m);
        active = false;
        is_full.notify_all();
        is_empty.notify_all();
    }

    bool push(T data) {
        unique_lock<mutex> lock(m);
        is_full.wait(lock, func_1);
        if (!active) return false;
        queue.emplace(move(data));
        is_empty.notify_all();
        return true;
    }

    bool pop(T &data) {
        unique_lock<mutex> lock(m);
        is_empty.wait(lock, func_2);
        if (!active) return false;
        data = move(queue.front());
        queue.pop();
        is_full.notify_all();
        return true;
    }
};

int main() {
    BoundedQueue<pair<int, int>> queue(4);

    auto producer = [&queue](int a, int b) -> void {
        for (int i = a; i < b; i++) {
            pair<int, int> pair(i, b);
            queue.push(pair);
            cout << "Produced data: " << pair.first << " , " << pair.second << endl;
            this_thread::sleep_for(100ms);
        }
    };

    auto consumer = [&queue]() -> void {
        pair<int, int> pair;
        while (queue.pop(pair)) {
            cout << "Consumed data: " << pair.first << " , " << pair.second << endl;
        }
        cout << "Queue is no longer active" << endl;
    };

    vector<thread> v_producers;
    vector<thread> v_consumers;

    for (int i = 0; i < 10; i++) {
        v_producers.emplace_back(producer, i, 10);
    }

    for (int i = 0; i < 4; i++) {
        v_consumers.emplace_back(consumer);
    }

    for (auto& t : v_producers) {
        t.join();
    }

    queue.close();

    for (auto& t : v_consumers) {
        t.join();
    }

    cout << "Task ended" << endl;
    return 0;
}
