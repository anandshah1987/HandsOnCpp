// ThreadSafeQueue.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <queue>
#include <condition_variable>
#include <atomic>
#include <iostream>

template <typename T>
class ThreadSafeQueue
{
    std::queue<T> m_queue;
    std::mutex m_mutex;
public :

    void Push(const T& data)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(data);
    }

    // Universal reference
    template <typename ...Args>
    void Emplace(Args&&... args)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.emplace(std::forward<Args>(args)...);  
    }

    void PopFront(T& data)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        data = m_queue.front();
        m_queue.pop();
    }

    void PopFrontNoLock(T& data)
    {
        data = m_queue.front();
        m_queue.pop();
    }

    size_t Size()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.size();
    }

    bool Empty()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }

    bool EmptyNoLock()
    {
        return m_queue.empty();
    }

    std::mutex& GetMutex()
    {
        return m_mutex;
    }

};

template <typename T>
class ReaderWriterQueue
{
    ThreadSafeQueue<T> m_safeQueue{};
    std::condition_variable m_condVar{};
    std::atomic<bool> m_writeCompleted{};
public :
    void Push(const T& data)
    {
        m_safeQueue.Push(data);
        m_condVar.notify_one();
    }

    // Universal reference
    template <typename ...Args>
    void Emplace(Args&&... args)
    {
        m_safeQueue.Emplace(std::forward<Args>(args)...);
        m_condVar.notify_one();
    }

    void PopFront(T& data)
    {
        std::unique_lock<std::mutex> lock(m_safeQueue.GetMutex());
        m_condVar.wait(lock, [this] {return (!m_safeQueue.EmptyNoLock() || m_writeCompleted); });
        m_safeQueue.PopFrontNoLock(data);
    }

    void NotifyWriteEnd()
    {
        m_writeCompleted = true;
    }

    bool IsWriteFinished() const
    {
        return m_writeCompleted;
    }

    bool Empty()
    {
        return m_safeQueue.Empty();
    }
    
};

void ProduceData(ReaderWriterQueue<int>& queue)
{
    int i = 0;
    while (i < 10)
    {
        queue.Emplace(i);
        i++;
    }
    queue.NotifyWriteEnd();
    std::cout << "Finished Writing" << std::endl;
}

void ReadData(ReaderWriterQueue<int>& queue)
{
    while (!queue.IsWriteFinished() || !queue.Empty())
    {
        int waitTime;
        queue.PopFront(waitTime);
        std::cout << "popped " << waitTime << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(waitTime));
    }
    std::cout << "Finished Reading" << std::endl;
}


int main()
{
    ReaderWriterQueue<int> rwQueue;
    std::thread writer(ProduceData, std::ref(rwQueue));
    const int readerThreadCount = 2;
    std::thread readers[readerThreadCount];
    for (int count=0; count < readerThreadCount; count++)
    {
        std::thread reader(ReadData, std::ref(rwQueue));
        readers[count] = std::move(reader);
    }
   
    if (writer.joinable())
    {
        writer.join();
    }
    for (int count = 0; count < readerThreadCount; count++)
    {
        if (readers[count].joinable())
        {
            readers[count].join();
        }
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
