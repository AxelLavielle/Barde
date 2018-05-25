/*
  ==============================================================================

    NonCopyable.h
    Created: 25 May 2018 7:47:22am
    Author:  Anthony

  ==============================================================================
*/

#pragma once

class NonCopyable
{
public:
	NonCopyable(void) {}
	~NonCopyable(void) {}
	NonCopyable(const NonCopyable & other) = delete;
	NonCopyable & operator=(const NonCopyable & other) = delete;
};