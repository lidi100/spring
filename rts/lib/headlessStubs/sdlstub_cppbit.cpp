/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

/*
 * This wraps a couple of useful boost c++ time functions,
 * for use in sdlstub
 * (which is written in C, and can not easily access C++ stuff directly)
 */

#include "boost/thread.hpp"

#ifdef __cplusplus
extern "C" {
#endif

#if (BOOST_VERSION >= 105000) //boost 1.50 renamed TIME_UTC to TIME_UTC_
	#define SPRING_UTCTIME boost::TIME_UTC_
#else
	#define SPRING_UTCTIME boost::TIME_UTC
#endif

int stub_sdl_getSystemMilliSeconds() {

	boost::xtime t;
	boost::xtime_get(&t, SPRING_UTCTIME);
	const int milliSeconds = t.sec * 1000 + (t.nsec / 1000000);   
	return milliSeconds;
}

void stub_sdl_sleepMilliSeconds(int milliSeconds) {

	boost::xtime t;
	boost::xtime_get(&t, SPRING_UTCTIME);
	t.nsec += 1000000 * milliSeconds;
	boost::thread::sleep(t);
}

#ifdef __cplusplus
} // extern "C"
#endif

