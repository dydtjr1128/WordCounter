#include "ThreadPool.h"

namespace ThreadPool {

	ThreadPool::ThreadPool(size_t threadCount) :
		threadCount_(threadCount),
		stopAllThread_(false) {
		workerThreads_.reserve(threadCount_);
		for (size_t i = 0; i < threadCount_; i++) {
			workerThreads_.emplace_back([this]() {this->WorkerThread(); });
		}

	}

	ThreadPool::~ThreadPool() {
		stopAllThread_ = true;
		conditionJobQuqueVariable.notify_all();

		for (auto& t : workerThreads_) {
			t.join();
		}
	}

	void ThreadPool::EnqueueJob(std::function<void()> job) {
		if (stopAllThread_) {
			throw std::runtime_error("ThreadPool ��� ������");
		}
		{
			std::lock_guard<std::mutex> lock(mutexJobsQueue_);
			jobs_.push(std::move(job));
		}
		//������� �����带 �ϳ� ����
		conditionJobQuqueVariable.notify_one();
	}

	bool ThreadPool::IsAllThreadStop() {
		return stopAllThread_;
	}

	void ThreadPool::WorkerThread() {
		while (true) {
			std::unique_lock<std::mutex> lock(mutexJobsQueue_);
			conditionJobQuqueVariable.wait(lock, [this]() { return !this->jobs_.empty() || stopAllThread_; });
			if (stopAllThread_ && this->jobs_.empty()) { // ����
				return;
			}

			// �� ���� job �� ����.
			std::function<void()> job = std::move(jobs_.front());
			jobs_.pop();
			lock.unlock();

			// �ش� job �� �����Ѵ� :)
			job();
		}
	}

}
