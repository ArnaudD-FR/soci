#ifndef _SOCI_CORE_SHARED_PTR
#define _SOCI_CORE_SHARED_PTR

#define SOCI_USE_SHARED_PTR(SharedPtr) namespace soci{ using SharedPtr; }

#if __cplusplus > 199711L
#include <memory>
SOCI_USE_SHARED_PTR(std::shared_ptr)
#elif HAVE_BOOST
#include <boost/shared_ptr.hpp>
SOCI_USE_SHARED_PTR(boost::shared_ptr)
#else
#include "shared_ptr_custom.h"
SOCI_USE_SHARED_PTR(details::memory::shared_ptr)
#endif

#endif // _SOCI_CORE_SHARED_PTR