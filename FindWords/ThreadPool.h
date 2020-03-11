#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <mutex>
#include <functional>
#include <thread>
#include <queue>
#include <vector>
namespace ThreadPool {
	class ThreadPool {
	public:
		explicit ThreadPool(size_t threadCount = 1);
		~ThreadPool();
		void EnqueueJob(std::function<void()> job);
		bool IsAllThreadStop();
		void WorkerThread();
	private:
		std::vector<std::thread> workerThreads_;
		std::queue<std::function<void()>> jobs_;

		std::condition_variable conditionJobQuqueVariable;
		std::mutex mutexJobsQueue_;

		size_t threadCount_;
		bool stopAllThread_;
	};
}
#endif
