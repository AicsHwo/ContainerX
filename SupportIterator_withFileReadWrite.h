#ifndef SF_CONTAINER_SUPPORT_ITERATOR__FILE_READ_WRITE__H
#define SF_CONTAINER_SUPPORT_ITERATOR__FILE_READ_WRITE__H

#include <fstream>				// std::ifstream, std::ofstream

#include "SupportIterator.h"

// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~

template<class Container, class ElementType>
struct SupportIterator_withFileReadWrite :  public virtual SupportIterator_withBinaryConvertor< Container, ElementType >
{
	// This framework requires
	// (+). SupportIterator provide length()
	// (+). SupportIterator provide begin() and end()
	// (+). ElementType provide friend function size()
	
	// >> Member Function : Read / Write Byte
	virtual bool read(const std::string& inPath)
	{
		std::ifstream inFile;
		auto fileSize = [&](void) -> size_t
		{
			inFile.seekg(0, inFile.end);
			size_t bLength = inFile.tellg();
			inFile.seekg(0, inFile.beg);
			return bLength;
		};
		inFile.open(inPath, std::ifstream::binary);
		if(inFile.good())
		{
			size_t bfSize = fileSize();
			size_t inLength = bfSize / size(ElementType{});
			// [!] Caller must ensure that the container has exactly the same size.
			assert( inLength == this->length() );
			std::unique_ptr<ElementType[]> tmp(new ElementType[inLength]);
			inFile.read( (char*)tmp.get(), bfSize);
			inFile.close();
			this->readBin( tmp );
			return true;
		}
		return false;
	}
	virtual bool write(const std::string& outPath)
	{
		std::ofstream outFile;
		outFile.open(outPath, std::ofstream::binary);
		if(outFile.good())
		{
			size_t bfSize = this->length() * size(ElementType{});
			std::unique_ptr<ElementType[]> tmp( std::move( Con2Bin( *this ) ) );
			outFile.write( (char*)tmp.get(), bfSize);
			outFile.close();
		}
		return false;
	}
	
};

// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~

#endif // SF_CONTAINER_SUPPORT_ITERATOR__FILE_READ_WRITE__H
