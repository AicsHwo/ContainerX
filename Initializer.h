#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <vector>
#include <initializer_list>
#include "SupportIterator.h"

// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~

template <class T>
struct initializer : public SupportIterator<initializer<T>, T>
{
	std::vector<T> data{};
	// >> Constructor
	initializer(const std::vector<T>& inData = {})
		:data(inData)
	{
		// ~
	}
	// >> Constructor
	initializer(const std::initializer_list<T>& args)
	{
		data.resize(args.size());
		size_t i{};
		for(auto const& it : args) {	data[i++] = it;	}
	}
	// >> Member Function
	bool isEmpty(void) const
	{
		return (data.size() == 0);
	}
	// >> Support Feature : Iterator
	size_t length(void) const
	{
		return data.size();
	}
	T& operator[](const size_t& sel)
	{
		assert( sel < data.size() );
		return data[sel];
	}
	const T operator[](const size_t& sel) const	// return const T& ?
	{
		assert( sel < data.size() );
		return data[sel];
	}
};

// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~



#endif // INITIALIZER_H
