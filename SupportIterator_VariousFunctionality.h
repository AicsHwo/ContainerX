#ifndef SF_CONTAINER_SUPPORT_ITERATOR__VARIOUS_FUNCTIONALITY__H
#define SF_CONTAINER_SUPPORT_ITERATOR__VARIOUS_FUNCTIONALITY__H

#include "SupportIterator.h"
#include "SupportIterator_Clear.h"
#include "SupportIterator_withOstream.h"
#include "SupportIterator_withBinaryConvertor.h"
#include "SupportIterator_withFileReadWrite.h"

// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~


template<class Container, class ElementType>
struct SupportIterator_withVariousFunctionality :	public virtual SupportIterator_withOstream< Container, ElementType >,
													public virtual SupportIterator_withClear< Container, ElementType >,
													public virtual SupportIterator_withBinaryConvertor< Container, ElementType >,
													public virtual SupportIterator_withFileReadWrite< Container, ElementType >
{
	//	-	-	-	-	--	-	-	--	-	-	-	-	-		-	--	-	-	-	-	-	-	-
	//	K E E P    E M P T Y    H E R E
	//	-	-	-	-	--	-	-	--	-	-	-	-	-		-	--	-	-	-	-	-	-	-
	//	Using "public inheritance" to sum up functionalities,
	//	while parent class shall do "public virtual inheritance" to resolve the diamond problem.
	//	-	-	-	-	--	-	-	--	-	-	-	-	-		-	--	-	-	-	-	-	-	-
};

// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~

#endif // SF_CONTAINER_SUPPORT_ITERATOR__VARIOUS_FUNCTIONALITY__H
