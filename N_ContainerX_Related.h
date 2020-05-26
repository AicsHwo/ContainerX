#ifndef N_CONTAINER_RELATED_FUNCTIONS_H
#define N_CONTAINER_RELATED_FUNCTIONS_H

#include <vector>
#include "CompileTimeOptions.h"
#include "Range.h"
#include "X.h"

namespace N_ContainerXRelated
{
	inline X<Range, 1> split(const Range& inR, const std::vector<size_t>& inSplit)
	{
		assert(inR.dimension() == inSplit.size());
		
		size_t volume(1);
		std::vector<size_t> period;
		Range step(ceilDiv(inR.toLength(), inSplit));
		DBG( std::cout << "step = " << step << std::endl; )
		Range zone(ceilDiv(inR.alignZero(), inSplit));
		DBG( std::cout << "zone = " << zone << std::endl; )
		Range start(inR.toStartPoint()+zone);
		DBG( std::cout << "start = " << start << std::endl; )
		for(auto const& it : inSplit)
		{
			period.push_back(volume);
			volume *= it;
			DBG( std::cout << it << "->" << volume << std::endl; )
		}
		X<Range, 1> partitions( volume );
		size_t _dim_( inR.length() );
		for(auto& it : partitions)
		{
			it.resize( _dim_ );
		}
		auto changeSubRange = [&](const size_t& idx)
		{
			const size_t	_reset_period_( inSplit[idx] );
			const size_t	_incr_period_( period[idx] );
			const size_t	_total_( partitions.length() );
			const Range1D	_start_( start[idx] ), _step_( step[idx] );
			const Range1D	_boundary_( inR[idx] );
			const Range1D	_separate_( {0, 1} );
			DBG( std::cout << "Range " << idx << "{ period{reset,incr}, start, step } = "; )
			DBG( std::cout << _reset_period_ << ", " << _incr_period_ << ", " << _start_ << ", " << _step_ << std::endl; )
			for(size_t i = 0, incr = 0; i < _total_; i += _incr_period_, incr++)
			{
				incr %= _reset_period_;
				//Range1D _separate_ = (incr % _reset_period_)? Range1D{1, 0} : Range1D{0, 0};
				for(size_t j = 0; j < _incr_period_; j++)
				{
					partitions[i+j][idx] = bound( _start_ + _step_ * incr - _separate_, _boundary_ );
				}
			}
		};
		for(size_t idx = 0; idx < _dim_; idx++)
		{
			changeSubRange( idx );
		}
		
		DBG( std::cout << "Partition = " << partitions << std::endl; )
		return partitions;
	}
}



#endif // N_CONTAINER_RELATED_FUNCTIONS_H
