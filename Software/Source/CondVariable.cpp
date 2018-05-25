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
	_m.lock();
	if (!_wait)
	{
		_m.unlock();
		return;
	}
	_state = true;
	_m.unlock();
	_cond.notify_one();
}

bool CondVariable::getState()
{
	return (_state);
}

void CondVariable::wait()
{
	_m.lock();
	_wait = true;
	_m.unlock();
	std::unique_lock<std::mutex> lk(_m);
	while (!getState())
		_cond.wait(lk, std::bind(&CondVariable::getState, this));
	_m.lock();
	_state = false;
	_wait = false;
	_m.unlock();
}