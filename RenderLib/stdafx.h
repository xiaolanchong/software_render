// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <vector>
#include <list>
#include <algorithm>
#include <string>
#include <map>
#include <memory>
#include <exception>
#include <stdexcept>
#include <cstdint>
#include <future>
#include <optional>

#define _USE_MATH_DEFINES
#include <math.h>

#include <assert.h>

#include "math/MathUtils.h"

#ifdef _DEBUG
#define verify(x) assert(x)
#else
#define verify(x)  (x)
#endif

#endif //PCH_H
