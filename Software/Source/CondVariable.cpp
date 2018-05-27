#include "CondVariable.hh"

CondVariable::CondVariable()
{
	_wait = false;
	_state = false;
}


CondVariable::~CondVariable()
{
}

void CondVariable::notify()
{
	std::lock_guard<std::mutex> lock(_m);
	if (!_wait)
		return;
	_state = true;
	_cond.notify_one();
}

bool CondVariable::getState()
{
	return (_state);
}

void CondVariable::wait()
{
	{
		std::lock_guard<std::mutex> lock(_m);
		_wait = true;
	}
	std::unique_lock<std::mutex> lk(_m);
	while (!getState())
		_cond.wait(lk, std::bind(&CondVariable::getState, this));
	_state = false;
	_wait = false;
}