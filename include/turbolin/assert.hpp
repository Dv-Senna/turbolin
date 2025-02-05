#pragma once

#include <print>

#ifdef WIN32
	#include <intrin.h>
	#define __TL_ASSERT_DEBUG_BREAKPOINT __debugbreak()
#elifdef __linux__
	#include <signal.h>
	#define __TL_ASSERT_DEBUG_BREAKPOINT raise(SIGTRAP)
#elifdef __APPLE__
	#include <signal.h>
	#define __TL_ASSERT_DEBUG_BREAKPOINT raise(SIGTRAP)
#else
	#error Your platform is not supported
#endif


#ifdef _MSC_VER
	#define __TL_ASSERT_LOG_MESSAGE(expr, msg) std::println(stderr, "Assert in " __FUNCTION__ " (" __FILE__ ":{}) '" #expr "' failed : " msg, __LINE__)
#elifdef __GNUC__
	#define __TL_ASSERT_LOG_MESSAGE(expr, msg) std::println(stderr, "Assert in " __PRETTY_FUNCTION__ " (" __FILE__ ":{}) '" #expr "' failed : " msg, __LINE__)
#else
	#error Your compiler is not supported
#endif


#define __TL_ASSERT_IMPLEMENTATION(expr, msg) if (!!(expr)) {} else {__TL_ASSERT_LOG_MESSAGE(expr, msg); __TL_ASSERT_DEBUG_BREAKPOINT;}


#if !defined(TL_RELEASE) && !defined(TL_DEBUG)
	#ifdef NDEBUG
		#define TL_RELEASE
	#else
		#define TL_DEBUG
	#endif
#endif


#ifdef TL_RELEASE
	#define TL_ASSERT(expr, msg) __TL_ASSERT_IMPLEMENTATION(expr, msg)
#elifdef TL_DEBUG
	#define TL_ASSERT(expr, msg)
#endif
