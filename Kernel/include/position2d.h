//-------------------------------------------------------
//@file: position2d.h
//@brief: position2d
//@author: venus
//@date: 2018/12/07-17:58
//-------------------------------------------------------
#ifndef __POSITION_H_INCLUDED__
#define __POSITION_H_INCLUDED__

#include "vector2d.h"

namespace venus
{
	namespace core
	{

		// Use typedefs where possible as they are more explicit...

		//! \deprecated position2d is now a synonym for vector2d, but vector2d should be used directly.
		typedef vector2d<f32> position2df;

		//! \deprecated position2d is now a synonym for vector2d, but vector2d should be used directly.
		typedef vector2d<s32> position2di;
	} // namespace core
} // namespace venus

// ...and use a #define to catch the rest, for (e.g.) position2d<f64>
#define position2d vector2d

#endif // __POSITION_H_INCLUDED__

