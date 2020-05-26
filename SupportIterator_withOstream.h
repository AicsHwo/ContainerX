#ifndef SF_CONTAINER_SUPPORT_ITERATOR__OSTREAM__H
#define SF_CONTAINER_SUPPORT_ITERATOR__OSTREAM__H

#include "SupportIterator.h"


// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~

template<class Container, class ElementType>
struct SupportIterator_withOstream :  public virtual SupportIterator< Container, ElementType >
{
	// >> Friend Function : Overload operator<< of std::ostream( OUR_CLASS )
	friend std::ostream& operator<<(std::ostream& os, const SupportIterator_withOstream& out)
	{
		for(auto& it : out)
		{
			os << it << " ";
		}
		return os;
	}
};
// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~

#endif //  SF_CONTAINER_SUPPORT_ITERATOR__OSTREAM__H
