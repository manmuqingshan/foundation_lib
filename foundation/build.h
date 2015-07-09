/* build.h  -  Foundation library build setup  -  Public Domain  -  2013 Mattias Jansson / Rampant Pixels
 *
 * This library provides a cross-platform foundation library in C11 providing basic support data types and
 * functions to write applications and games in a platform-independent fashion. The latest source code is
 * always available at
 *
 * https://github.com/rampantpixels/foundation_lib
 *
 * This library is put in the public domain; you can redistribute it and/or modify it without any restrictions.
 *
 */

#pragma once

/*! \file build.h
\brief Build setup
\details Build setup. This header contains all the compile time build setup for the foundation library. This header
unifies the debug/release build macros across platforms, build systems and compiler and provides the following
macro idenfiers, usable with <i>\#if BUILD_[type]</i> conditionals.

<ul>
<li>BUILD_DEBUG   - Debug build
<li>BUILD_RELEASE - Release build
<li>BUILD_PROFILE - Deploy build with profiling
<li>BUILD_DEPLOY  - Deploy build
</ul>

Feature enable/disable control is made through the various <i>BUILD_ENABLE_[...]</i> preprocessor definitions declared
in this header. The value of a flag is interpreted as disabled if the value is 0, and enabled for all other values (with
1 being the normal value for enabled). These enable flags can also be set externally on compilation command lines or in
source files prior to inclusion of foundation headers. Note that some affect if source code is compiled in or discarded
in the library, so it is recommended to set all values inside this header.

There are also a number of <i>BUILD_SIZE_[...]</i> defines for preallocated buffer sizes used. These definitions have
to be made inside this header since they are only used in the library source code and not affecting external code.
Refer to each definition for the meaning and default value. */

#include <foundation/platform.h>

#ifdef FOUNDATION_PLATFORM_DOXYGEN

/*! \brief Debug build flag
Set to 1 for debug build, 0 otherwise. Debug builds are by default unoptimized with full debugging
functionality enabled such as asserts, logging, memory tracking and other features. */
#  define BUILD_DEBUG 1

/*! \brief Release build flag
Set to 1 for release build, 0 otherwise. Release builds are by default optimized but with a normal
set of debugging functionality enabled such as asserts, some logging and memory tracking. */
#  define BUILD_RELEASE 1

/*! \brief Profile build flag
Set to 1 for profile build, 0 otherwise. Profile builds are by default fully optimized and all
debugging functionality disabled, but with profiling calls enabled. */
#  define BUILD_PROFILE 1

/*! \brief Deploy build flag
Set to 1 for deploy build, 0 otherwise. Deploy builds are by default fully optimized and have
all debugging and profiling functionality disabled. */
#  define BUILD_DEPLOY 1

/*! \brief Assert control
Control if runtime asserts are enabled. Default value is enabled in debug and release builds,
and disabled in profile and deploy builds. If asserts are disabled, all assert macros will reduce
to void (no evaluated code). See assert.h documentation for more information on asserts. */
#  define BUILD_ENABLE_ASSERT 1

/*! \brief Error context control
Control if error context tracking is enabled. Default value is enabled in debug and release
builds, and disabled in profile and deploy builds. If error context tracking is disabled, all
calls to set error context will reduce to void (no evaluated code). See error.h documentation
for more information on error context tracking. */
#  define BUILD_ENABLE_ERROR_CONTEXT 1

/*! \brief Log control
Control if logging is enabled. Default value is enabled in debug and release builds on all
platforms, disabled in profile and deploy builds on console/mobile platform families, and
enabled in profile and deploy builds on all other platforms. If logging is disabled, all
calls to log functions will reduce to void (no evaluated code). See log.h documentation for
more information on log functions. */
#  define BUILD_ENABLE_LOG 1

/*! \brief Debug log control
Control if debug logging is enabled. Similar to BUILD_ENABLE_LOG, but explicitly controls
debug level logging. Default value is enabled in debug builds, and disabled in all other
builds. Depends on BUILD_ENABLE_LOG */
#  define BUILD_ENABLE_DEBUG_LOG 1

/*! \brief Config debug control
Control if extra debug logging is enabled in the config module. Default is disabled in all builds. */
#  define BUILD_ENABLE_CONFIG_DEBUG 1

/*! \brief Profile control
Control if profiling is enabled. Default value is enabled in debug, release and profile
builds, and disabled in deploy builds. If profiling is disabled, all calls to profile
functions will reduce to void (no evaluated code). See profile.h documentation for more
information on profiling calls. */
#  define BUILD_ENABLE_PROFILE 1

/*! \brief Memory context control
Control is memory context tracking is enabled. Default value is enabled in debug and
release builds, and disabled in profile and deploy builds. If memory context tracking
is disabled, all calls to track memory context will reduce to void (no evaluated code).
See memory.h documentation for more information on memory context tracking. */
#  define BUILD_ENABLE_MEMORY_CONTEXT 1

/*! \brief Memory tracker control
Control if memory tracking is enabled. Default value is enabled in debug and release
builds, and disabled in profile and deploy builds. If memory tracking is enabled, each
memoruy allocation and deallocation will incur a slight overhead to track the origin of
the call and enable memory leak detection. For more information on memory tracking, check
the memory.h documentation. */
#  define BUILD_ENABLE_MEMORY_TRACKER 1

