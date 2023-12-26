#pragma once
#include<mutex>
#include<queue>
#include<condition_variable>
#include<chrono>

template <class T>
class safe_queue
{
public:
	safe_queue() {};
	~safe_queue(){};

	void push(T&& tc)
	{
		std::lock_guard lg{ m };
		sq.push(std::move(tc));
	};
	void pop()
	{
		std::unique_lock ul{ m };
		while (true)
		{
			if (!ul.owns_lock()) { ul.lock(); }
			cv_dat.wait(ul, [&]() {return !sq.empty() || exit; });
			if (!sq.empty())
			{
				T entity = std::move(sq.front());
				entity();
				sq.pop();
				ul.unlock();
			}
			if (exit) { break; };
		}
	};

	void notify()
	{
		cv_dat.notify_all();
	}

	void stop()
	{
		exit = true;
		notify();
	}
private:
	std::mutex m;
	std::queue<T> sq;
	std::condition_variable cv_dat;
	bool exit{ false };
};