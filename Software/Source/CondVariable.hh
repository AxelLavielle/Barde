#pragma once

#include <condition_variable>
#include <mutex>

class CondVariable
{
public:
	CondVariable();
	~CondVariable();
	void notify();
	void wait();
	void notifyAll();

private:
	bool getState();
	std::condition_variable _cond;
	bool _state;
	bool _wait;
	std::mutex _m;
};
