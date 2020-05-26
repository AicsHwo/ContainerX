#ifndef SF_CONTAINER_SUPPORT_ITERATOR__CLEAR__H
#define SF_CONTAINER_SUPPORT_ITERATOR__CLEAR__H

#include "SupportIterator.h"

// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~

template<class Container, class ElementType>
struct SupportIterator_withClear :  public virtual SupportIterator< Container, ElementType >
{
	// >> Member Function : Clear ALL
	virtual void clearAll(void)
	{
		for(auto& it : *this)
		{
			it = ElementType{};
		}
	}
};

// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~

#endif // SF_CONTAINER_SUPPORT_ITERATOR__CLEAR__H
