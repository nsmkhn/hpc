#include "thread_pool.h"

ThreadPool::ThreadPool(size_t num_workers)
    : m_running(true), m_num_workers(num_workers),
    m_workers(std::make_unique<std::thread[]>(m_num_workers))
{
    for(size_t i = 0; i < m_num_workers; ++i)
        m_workers[i] = std::thread(&ThreadPool::worker, this);
}

ThreadPool::~ThreadPool()
{
    join_workers();
}

void
ThreadPool::add_task(std::function<void()> task)
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_tasks.push(task);
    }
    m_condition.notify_one();
}

void
ThreadPool::worker()
{
    for(;;)
    {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_condition.wait(lock, [this](){
                return !m_tasks.empty() || !m_running;
            });
            if(m_tasks.empty())
                break;
            task = std::move(m_tasks.front());
            m_tasks.pop();
        }
        task();
    }
}

void
ThreadPool::join_workers()
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_running = false;
    }
    m_condition.notify_all();
    for(size_t i = 0; i < m_num_workers; ++i)
        if(m_workers[i].joinable())
            m_workers[i].join();
}
