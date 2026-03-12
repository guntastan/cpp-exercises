// exercise 13: concurrency and multithreading
// learn: std::thread, mutex, lock_guard, condition_variable, async, future

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <vector>
#include <string>
#include <chrono>
#include <queue>

// ==== basic thread creation ====

void basicTask(int id, std::string name) {
    std::cout << "thread " << id << " (" << name << ") running" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "thread " << id << " (" << name << ") done" << std::endl;
}

void demonstrateBasicThreads() {
    std::cout << "\n=== basic thread creation ===" << std::endl;
    
    std::thread t1(basicTask, 1, "worker1");
    std::thread t2(basicTask, 2, "worker2");
    std::thread t3(basicTask, 3, "worker3");
    
    t1.join();  // wait for t1 to finish
    t2.join();
    t3.join();
    
    std::cout << "all threads finished" << std::endl;
}

// ==== mutex and race conditions ====

int counter = 0;
std::mutex counterMutex;

void incrementWithoutLock(int times) {
    for (int i = 0; i < times; i++) {
        counter++;  // race condition!
    }
}

void incrementWithLock(int times) {
    for (int i = 0; i < times; i++) {
        std::lock_guard<std::mutex> lock(counterMutex);  // auto unlocks
        counter++;
    }
}

void demonstrateMutex() {
    std::cout << "\n=== mutex and race conditions ===" << std::endl;
    
    // without mutex (race condition)
    counter = 0;
    std::thread t1(incrementWithoutLock, 1000);
    std::thread t2(incrementWithoutLock, 1000);
    t1.join();
    t2.join();
    std::cout << "without mutex (expected 2000): " << counter << std::endl;
    
    // with mutex (thread safe)
    counter = 0;
    std::thread t3(incrementWithLock, 1000);
    std::thread t4(incrementWithLock, 1000);
    t3.join();
    t4.join();
    std::cout << "with mutex (expected 2000): " << counter << std::endl;
}

// ==== condition variable (producer-consumer) ====

std::queue<int> dataQueue;
std::mutex queueMutex;
std::condition_variable dataReady;
bool finished = false;

void producer() {
    for (int i = 1; i <= 5; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            dataQueue.push(i);
            std::cout << "produced: " << i << std::endl;
        }
        dataReady.notify_one();  // wake up consumer
    }
    
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        finished = true;
    }
    dataReady.notify_one();
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(queueMutex);
        dataReady.wait(lock, [] { return !dataQueue.empty() || finished; });
        
        while (!dataQueue.empty()) {
            int value = dataQueue.front();
            dataQueue.pop();
            lock.unlock();
            std::cout << "consumed: " << value << std::endl;
            lock.lock();
        }
        
        if (finished) break;
    }
}

void demonstrateConditionVariable() {
    std::cout << "\n=== condition variable (producer-consumer) ===" << std::endl;
    
    finished = false;
    
    std::thread prod(producer);
    std::thread cons(consumer);
    
    prod.join();
    cons.join();
    
    std::cout << "producer-consumer finished" << std::endl;
}

// ==== async and future ====

int heavyComputation(int n) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    int result = 0;
    for (int i = 1; i <= n; i++) {
        result += i;
    }
    return result;
}

void demonstrateAsyncFuture() {
    std::cout << "\n=== async and future ===" << std::endl;
    
    // launch async task
    std::future<int> result1 = std::async(std::launch::async, heavyComputation, 100);
    std::future<int> result2 = std::async(std::launch::async, heavyComputation, 200);
    
    std::cout << "tasks launched, doing other work..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "other work done, waiting for results..." << std::endl;
    
    // get() blocks until result is ready
    std::cout << "sum 1-100: " << result1.get() << std::endl;
    std::cout << "sum 1-200: " << result2.get() << std::endl;
}

// ==== thread pool (practical example) ====

class ThreadPool {
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex taskMutex;
    std::condition_variable taskAvailable;
    bool stop = false;

public:
    ThreadPool(int numThreads) {
        for (int i = 0; i < numThreads; i++) {
            workers.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(taskMutex);
                        taskAvailable.wait(lock, [this] {
                            return stop || !tasks.empty();
                        });
                        
                        if (stop && tasks.empty()) return;
                        
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
        std::cout << "thread pool created with " << numThreads << " threads" << std::endl;
    }
    
    void submit(std::function<void()> task) {
        {
            std::lock_guard<std::mutex> lock(taskMutex);
            tasks.push(std::move(task));
        }
        taskAvailable.notify_one();
    }
    
    ~ThreadPool() {
        {
            std::lock_guard<std::mutex> lock(taskMutex);
            stop = true;
        }
        taskAvailable.notify_all();
        for (auto& worker : workers) {
            worker.join();
        }
        std::cout << "thread pool destroyed" << std::endl;
    }
};

void demonstrateThreadPool() {
    std::cout << "\n=== thread pool ===" << std::endl;
    
    ThreadPool pool(3);
    std::mutex printMutex;
    
    for (int i = 1; i <= 6; i++) {
        pool.submit([i, &printMutex] {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            std::lock_guard<std::mutex> lock(printMutex);
            std::cout << "task " << i << " completed by thread "
                      << std::this_thread::get_id() << std::endl;
        });
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

int main() {
    std::cout << "=== concurrency and multithreading ===" << std::endl;
    
    demonstrateBasicThreads();
    demonstrateMutex();
    demonstrateConditionVariable();
    demonstrateAsyncFuture();
    demonstrateThreadPool();
    
    std::cout << "\n=== key concepts ===" << std::endl;
    std::cout << "std::thread: creates and manages threads" << std::endl;
    std::cout << "join(): wait for thread to finish" << std::endl;
    std::cout << "mutex: prevents race conditions (mutual exclusion)" << std::endl;
    std::cout << "lock_guard: RAII wrapper for mutex (auto unlock)" << std::endl;
    std::cout << "condition_variable: thread synchronization/signaling" << std::endl;
    std::cout << "async/future: run tasks asynchronously, retrieve results later" << std::endl;
    std::cout << "thread pool: reuse threads for multiple tasks" << std::endl;
    
    return 0;
}