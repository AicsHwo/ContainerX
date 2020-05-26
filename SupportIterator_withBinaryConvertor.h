#ifndef SF_CONTAINER_SUPPORT_ITERATOR__BINARY_CONVERTOR__H
#define SF_CONTAINER_SUPPORT_ITERATOR__BINARY_CONVERTOR__H

#include "SupportIterator.h"

// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~

template<class C>
size_t size(const C& in)
{
	// [!] Provide member function C::size(void), while POD-type must do template specialization
	// return in.size();
	// [!] Provide friend function size(C) to override, while new types shall properly specialize this global function
	return sizeof(in);
}

template<class Container, class ElementType>
struct SupportIterator_withBinaryConvertor :  public virtual SupportIterator< Container, ElementType >
{
	// This framework requires
	// (+). SupportIterator provide length()
	// (+). SupportIterator provide begin() and end()
	// (-). ElementType provide friend function size()
	// because the use of std::copy.
		
	// >> Friend Function
	friend std::unique_ptr<ElementType[]> Con2Bin(const SupportIterator_withBinaryConvertor& out)
	{
		std::unique_ptr<ElementType[]> dest(new ElementType[out.length()]);
		std::copy( out.begin(), out.end(), dest.get() );
		FURTHUR_DBG_MSG( for(int i = 0; i < out.length(); i++){	std::cout << dest[i] << std::endl;	} )
		return std::move(dest);
	}
	// >> Member Function
	void readBin(const ElementType* ptr)
	{
		// [!] Caller must ensure the size match length().
		std::copy( ptr, ptr + this->length(), this->begin() );
	}
	void readBin(const std::unique_ptr<ElementType[]>& ptr)
	{
		// [!] Caller must ensure the size match length().
		readBin( ptr.get() );
	}
};

// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~


#endif // SF_CONTAINER_SUPPORT_ITERATOR__BINARY_CONVERTOR__H
