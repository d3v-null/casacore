//# aipsdef.h: Global initialization for special Casacore macros
//# Copyright (C) 2000,2001,2002
//# Associated Universities, Inc. Washington DC, USA.
//#
//# This library is free software; you can redistribute it and/or modify it
//# under the terms of the GNU Library General Public License as published by
//# the Free Software Foundation; either version 2 of the License, or (at your
//# option) any later version.
//#
//# This library is distributed in the hope that it will be useful, but WITHOUT
//# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
//# License for more details.
//#
//# You should have received a copy of the GNU Library General Public License
//# along with this library; if not, write to the Free Software Foundation,
//# Inc., 675 Massachusetts Ave, Cambridge, MA 02139, USA.
//#
//# Correspondence concerning AIPS++ should be addressed as follows:
//#        Internet email: casa-feedback@nrao.edu.
//#        Postal address: AIPS++ Project Office
//#                        National Radio Astronomy Observatory
//#                        520 Edgemont Road
//#                        Charlottesville, VA 22903-2475 USA

#ifndef CASA_AIPSDEF_H
#define CASA_AIPSDEF_H

#include <casacore/casa/aipstype.h>   //# needed for Bool

//# Define the Casacore global macros

//# Defined the "aips_name2" macro which is used to join two tokens.

#if defined(__STDC__) || defined(__ANSI_CPP__) || defined(__hpux)
#define aips_name2(a,b) a##b
#else
#define aips_name2(a,b) a/**/b
#endif

namespace casacore { //# NAMESPACE CASACORE - BEGIN

// If AIPS_DEBUG is not defined, then the symbol expands to (0) which in an
// if should be removed by the dead code eliminator of any optimizer; thus
// using this in your code should have no performance penalty in the normal
// case. If compiled with AIPS_DEBUG, then aips_debug is (defined to )
// a global boolean variable (so it can be turned on and off in a debugger) 
// which is initialized to True.

extern Bool aips_debug_on;

} //# NAMESPACE CASACORE - END

#if !defined(AIPS_DEBUG)
#define aips_debug (0)
#else
// The reason that we just don't make this a variable here is so that
// we can link against libraries compiled with or without AIPS_DEBUG
// without having any missing symbols.
#define aips_debug aips_debug_on
#endif

// HP/UX
#if defined(__hpux__)
#define AIPS_HPUX
#endif

// The restrict keyword is supported by some compilers only.
#if !defined(AIPS_KAICC) && !defined(AIPS_INTELCC)
#if !defined(restrict)
#define restrict
#endif
#endif

// Define the macros to stringify a preprocessor variable.
#define CASACORE_STRINGIFY(x) CASACORE_STRINGIFY_HELPER(x)
#define CASACORE_STRINGIFY_HELPER(x) #x

// A fallthrough attribute to avoid compiler warnings,
// available only from C++17 onwards
#if __cplusplus >= 201703L
#define CASACORE_FALLTHROUGH [[fallthrough]]
#elif defined(__GNUC__) && __GNUC__ >= 7
#define CASACORE_FALLTHROUGH [[gnu::fallthrough]]
#elif defined(__clang__)
#define CASACORE_FALLTHROUGH [[clang::fallthrough]]
#else
#define CASACORE_FALLTHROUGH
#endif

#endif
