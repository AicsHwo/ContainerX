#ifndef SF_SUPPORT_INDEX_PROTECTION_H
#define SF_SUPPORT_INDEX_PROTECTION_H

// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~


class SupportIndexingProtection
{
	protected:
		size_t _length = 0;
		inline void updLength(const size_t& newLength)
		{
			_length = newLength;
		}
		inline const size_t& lengthOfCurDim(void) const
		{
			return _length;
		}
		inline size_t validIdx(const size_t& inIdx) const
		{
			return (inIdx < 0) ? 0 : (inIdx >= _length) ? _length-1 : inIdx;
		}
};

// - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~ - ~

#endif // SF_SUPPORT_INDEX_PROTECTION_H
