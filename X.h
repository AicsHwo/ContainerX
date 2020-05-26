#ifndef CONTAINER_X_H
#define CONTAINER_X_H

#include <iostream>
#include <cassert>
#include <memory>				// std::unique_ptr<T>
#include <initializer_list>		// std::initializer_list<T>
#include <vector>				// std::vector<T>
#include <cmath>				// std::floor()

#include "CompileTimeOptions.h"
#include "SupportIndexProtection.h"
#include "SupportIterator.h"
#include "SupportIterator_VariousFunctionality.h"

#include "Range.h"
#include "Initializer.h"


template<class T, size_t dim>
class X : public SupportIndexingProtection, public SupportIterator_withVariousFunctionality< X<T,dim>, T >
{
	// [!] Dimension Specification from High to Low
	// [!] class T requirements:
	//	   1. Provide Default Constructor for new T[size] use.
	
	protected:
		std::unique_ptr< X<T, dim-1>[] > lowerDims;
		
		friend class X<T, dim+1>;
		void allocation(const size_t& curDim)
		{
			assert( curDim );
			updLength( curDim );
			lowerDims.reset(new X<T, dim-1>[curDim]);
			DBG( std::cout << " X<T, "<< dim << "> : " << curDim << std::endl; )
		}
		void allocation(const std::vector<size_t>& inDims)
		{
			assert( inDims.size() );
			allocation(inDims[0]);
			
			size_t leftDims = inDims.size()-1;
			if( leftDims )
			{
				std::vector<size_t> subDims(inDims.size()-1);
				std::copy(inDims.begin()+1, inDims.end(), subDims.begin());
				for( size_t i = 0; i < lengthOfCurDim(); i++ )
				{
					lowerDims[i].allocation( subDims );
				}
			}
		}
		void copyWithReallocation(const X& inCopy)
		{
			allocation(inCopy.lengthOfCurDim());
			DBG( std::cout << " X<T,> : "<< inCopy << " : " << inCopy.lengthOfCurDim() << std::endl; )
			for( size_t i = 0; i < lengthOfCurDim(); i++ )
			{
				lowerDims[i].copyWithReallocation( inCopy(i) );
			}
		}
		void copyRange(const X& inCopy, const Range& inRange)
		{
			bool destSpaceCheck	= (lengthOfCurDim() == inRange[0].length());
			bool srcSpaceCheck	= (inCopy.lengthOfCurDim() > inRange[0].end);
			assert( destSpaceCheck && srcSpaceCheck );
			for( size_t dest_i = 0, src_i = inRange[0].start ; dest_i < lengthOfCurDim(); dest_i++, src_i++ )
			{
				lowerDims[dest_i].copyRange( inCopy(src_i), inRange.subDimension() );
			}
		}
	public:
		// >> Default Constructor
		explicit X():lowerDims(nullptr){}
		// >> Constructor
		explicit X(const std::vector<size_t>& inDims, const initializer<T>& values = {})
		{
			// [!] If new T[] can call constructor with argument rather than default, 
			//     the whole recursive scheme can be avoided.
			allocation( inDims );
			if(!values.isEmpty())
			{
				size_t i{};
				for(auto& it : *this)
				{
					it = values[i++];
				}
			}
		}
		// >> Copy Constructor
		X(const X& inCopy)
		{
			copyWithReallocation( inCopy );
		}
		/*
		// >> Conversion Constructor
		template<class T2>
		explicit X(const X<T2, dim>& inConv)
		{
			copyWithReallocation( (X<T, dim>)inConv );
		}*/
		
		// >> Operator Overloading : assignment
		X& operator=(const X& inAssign)
		{
			// [!] Currently propagation is NOT supported
			assert(length() == inAssign.length());
			auto to(this->begin()), from(inAssign.begin());
			for(size_t i = 0; i < length(); i++)
			{
				(*to) = (*from);
				to++;
				from++;
			}
			return *this;
		}
		
