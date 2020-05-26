#ifndef SF_CONTAINER_SUPPORT_ITERATOR_H
#define SF_CONTAINER_SUPPORT_ITERATOR_H

// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~

template<class Container, class ElementType>
struct SupportIterator
{
	// [!] Usage : inherit this class and fulfill the following requirements :
	// 1. Provide "size_t length(void) const" member function implementation.
	// 2. Provide "T& operator[](size_t)" operator overloading.
	
	// >> Pure Virtual Function Requires Implementation :
	virtual size_t length(void) const = 0;
	// >> Support Iterator
	class iterator : public std::iterator<std::forward_iterator_tag, ElementType>
	{
        private:
            //  >> Data Member
            Container* ptr;
            size_t j{}, _length{};
        public:
            //  >> Implicit Default Constructor & Copy Constructor Explicitly write-out
            //	>> [!] CANNOT add "explicit" specifier to constructor
            iterator(Container* inPtr = nullptr, const int& jj = 0)
                : ptr(inPtr), j(jj)
            {
                if(ptr != nullptr)
                {
                	// DBG : std::cout << "DBG :" << ptr->length() << std::endl;
                    _length = ptr->length();
				}
            }
            iterator(const iterator& inCopy)
            {
                (*this) = inCopy;
            }
            iterator& operator=(const iterator& inCopy)
            {
                ptr = inCopy.ptr;
                j = inCopy.j;
                _length = ptr->length();
                return (*this);
            }
            //  >> Member functions
            //	[!] Notice we haven't provide operator -/+, so the std::distance(a,b) use operator++.
            //	
            //  ---->> the equality/inequality operators
            const bool operator==(const iterator& inRight) const
            {
                bool check_address(this == &inRight);
                bool check_content((ptr == inRight.ptr) && (j == inRight.j));
                return check_address || check_content;
            }
            const bool operator!=(const iterator& inRight) const
            {
                return !((*this) == inRight);
            }
            //  ---->> Overload l-value dereference operator
            ElementType& operator*(void) const
            {
                assert(ptr != nullptr);
                return (*ptr)[j];	// Container should provide operator[] overload
            }
            /*C* operator->(void) const
            {
                // should I return pointer or address of the element?
                assert(pointer != nullptr);
                return pointer;
            }*/
            //  ---->> Overload incremental operator (prefix ++ operator)
            iterator operator++(void)
            {
                j++;
                if(j >= _length) { j = _length;	}
                return iterator(ptr, j);
            }
            //  ---->> Overload incremental operator (postfix ++ operator)
            iterator operator++(int)
            {
            	iterator oldValue(*this);
            	++(*this);
                return oldValue;
            }
            friend iterator operator+(const iterator& inLeft, const size_t& amount)
            {
            	iterator ret(inLeft);
            	ret.j += amount;
            	if(ret.j >= ret._length) { ret.j = ret._length;	}
            	return ret;
			}
            // >> Free Functions
            friend void swap(iterator& a, iterator& b)
            {
                std::swap(a, b);
            }
            friend std::ostream& operator<<(std::ostream& os, const iterator& it)
            {
            	os << "(" << it.j << ")" << "/(" << it._length << ")";
            	return os;
			}
	};
	// >> Iterator Access Member function (Type I)
	iterator begin(void)
	{
	    // return iterator(this);
	    return iterator( dynamic_cast<Container*>(this) );
	}
	iterator end(void)
	{
	    // return iterator(this, length());
	    return iterator( dynamic_cast<Container*>(this), length());
	}
	// >> Iterator Access Member function (Type I)
	iterator begin(void) const
	{
	    // return iterator(this);
	    return iterator( const_cast<Container*>( dynamic_cast<const Container*>(this) ) );
	}
	iterator end(void) const
	{
	    // return iterator(this, length());
	    return iterator( const_cast<Container*>( dynamic_cast<const Container*>(this) ), length());
	}
	// >> Iterator Access Free function (Type II)
	friend iterator begin(Container& xXx)
	{
	    return xXx.begin();
	}
	friend iterator end(Container& xXx)
	{
	    return xXx.end();
	}
};

// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~



#endif // SF_CONTAINER_SUPPORT_ITERATOR_H
