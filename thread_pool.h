#pragma once
#include<iostream>
#include<thread>
#include<vector>
#include<future>
#include"safe_queue.cpp"

class thread_pool
{
public:
	thread_pool();
	thread_pool(const thread_pool&) = delete;
	thread_pool(thread_pool&) = delete;
	thread_pool& operator= (thread_pool&) = delete;
	thread_pool& operator= (const thread_pool&) = delete;
	~thread_pool();
	
	void submit(std::packaged_task<void()>& pt);
	void go();
	void stop();
private:
	void work();
	std::vector<std::thread> vths;
	safe_queue<std::packaged_task<void()>> safeq;
};