		// >> Type-cast
		template<class T2>
		explicit operator X<T2, dim>() const
		{
			DBG( std::cout << "Type-casting :" << std::endl; )
			X<T2, dim> tmp( hyperCube() );
			typename SupportIterator< X<T2,dim>, T2 >::iterator to(tmp.begin());
			typename SupportIterator< X<T,dim>, T >::iterator from(this->begin());
			DBG( std::cout << "iterator to : " << to << std::endl; )
			DBG( std::cout << "iterator from : " << from << std::endl; ) 
			for(size_t i = 0; i < length(); i++)
			{
				(*to) = (T2)(*from);
				DBG( std::cout << (*from) << "->" << (*to) << std::endl; )
				to++;
				from++;
				// DBG( std::cout << "iterator to : " << to << std::endl; )
				// DBG( std::cout << "iterator from : " << from << std::endl; ) 
			}
			return tmp;
		}
		
		// >> Support Compile-Time indexing using Functor, e.g. X<int,2> x({1,2}); x(0)(1) = 2;
		X<T, dim-1>& operator()(const size_t& sel)
		{
			assert(lowerDims != nullptr);
			return lowerDims[ validIdx(sel) ];
		}
		// >> Duplicate of function operator
		const X<T, dim-1>& operator()(const size_t& sel) const
		{
			assert(lowerDims != nullptr);
			return lowerDims[ validIdx(sel) ];
		}
		// >> Support Compile-Time indexing using Variadic Template e.g. X<int,2> x({1,2}); x(0, 1) = 2;
		template<class... Args>
		T& operator()(const size_t& idx1, Args&&... restIdx)
		{
			// DBG : std::cout << idx1 << std::endl;
			return operator()(idx1)(std::forward<Args>(restIdx)...);
		}
		
		// >> Support Run-Time indexing
		T& operator()(const std::vector<size_t>& indices)
		{
			// [!] Can't pass vector elements to variadic function template due to 
			// FACT : vector is run-time object while variadic template is compile-time decided.
			assert(indices.size() == dim);
			return operator()(indices[0])( std::vector<size_t>(indices.begin()+1, indices.end()) );
		}
		
		// >> Fetch Subset
		X<T, dim> operator()(const Range& inSection) const
		{
			X<T, dim> tmp(inSection.hyperCube());
			tmp.copyRange(*this, inSection);
			return tmp;
		}
		
		// >> Support Feature : Iterator
		inline size_t innerLength(void) const
		{
			assert(lowerDims != nullptr);
			return lowerDims[0].length();
		}
		virtual size_t length(void) const
		{
			return _length * innerLength();
		}
		T& operator[](const size_t& inJ)
		{
			size_t curIdx = std::floor(inJ / innerLength());
			size_t idxLeft = std::floor(inJ % innerLength());
			FURTHUR_DBG_MSG( std::cout << inJ << ", " << innerLength() << ", " << curIdx << ", " << idxLeft << std::endl; )
			assert(curIdx >= 0);
			return lowerDims[curIdx][idxLeft];
		}
		// >> Duplicate of subscript operator
		const T& operator[](const size_t& inJ) const
		{
			size_t curIdx = std::floor(inJ / innerLength());
			size_t idxLeft = std::floor(inJ % innerLength());
			FURTHUR_DBG_MSG( std::cout << inJ << ", " << innerLength() << ", " << curIdx << ", " << idxLeft << std::endl; )
			assert(curIdx >= 0);
			return lowerDims[curIdx][idxLeft];
		}
		
		// >> Support Range information
		Range range(void) const
		{
			Range r({{0, lengthOfCurDim()-1}});
			r.append(lowerDims[0].range());
			return r;
		}
		
		// >> Report Dimension
		std::vector<size_t> hyperCube(void) const
		{
			std::vector<size_t> tmp{lengthOfCurDim()};
			std::vector<size_t> dims_below( lowerDims[0].hyperCube() );
			tmp.insert(tmp.end(), dims_below.begin(), dims_below.end());
			return tmp;
		}
		
		// >> (...)
};

template<class T>
class X<T, 1> : public SupportIndexingProtection, public SupportIterator_withVariousFunctionality< X<T,1>, T >
{
	protected:
		std::unique_ptr< T[] > data = nullptr;
		