/*! \brief Memory guard control
Control if memory guarding is enabled. Default value is enabled in debug and release
builds, and disabled in profile and deploy builds. Memory guarding incurs a slight memory
overhead on each allocation, and enables over/underwrite detection on memory deallocation.
For more information on memory guarding, check the memory.h documentation. */
#  define BUILD_ENABLE_MEMORY_GUARD 1

/*! \brief Static hash debug control
Control if static string hashing debugging is enabled. Default value is enabled in debug
and release builds on desktop platforms, and disabled all other build configurations
and/or platforms. Static string hash debugging enables sanity checking in statically
hashed strings, as well as reverse lookup of string hashes. See hash.h documentation for
more information on statically hashed strings. */
#  define BUILD_ENABLE_STATIC_HASH_DEBUG 1

#endif

#ifndef BUILD_DEBUG
#  define BUILD_DEBUG                         0
#endif

#ifndef BUILD_RELEASE
#  define BUILD_RELEASE                       0
#endif

#ifndef BUILD_PROFILE
#  define BUILD_PROFILE                       0
#endif

#ifndef BUILD_DEPLOY
#  define BUILD_DEPLOY                        0
#endif

//Fallback
#if !BUILD_DEBUG && !BUILD_RELEASE && !BUILD_PROFILE && !BUILD_DEPLOY
#  if defined( NDEBUG )
#    undef  BUILD_RELEASE
#    define BUILD_RELEASE                     1
#  else
#    undef  BUILD_DEBUG
#    define BUILD_DEBUG                       1
#  endif
#endif


// Configurable choises
#ifndef BUILD_ENABLE_ASSERT
#if BUILD_DEBUG || BUILD_RELEASE
#define BUILD_ENABLE_ASSERT                   1
#else
#define BUILD_ENABLE_ASSERT                   0
#endif
#endif

#ifndef BUILD_ENABLE_ERROR_CONTEXT
#if BUILD_DEBUG || BUILD_RELEASE
#define BUILD_ENABLE_ERROR_CONTEXT            1
#else
#define BUILD_ENABLE_ERROR_CONTEXT            0
#endif
#endif

#ifndef BUILD_ENABLE_LOG
#if BUILD_DEBUG || BUILD_RELEASE
#define BUILD_ENABLE_LOG                      1
#else
#define BUILD_ENABLE_LOG                      0
#endif
#endif

#ifndef BUILD_ENABLE_DEBUG_LOG
#if BUILD_DEBUG
#define BUILD_ENABLE_DEBUG_LOG                1
#else
#define BUILD_ENABLE_DEBUG_LOG                0
#endif
#endif

#define BUILD_ENABLE_CONFIG_DEBUG             0

#ifndef BUILD_ENABLE_PROFILE
#if BUILD_DEBUG || BUILD_RELEASE || BUILD_PROFILE
#define BUILD_ENABLE_PROFILE                  1
#else
#define BUILD_ENABLE_PROFILE                  0
#endif
#endif

#ifndef BUILD_ENABLE_MEMORY_CONTEXT
#if BUILD_DEBUG || BUILD_RELEASE
#define BUILD_ENABLE_MEMORY_CONTEXT           1
#else
#define BUILD_ENABLE_MEMORY_CONTEXT           0
#endif
#endif

#ifndef BUILD_ENABLE_MEMORY_TRACKER
#if BUILD_DEBUG || BUILD_RELEASE
#define BUILD_ENABLE_MEMORY_TRACKER           1
#else
#define BUILD_ENABLE_MEMORY_TRACKER           0
#endif
#endif

#ifndef BUILD_ENABLE_MEMORY_GUARD
#if BUILD_DEBUG || BUILD_RELEASE
#define BUILD_ENABLE_MEMORY_GUARD             1
#else
#define BUILD_ENABLE_MEMORY_GUARD             0
#endif
#endif

#ifndef BUILD_ENABLE_STATIC_HASH_DEBUG
#if ( BUILD_DEBUG || BUILD_RELEASE ) && FOUNDATION_PLATFORM_FAMILY_DESKTOP
#define BUILD_ENABLE_STATIC_HASH_DEBUG        1
#else
#define BUILD_ENABLE_STATIC_HASH_DEBUG        0
#endif
#endif

#if FOUNDATION_PLATFORM_IOS || FOUNDATION_PLATFORM_ANDROID || FOUNDATION_PLATFORM_PNACL || FOUNDATION_PLATFORM_TIZEN
#  undef  BUILD_MONOLITHIC
#  define BUILD_MONOLITHIC                    1
#elif !defined( BUILD_MONOLITHIC )
#  define BUILD_MONOLITHIC                    0
#endif

/*! \brief Default stream byte order
The default stream byte order used if the byte order is not explicitly set on a stream.
Default value is little endian, matching most supported architectures. */
#define BUILD_DEFAULT_STREAM_BYTEORDER        BYTEORDER_LITTLEENDIAN

/*! \brief Maximum length of a path string
The maximum length of a stream path string. Used to limit temporary memory usage. */
#define BUILD_MAX_PATHLEN                     512

