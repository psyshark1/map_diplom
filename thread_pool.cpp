#include"thread_pool.h"

thread_pool::thread_pool()
{
	const unsigned cores = std::thread::hardware_concurrency();
	for (unsigned i{ 0 }; i < cores; ++i)
	{
		vths.push_back(std::thread(&thread_pool::work, this));
	}
}

void thread_pool::work()
{
	this->safeq.pop();
}

void thread_pool::submit(std::packaged_task<void()>& pt)
{
	safeq.push(std::move(pt));
}

void thread_pool::go()
{
	this->safeq.notify();
}

void thread_pool::stop()
{
	this->safeq.stop();
}

thread_pool::~thread_pool()
{
	for (auto& it : vths)
	{
		it.join();
	}
}