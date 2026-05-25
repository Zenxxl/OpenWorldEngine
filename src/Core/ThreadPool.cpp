// ThreadPool.cpp
#include "ThreadPool.h"
#include <utility>

using namespace Motor3D::Core;

ThreadPool::ThreadPool(size_t threadCount) {
	if (threadCount == 0) threadCount = 1;
	for (size_t i = 0; i < threadCount; ++i) {
		workers.emplace_back([this]() {
			for (;;) {
				std::function<void()> task;
				{
					std::unique_lock<std::mutex> lock(this->queueMutex);
					this->condition.wait(lock, [this]() { return this->stop || !this->tasks.empty(); });
					if (this->stop && this->tasks.empty()) return;
					task = std::move(this->tasks.front());
					this->tasks.pop();
				}
				task();
			}
		});
	}
}

ThreadPool::~ThreadPool() {
	{
		std::unique_lock<std::mutex> lock(queueMutex);
		stop = true;
	}
	condition.notify_all();
	for (std::thread &worker : workers) worker.join();
}

// Template Submit implementation moved to header.
