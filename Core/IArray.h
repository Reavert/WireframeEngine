#pragma once
#include <vector>

template <typename T>
class IArray
{
public:
	virtual std::vector<T> ToArray() = 0;
};

