#pragma once
#include <iostream>
#include <mutex>

class NonThreadSafeSingleton
{
public:
    static NonThreadSafeSingleton& getInstance() {
        if (sInstance == nullptr) {
            std::cout << "Create a Singleton" << "\n";
            std::chrono::seconds duration(2);
            std::this_thread::sleep_for(duration);
            sInstance = new NonThreadSafeSingleton();
        }
        return *sInstance;
    }
    int GetValue() const { return value; }
    static void SetValue() {
        std::chrono::seconds duration(2);
        std::this_thread::sleep_for(duration);
        value++;
        std::cout << value << " ";
    }


private:
    NonThreadSafeSingleton() {}
    static int value;
    static NonThreadSafeSingleton* sInstance;
};
int NonThreadSafeSingleton::value = 0;
NonThreadSafeSingleton* NonThreadSafeSingleton::sInstance = nullptr;

class ThreadSafeLockSingleton
{
public:
    static ThreadSafeLockSingleton& getInstance() {
        std::lock_guard<std::mutex> lock(sMutex);
        if (sInstance == nullptr) {
            std::cout << "Create a Singleton";
            sInstance = new ThreadSafeLockSingleton();
        }
        return *sInstance;
    }

    int GetValue() const { return value; }
    static void SetValue() {
        //std::lock_guard<std::mutex> lock(sMutex);
        std::chrono::seconds duration(2);
        std::this_thread::sleep_for(duration);
        value++;
        std::cout << value << " ";
    }

private:
    ThreadSafeLockSingleton() {
    }
    static int value;
    static std::mutex sMutex;
    static ThreadSafeLockSingleton* sInstance;
};
int ThreadSafeLockSingleton::value = 0;
std::mutex ThreadSafeLockSingleton::sMutex;
ThreadSafeLockSingleton* ThreadSafeLockSingleton::sInstance = nullptr;


class ThreadSafeMeyersSingleton
{
public:
    static ThreadSafeMeyersSingleton& getInstance() {
        static ThreadSafeMeyersSingleton sInstance;
        return sInstance;
    }

    int GetValue() const { return value; }
    static void SetValue() {
        std::chrono::seconds duration(2);
        std::this_thread::sleep_for(duration);
        value++;
        std::cout << value << " ";
    }

private:
    ThreadSafeMeyersSingleton() {}
    static int value;
    mutable std::mutex mutex_;
};
int ThreadSafeMeyersSingleton::value = 0;

void TestMultiThreadSingleton() {
    const int numThreads = 50;
    std::thread threads[numThreads];

    // Create multiple threads
    for (int i = 0; i < numThreads; ++i) {
        threads[i] = std::thread([]() {
            ThreadSafeLockSingleton::getInstance().SetValue();
            });
    }

    // Join the threads
    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }
}

