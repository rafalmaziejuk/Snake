#pragma once

#include <cassert>

#ifdef EN_DEBUG
	#define EN_ASSERT(x) assert(x)
#else
	#define EN_ASSERT(x)
#endif