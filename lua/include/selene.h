#pragma once

#if defined(_MSC_VER) && _MSC_VER < 1900 // before MSVS-14 CTP1
#define constexpr const
#endif

#include "selene/State.h"
#include "selene/Tuple.h"

/* My unique change to the library */
namespace lua = sel;