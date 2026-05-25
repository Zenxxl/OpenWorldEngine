// ThreadPool.h
#pragma once
#include <vector>
#include <thread>
#include <future>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <type_traits>
#include <stdexcept>

namespace Motor3D { namespace Core {

class ThreadPool {
public:
	ThreadPool(size_t threadCount = std::thread::hardware_concurrency());
	~ThreadPool();

	template<class F>
	auto Submit(F f) -> std::future<decltype(f())> {
		using return_type = decltype(f());
		auto task = std::make_shared<std::packaged_task<return_type()>>(std::move(f));
		std::future<return_type> res = task->get_future();
		{
			std::unique_lock<std::mutex> lock(queueMutex);
			if (stop) throw std::runtime_error("Submit on stopped ThreadPool");
			tasks.emplace([task]() { (*task)(); });
		}
		condition.notify_one();
		return res;
	}

private:
	std::vector<std::thread> workers;
	std::queue<std::function<void()>> tasks;
	std::mutex queueMutex;
	std::condition_variable condition;
	bool stop = false;
};

}}
