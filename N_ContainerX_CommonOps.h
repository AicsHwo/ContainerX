#ifndef COMMON_OPERATIONS_ON_CONTAINER_X_H
#define COMMON_OPERATIONS_ON_CONTAINER_X_H

// Abs(), Max(), Min(), Sum(), Avg(), Normalize()

#include <iostream>

namespace N_ContainerX_CommonOps
{
	template<class T, size_t dim>
	inline X<T, dim> Abs(const X<T, dim>& inX)
	{
		const T Zero{};
		X<T, dim> ans(inX.hyperCube());
		auto iterIn(inX.begin());
		auto iterOut(ans.begin());
		for(size_t i = 0; i < ans.length(); i++)
		{
			const auto& Val(*iterIn);
			auto& out(*iterOut);
			out = (Val < Zero)? -Val : Val;
			iterIn++;
			iterOut++;
		}
		return ans;
	}
	
	template<class T, size_t dim>
	inline const T Max(const X<T, dim>& inX)
	{
		auto iterIn(inX.begin());
		T tmp(*iterIn);
		for(auto const& Val : inX)
		{
			if(Val > tmp)
			{
				tmp = Val;
			}
		}
		return tmp;
	}
	
	template<class T, size_t dim>
	inline const T Min(const X<T, dim>& inX)
	{
		auto iterIn(inX.begin());
		T tmp(*iterIn);
		for(auto const& Val : inX)
		{
			if(Val < tmp)
			{
				tmp = Val;
			}
		}
		return tmp;
	}
	
	template<class T, size_t dim>
	inline const T Sum(const X<T, dim>& inX)
	{
		T tmp{};
		for(auto const& Val : inX)
		{
			tmp += Val;
		}
		return tmp;
	}
	
	#ifndef _USE_EXPANSION
	template<class T, size_t dim>
	inline const T Avg(const X<T, dim>& inX)
	{
		DBG( std::cout << inX.length() << std::endl; )
		return Sum( inX ) / (T)inX.length();
	}
	#else
	template<class T, size_t dim>
	inline auto Avg(const X<T, dim>& inX) -> decltype(T{}*0.1)
	{
		DBG( std::cout << inX.length() << std::endl; )
		return Sum( inX ) / (double)inX.length();
	}
	#endif
	
	template<class T, size_t dim>
	inline X<T, dim> Normalize(const X<T, dim>& inX)
	{
		const T _Max{Max(inX)}, _Min{Min(inX)};
		const T _Width{_Max-_Min};
		X<T, dim> ans(inX);
		for(auto& Val : ans)
		{
			Val = (Val - _Min) / _Width;
		}
		return ans;
	}
	
}

#endif // COMMON_OPERATIONS_ON_CONTAINER_X_H
