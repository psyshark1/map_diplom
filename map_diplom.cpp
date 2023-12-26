#include"thread_pool.h"

void func1()
{
	std::cout << "Executing: " << __FUNCTION__ << std::endl;
}
void func2()
{
	std::cout << "Executing: " << __FUNCTION__ << std::endl;
}

void func3()
{
	std::cout << "Executing: " << __FUNCTION__ << std::endl;
}

void func4()
{
	std::cout << "Executing: " << __FUNCTION__ << std::endl;
}

int main()
{
	thread_pool thpool;
	for (int i = 0; i < 5; ++i)
	{
		std::packaged_task<void()> pt1(func1);
		std::packaged_task<void()> pt2(func2);
		std::packaged_task<void()> pt3(func3);
		std::packaged_task<void()> pt4(func4);
		std::this_thread::sleep_for(std::chrono::seconds(2));
		thpool.submit(std::move(pt1));
		thpool.submit(std::move(pt2));
		thpool.submit(std::move(pt3));
		thpool.submit(std::move(pt4));
		thpool.go();
	}

	thpool.stop();
	return 0;
}
