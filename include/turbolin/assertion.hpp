#pragma once

#include <iostream>

#ifdef WIN32
	#include <intrin.h>
#elifdef __linux__
	#include <signal.h>
#elifdef __APPLE__
	#include <signal.h>
#endif


#define __TL_LOG_ASSERT_MESSAGE(expr, msg) std::cout << "Assertion in " __FILE__ ":" << __LINE__ << " '" #expr "' failed : " msg << std::endl


#ifdef WIN32
	#define __TL_ASSERT_DEBUG_BREAKPOINT __debugbreak() 
#elifdef __linux__
	#define __TL_ASSERT_DEBUG_BREAKPOINT raise(SIGTRAP) 
#elifdef __APPLE__
	#define __TL_ASSERT_DEBUG_BREAKPOINT raise(SIGTRAP)
#else
	#define No platform selected (or selected platform is not supported by turbolin)
#endif


#define __TL_ASSERT_IMPLEMENTATION(expr, msg) if (!!(expr)) {} else {__TL_LOG_ASSERT_MESSAGE(expr, msg); __TL_ASSERT_DEBUG_BREAKPOINT;}


#ifdef TL_RELEASE
	#define TL_SLOW_ASSERT(expr, msg)
	#define TL_ASSERT(expr, msg) __TL_ASSERT_IMPLEMENTATION(expr, msg)
#elifdef TL_DEBUG
	#define TL_SLOW_ASSERT(expr, msg) __TL_ASSERT_IMPLEMENTATION(expr, msg)
	#define TL_ASSERT(expr, msg) __TL_ASSERT_IMPLEMENTATION(expr, msg)
#else
	#error No build configuration selected
#endif