		friend class X<T, 2>;
		void allocation(const size_t& curDim)
		{
			assert( curDim );
			updLength( curDim );
			data.reset(new T[curDim]);
			DBG( std::cout << " X<T, 1> : " << curDim << std::endl; )
		}
		void allocation(const std::vector<size_t>& inDims)
		{
			assert( inDims.size() == 1 );
			allocation(inDims[0]);
		}
		void copyWithReallocation(const X& inCopy)
		{
			allocation(inCopy.lengthOfCurDim());
			std::copy(inCopy.begin(), inCopy.end(), this->begin());
		}
		void copyWithSizeCheck(const X& inCopy)
		{
			assert( lengthOfCurDim() == inCopy.lengthOfCurDim());
			std::copy(inCopy.begin(), inCopy.end(), this->begin());
		}
		void copyRange(const X& inCopy, const Range& inRange)
		{
			bool destSpaceCheck	= (lengthOfCurDim() == inRange[0].length());
			bool srcSpaceCheck	= (inCopy.lengthOfCurDim() > inRange[0].end);
			assert( destSpaceCheck && srcSpaceCheck );
			DBG( std::cout << inRange[0].length() << std::endl; )
			std::copy(inCopy.begin()+inRange[0].start, inCopy.begin()+inRange[0].end+1, this->begin());
			DBG( std::cout << "done" << std::endl; )
		}
	public:
		explicit X() = default;
		explicit X(const size_t& inDims, const initializer<T>& values = {})
		{
			// [!] If new T[] can call constructor with argument rather than default, 
			//     the whole recursive scheme can be avoided.
			allocation( inDims );
			if(!values.isEmpty())
			{
				size_t i{};
				for(auto& it : *this)
				{
					it = values[i++];
				}
			}
		}
		// >> Copy Constructor
		X(const X& inCopy)
		{
			copyWithReallocation( inCopy );
		}
		
		// >> Operator Overloading : assignment
		X& operator=(const X& inAssign)
		{
			// [!] Currently propagation is NOT supported
			assert(length() == inAssign.length());
			auto to(this->begin()), from(inAssign.begin());
			for(size_t i = 0; i < length(); i++)
			{
				(*to) = (*from);
				to++;
				from++;
			}
			return *this;
		}
		
		// >> Type-cast
		template<class T2>
		explicit operator X<T2, 1>() const
		{
			X<T2, 1> tmp( hyperCube() );
			auto to(tmp.begin());
			auto from(this->begin());
			for(size_t i = 0; i < length(); i++)
			{
				(*to) = (T2)(*from);
				to++;
				from++;
			}
			return tmp;
		}
		
		// >> Support Compile-Time indexing using Functor
		T& operator()(const size_t& sel)
		{
			assert(data != nullptr);
			return data[ validIdx(sel) ];
		}
		
		// >> Support Run-Time indexing
		T& operator()(const std::vector<size_t>& indices)
		{
			// [!] Can't pass vector elements to variadic function template due to 
			// FACT : vector is run-time object while variadic template is compile-time decided.
			assert(indices.size() == 1);
			return operator()(indices[0]);
		}
		
		// >> Fetch Subset
		X<T, 1> operator()(const Range& inSection) const
		{
			X<T, 1> tmp(inSection[0].length());
			tmp.copyRange(*this, inSection);
			return tmp;
		}
		
		
		// >> Support Feature : Iterator
		virtual size_t length(void) const
		{
			//return _length;
			return lengthOfCurDim();
		}
		T& operator[](const size_t& inJ)
		{
			return operator()(inJ);
		}
		// >> Duplicate of subscript operator
		const T& operator[](const size_t& inJ) const
		{
			return operator()(inJ);
		}
		
		// >> Support Range information
		Range range(void) const
		{
			return Range({{0, lengthOfCurDim()-1}});
		}
		
		// >> Report Dimension
		std::vector<size_t> hyperCube(void) const
		{
			return std::vector<size_t>{lengthOfCurDim()};
		}
		
		// >> (...)
};


// Using Alias Template :
template<class T>
using X1 = X<T, 1>;
template<class T>
using X2 = X<T, 2>;

#include "X_NonMemberOperatorOverloads.h"
#include "N_ContainerX_Related.h"
#include "N_ContainerX_CommonOps.h"

#endif // CONTAINER_X_H
