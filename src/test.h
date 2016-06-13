#pragma once

#include <cstddef>

#define _COMPARE
#define _ACCESS

extern size_t compares;
extern size_t accesses;

#ifdef _COMPARE

#define COMP compares++;

#else

#define COMP

#endif // _COMPARE

#ifdef _ACCESS

#define ACC accesses++;

#else

#define ACC

#endif // _ACCESS
