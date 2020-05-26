#ifndef RANGE_H
#define RANGE_H

#include <iostream>
#include <vector>

// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~

struct Range1D
{
	size_t start, end;
	Range1D operator+(const Range1D& inRight) const
	{
		return Range1D{start + inRight.start, end + inRight.end};
	}
	Range1D operator-(const Range1D& inRight) const
	{
		size_t _start_((start < inRight.start)? 0 : start - inRight.start);
		size_t _end_((end < inRight.end)? 0 : end - inRight.end);
		return Range1D{ _start_, _end_ };
		// return Range1D{start - inRight.start, end - inRight.end};
	}
	Range1D& operator+=(const Range1D& inRight)
	{
		start += inRight.start;
		end += inRight.end;
		return *this;
	}
	// >> 
	friend Range1D operator+(const Range1D& inLeft, const size_t& inRight)
	{
		return Range1D{inLeft.start + inRight, inLeft.end + inRight};
	}
	friend Range1D operator/(const Range1D& inLeft, const size_t& inRight)
	{
		assert(inRight != 0);
		return Range1D{inLeft.start / inRight, inLeft.end / inRight};
	}
	friend Range1D operator*(const Range1D& inLeft, const size_t& inRight)
	{
		return Range1D{inLeft.start * inRight, inLeft.end * inRight};
	}
	// >>
	inline size_t length(void) const
	{
		return end - start + 1;
	}
	// >>
	friend Range1D bound(const Range1D& in, const Range1D& boundary)
	{
		size_t _start_((in.start < boundary.start)? boundary.start : in.start);
		size_t _end_((in.end > boundary.end)? boundary.end : in.end);
		return Range1D{ _start_, _end_ };
	}
	// >>
	friend std::ostream& operator<<(std::ostream& os, const Range1D& out)
	{
		os << "[" << out.start << ", " << out.end << "]";
		return os;
	}
};
struct Range : public SupportIterator<Range, Range1D>
{
	std::vector<Range1D> data{};
	// >> Constructor
	Range(const std::vector<Range1D>& inData = {})
			: data(inData)
	{
		// ~
	}
	// >> Copy Constructor
	Range(const Range& inCopy)
		: data(inCopy.data)
	{
		// ~
	}
	// >>
	void resize(const size_t& inSize)
	{
		data.resize(inSize);
	}
	void replace(const std::vector<Range1D>& inData)
	{
		data = inData;
	}
	void append(const Range& inR)
	{
		data.insert(data.end(), inR.data.begin(), inR.data.end());
	}
	// >> Support Feature : Iterator
	size_t length(void) const
	{
		return data.size();
	}
	Range1D& operator[](const size_t& sel)
	{
		assert( sel < data.size() );
		return data[sel];
	}
	const Range1D& operator[](const size_t& sel) const
	{
		assert( sel < data.size() );
		return data[sel];
	}
	// >> Operator Overloading
	Range operator+(const Range& inR) const
	{
		Range ret(*this);
		for(size_t i = 0; i < length(); i++)
		{
			ret[i] += inR[i];
		}
		return ret;
	}
	friend Range operator+(const Range& inL, const Range1D& inR)
	{
		Range ret(inL);
		for(auto& it : ret)
		{
			it += inR;
		}
		return ret;
	}
	friend Range operator/(const Range& inL, const size_t& inR)
	{
		Range ret(inL);
		for(auto& it : ret)
		{
			it = it / inR;
		}
		return ret;
	}
	friend Range operator/(const Range& inL, const std::vector<size_t>& inR)
	{
		assert(inL.length() == inR.size());
		Range ret(inL);
		for(size_t i = 0; i < inL.length(); i++)
		{
			ret[i] = ret[i] / inR[i];
		}
		return ret;
	}
	friend Range ceilDiv(const Range& inL, const std::vector<size_t>& inR)
	{
		assert(inL.length() == inR.size());
		const Range1D one( {1,1} );
		Range ret(inL);
		for(size_t i = 0; i < inL.length(); i++)
		{
			//ret[i] = one + ((ret[i]-one) / inR[i]);
			ret[i] = (ret[i]+inR[i]-one) / inR[i];
		}
		return ret;
	}
	// >> 
	Range alignZero(void) const
	{
		Range ret(*this);
		for(auto& it : ret){	it = Range1D{ 0, it.length()};		}
		return ret;
	}
	Range toLength(void) const
	{
		Range ret(*this);
		for(auto& it : ret){	it = Range1D{ it.length(), it.length()};	}
		return ret;
	}
	Range toStartPoint(void) const
	{
		Range ret(*this);
		for(auto& it : ret){	it = Range1D{ it.start, it.start};	}
		return ret;
	}
	// >> 
	std::vector<size_t> hyperCube(void) const
	{
		std::vector<size_t> tmp{};
		for(auto const& it : data)
		{
			tmp.push_back( it.length() );
		}
		return tmp;
	}
	size_t dimension(void) const
	{
		return data.size();
	}
	Range subDimension(void) const
	{
		return Range( std::vector<Range1D>(data.begin()+1, data.end()) );
	}
	friend std::ostream& operator<<(std::ostream& os, const Range& out)
	{
		for(auto const& it : out.data)
		{
			os << it << " ";
		}
		return os;
	}
};

// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~

#endif // RANGE_H
