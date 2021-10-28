#pragma once
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

struct ThreadPool
{
    ThreadPool(size_t num_workers = std::thread::hardware_concurrency());
    ~ThreadPool();
    void add_task(std::function<void()> task);
    void join_workers();

private:
    void worker();

private:
    bool                                m_running;
    size_t                              m_num_workers;
    std::unique_ptr<std::thread[]>      m_workers;
    std::queue<std::function<void()>>   m_tasks;
    std::mutex                          m_mutex;
    std::condition_variable             m_condition;
};
