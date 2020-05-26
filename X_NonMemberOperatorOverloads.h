

// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~

// [!] Well utilize non-member operator overloads to split code files.
// [!] Notice the friend declaration if it were made inside the class.

// >> CAN be non-member
// + - * / % ? & | ~ ! < > += -= *= /= %= ?= &= |= << >> >>= <<= == != <= >= && || ++ -- , ->*
// >> Implement : 
// >> + , - , * , /, & , |, unary -
// >> ! , &&, ||
// >> += , -= , *=, /=
// >> < , > , == , != , <= , >=
// >> ++ , --
// 
// >> CANNOT be non-member
// = , ( ) , [ ] ,  ->

// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~



// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~
//		                 A R I T H M E T I C     O P E R A T O R S
// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~

template<class T, size_t dim>
inline X<T, dim> operator+(const X<T, dim>& inL, const X<T, dim>& inR)
{
	assert(inL.length() == inR.length());
	X<T, dim> ans(inL);
	for(size_t i = 0; i < ans.length(); i++)
	{
		ans[i] += inR[i];
	}
	return ans;
}


template<class T, size_t dim>
inline X<T, dim> operator-(const X<T, dim>& inL, const X<T, dim>& inR)
{
	assert(inL.length() == inR.length());
	X<T, dim> ans(inL);
	for(size_t i = 0; i < ans.length(); i++)
	{
		ans[i] -= inR[i];
	}
	return ans;
}


template<class T, size_t dim>
inline X<T, dim> operator*(const X<T, dim>& inL, const X<T, dim>& inR)
{
	assert(inL.length() == inR.length());
	X<T, dim> ans(inL);
	for(size_t i = 0; i < ans.length(); i++)
	{
		ans[i] *= inR[i];
	}
	return ans;
}


template<class T, size_t dim>
inline X<T, dim> operator/(const X<T, dim>& inL, const X<T, dim>& inR)
{
	const T zero{};
	assert(inL.length() == inR.length());
	X<T, dim> ans(inL);
	for(size_t i = 0; i < ans.length(); i++)
	{
		if( inR[i] != zero )
			ans[i] /= inR[i];
	}
	return ans;
}


template<class T, size_t dim>
inline X<T, dim> operator&(const X<T, dim>& inL, const X<T, dim>& inR)
{
	assert(inL.length() == inR.length());
	X<T, dim> ans(inL);
	for(size_t i = 0; i < ans.length(); i++)
	{
		ans[i] &= inR[i];
	}
	return ans;
}

template<class T, size_t dim>
inline X<T, dim> operator|(const X<T, dim>& inL, const X<T, dim>& inR)
{
	assert(inL.length() == inR.length());
	X<T, dim> ans(inL);
	for(size_t i = 0; i < ans.length(); i++)
	{
		ans[i] |= inR[i];
	}
	return ans;
}

template<class T, size_t dim>
inline X<T, dim> operator-(const X<T, dim>& inL)
{
	X<T, dim> ans(inL.hyperCube());
	for(size_t i = 0; i < ans.length(); i++)
	{
		ans[i] = -inL[i];
	}
	return ans;
}

// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~
//		                		 L O G I C     O P E R A T O R S
// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~

template<class T, size_t dim>
inline X<bool, dim> operator!(const X<T, dim>& inL)
{
	// [!] Type-cast or conversion constructor required
	X<bool, dim> ans(inL.hyperCube());
	for(size_t i = 0; i < ans.length(); i++)
	{
		ans[i] = !inL[i];
	}
	return ans;
}


template<class T, size_t dim>
inline X<bool, dim> operator&&(const X<T, dim>& inL, const X<T, dim>& inR)
{
	// [!] Type-cast or conversion constructor required
	assert(inL.length() == inR.length());
	X<bool, dim> ans(inL.hyperCube());
	for(size_t i = 0; i < ans.length(); i++)
	{
		ans[i] = inL[i] && inR[i];
	}
	return ans;
}


template<class T, size_t dim>
inline X<bool, dim> operator||(const X<T, dim>& inL, const X<T, dim>& inR)
{
	// [!] Type-cast or conversion constructor required
	assert(inL.length() == inR.length());
	X<bool, dim> ans(inL.hyperCube());
	for(size_t i = 0; i < ans.length(); i++)
	{
		ans[i] = inL[i] || inR[i];
	}
	return ans;
}


// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~
//		         A R I T H M E T I C     A S S I G N M E N T     O P E R A T O R S
// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~


template<class T, size_t dim>
inline X<T, dim>& operator+=(X<T, dim>& inL, const X<T, dim>& inR)
{
	assert(inL.length() == inR.length());
	X<T, dim>& ans(inL);
	for(size_t i = 0; i < ans.length(); i++)
	{
		ans[i] += inR[i];
	}
	return ans;
}


template<class T, size_t dim>
inline X<T, dim>& operator-=(X<T, dim>& inL, const X<T, dim>& inR)
{
	assert(inL.length() == inR.length());
	X<T, dim>& ans(inL);
	for(size_t i = 0; i < ans.length(); i++)
	{
		ans[i] -= inR[i];
	}
	return ans;
}


template<class T, size_t dim>
inline X<T, dim>& operator*=(X<T, dim>& inL, const X<T, dim>& inR)
{
	assert(inL.length() == inR.length());
	X<T, dim>& ans(inL);
	for(size_t i = 0; i < ans.length(); i++)
	{
		ans[i] *= inR[i];
	}
	return ans;
}


template<class T, size_t dim>
inline X<T, dim>& operator/=(X<T, dim>& inL, const X<T, dim>& inR)
{
	const T zero{};
	assert(inL.length() == inR.length());
	X<T, dim>& ans(inL);
	for(size_t i = 0; i < ans.length(); i++)
	{
		if( inR[i] != zero )
			ans[i] /= inR[i];
	}
	return ans;
}



// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~
//		         			C O M P A R I S O N     O P E R A T O R S
// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~


template<class T, size_t dim>
inline X<bool, dim> operator==(const X<T, dim>& inL, const X<T, dim>& inR)
{
	// [!] Type-cast or conversion constructor required
	assert(inL.length() == inR.length());
	X<bool, dim> ans(inL.hyperCube());
	for(size_t i = 0; i < ans.length(); i++)
	{
		ans[i] = (inL[i] == inR[i]);
	}
	return ans;
}


template<class T, size_t dim>
inline X<bool, dim> operator!=(const X<T, dim>& inL, const X<T, dim>& inR)
{
	// [!] Type-cast or conversion constructor required
	assert(inL.length() == inR.length());
	X<bool, dim> ans(inL.hyperCube());
	for(size_t i = 0; i < ans.length(); i++)
	{
		ans[i] = (inL[i] != inR[i]);;
	}
	return ans;
}


template<class T, size_t dim>
inline X<bool, dim> operator>(const X<T, dim>& inL, const X<T, dim>& inR)
{
	// [!] Type-cast or conversion constructor required
	assert(inL.length() == inR.length());
	X<bool, dim> ans(inL.hyperCube());
	for(size_t i = 0; i < ans.length(); i++)
	{
		ans[i] = (inL[i] > inR[i]);;
	}
	return ans;
}

template<class T, size_t dim>
inline X<bool, dim> operator>=(const X<T, dim>& inL, const X<T, dim>& inR)
{
	// [!] Type-cast or conversion constructor required
	assert(inL.length() == inR.length());
	X<bool, dim> ans(inL.hyperCube());
	for(size_t i = 0; i < ans.length(); i++)
	{
		ans[i] = (inL[i] >= inR[i]);;
	}
	return ans;
}

template<class T, size_t dim>
inline X<bool, dim> operator<(const X<T, dim>& inL, const X<T, dim>& inR)
{
	// [!] Type-cast or conversion constructor required
	assert(inL.length() == inR.length());
	X<bool, dim> ans(inL.hyperCube());
	for(size_t i = 0; i < ans.length(); i++)
	{
		ans[i] = (inL[i] < inR[i]);;
	}
	return ans;
}

template<class T, size_t dim>
inline X<bool, dim> operator<=(const X<T, dim>& inL, const X<T, dim>& inR)
{
	// [!] Type-cast or conversion constructor required
	assert(inL.length() == inR.length());
	X<bool, dim> ans(inL.hyperCube());
	for(size_t i = 0; i < ans.length(); i++)
	{
		ans[i] = (inL[i] <= inR[i]);;
	}
	return ans;
}




