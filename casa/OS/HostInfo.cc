//# HostInfo.h: Information about the host that this process is running on.
//# Copyright (C) 1997-2006
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

#define _XOPEN_SOURCE 600       //For clock_gettime

#include <casacore/casa/BasicSL/String.h>
#include <casacore/casa/OS/HostInfo.h>
#include <casacore/casa/System/Aipsrc.h>
#include <casacore/casa/Utilities/Assert.h>

#include <unistd.h>
#include <sys/utsname.h>

// Time related includes
#include <time.h>

namespace casacore { //# NAMESPACE CASACORE - BEGIN

String HostInfo::hostName()
{
    String retval;
#if defined(AIPS_IRIX)
      // This is a kludge to get around a problem with
      // losing environment variable names on some IRIX machines
      // at NCSA in Urbana IL.
    Char buf[65];
    if (gethostname(buf, 64) >= 0) {
	retval = String(buf);
    }
#else
    struct utsname name;
    if (uname(&name) >= 0) {
	retval = name.nodename;
    }
#endif
    return retval;
}

Int HostInfo::processID()
{
    return getpid();
}


Double HostInfo::secondsFrom1970()
{
  struct timespec tp;
  AlwaysAssert(clock_gettime(CLOCK_REALTIME, &tp) == 0, AipsError);
  double total = tp.tv_sec;
  total += tp.tv_nsec * 1.e-9;
  return total;
}

#define HOSTINFO_IMPLEMENT_MEMBERS				\
Int HostInfo::numCPUs(bool use_aipsrc)				\
{								\
    static const String keyword("system.resources.cores");	\
    if ( use_aipsrc ) {						\
	String value;						\
	if (resources_numCPUs > 0) {				\
		return resources_numCPUs;			\
	} else if ( Aipsrc::find(value, keyword) ) {			\
	    int result;						\
	    if ( sscanf( value.c_str( ), "%d", &result ) == 1 )	\
		return (Int) result;				\
	}							\
    }								\
								\
    if ( ! info ) info = new HostMachineInfo( );		\
    return info->valid ? info->cpus : 0;			\
}								\
								\
ptrdiff_t HostInfo::memoryTotal(bool use_aipsrc) 		\
{								\
    static const String memory("system.resources.memory");	\
    static const String fraction("system.resources.memfrac");	\
    int frac = 0;						\
    /** aipsrc memory is in megabytes whereas this **/		\
    /** returns the memory in kilobytes...         **/		\
    if ( use_aipsrc ) {						\
	String value;						\
    if (resources_memory > 0) {				\
        return resources_memory;				\
    } else if ( Aipsrc::find(value, memory) ) {		\
	    int result;						\
	    if ( sscanf( value.c_str( ), "%d", &result ) == 1 )	\
		return (ptrdiff_t) result * 1024;		\
    } else if (resources_memfrac > 0) {			\
        frac = resources_memfrac;				\
    } else if ( Aipsrc::find(value,	fraction) ) {		\
	    int result;						\
	    if ( sscanf( value.c_str( ), "%d", &result ) == 1 )	\
		frac = result;					\
	}							\
    }								\
								\
    if ( ! info ) info = new HostMachineInfo( );		\
								\
    if ( ! info->valid )					\
	return -1;						\
    else if ( frac == 0 )					\
	return info->memory_total;				\
    else {							\
	double f = ((double) frac / 100.0);			\
	return (ptrdiff_t) ((double ) info->memory_total * f);	\
    }								\
}								\
								\
ptrdiff_t HostInfo::memoryUsed( )				\
{								\
    if ( ! info ) info = new HostMachineInfo( );		\
    info->update_info( );					\
    return info->valid ? info->memory_used : -1;		\
}								\
								\
ptrdiff_t HostInfo::memoryFree( )				\
{								\
    if ( ! info ) info = new HostMachineInfo( );		\
    info->update_info( );					\
    return info->valid ? info->memory_free : -1;		\
}								\
								\
ptrdiff_t HostInfo::swapTotal( )				\
{								\
    if ( ! info ) info = new HostMachineInfo( );		\
    info->update_info( );					\
    return info->valid ? info->swap_total : -1;			\
}								\
								\
ptrdiff_t HostInfo::swapUsed( )					\
{								\
    if ( ! info ) info = new HostMachineInfo( );		\
    info->update_info( );					\
    return info->valid ? info->swap_used : -1;			\
}								\
								\
ptrdiff_t HostInfo::swapFree( )					\
{								\
    if ( ! info ) info = new HostMachineInfo( );		\
    info->update_info( );					\
    return info->valid ? info->swap_free : -1;			\
}								\
								\
ptrdiff_t HostInfo::setMemoryTotal(ptrdiff_t memory)		\
{								\
    ptrdiff_t old_memory = resources_memory;			\
    resources_memory = 1024*memory;				\
    return old_memory;						\
}								\
								\
Int HostInfo::setMemoryFraction(Int memfrac)			\
{								\
    Int old_memfrac = resources_memfrac;			\
    resources_memfrac = memfrac;				\
    return old_memfrac;					\
}								\
Int HostInfo::setNumCPUs(Int numCPUs)				\
{								\
    Int old_numCPUs = resources_numCPUs;			\
    resources_numCPUs = numCPUs;				\
    return old_numCPUs;					\
}


} //# NAMESPACE CASACORE - END

#define HOSTINFO_DO_IMPLEMENT
#if defined(AIPS_LINUX)
#include <casacore/casa/OS/HostInfoLinux.h>
namespace casacore { //# NAMESPACE CASACORE - BEGIN

HOSTINFO_IMPLEMENT_MEMBERS
} //# NAMESPACE CASACORE - END

#elif defined(AIPS_SOLARIS)
#include <casacore/casa/OS/HostInfoSolaris.h>
namespace casacore { //# NAMESPACE CASACORE - BEGIN

HOSTINFO_IMPLEMENT_MEMBERS
} //# NAMESPACE CASACORE - END

#elif defined(AIPS_IRIX)
#include <casacore/casa/OS/HostInfoIrix.h>
HOSTINFO_IMPLEMENT_MEMBERS
} //# NAMESPACE CASACORE - END

#elif defined(AIPS_OSF)
#include <casacore/casa/OS/HostInfoOsf1.h>
namespace casacore { //# NAMESPACE CASACORE - BEGIN

HOSTINFO_IMPLEMENT_MEMBERS
} //# NAMESPACE CASACORE - END

#elif defined(AIPS_HPUX)
#include <casacore/casa/OS/HostInfoHpux.h>
namespace casacore { //# NAMESPACE CASACORE - BEGIN

HOSTINFO_IMPLEMENT_MEMBERS
} //# NAMESPACE CASACORE - END

#elif defined(__APPLE__)
#include <casacore/casa/OS/HostInfoDarwin.h>
namespace casacore { //# NAMESPACE CASACORE - BEGIN

HOSTINFO_IMPLEMENT_MEMBERS
} //# NAMESPACE CASACORE - END

#elif defined(AIPS_BSD)
#include <casacore/casa/OS/HostInfoBsd.h>
namespace casacore { //# NAMESPACE CASACORE - BEGIN

HOSTINFO_IMPLEMENT_MEMBERS
} //# NAMESPACE CASACORE - END

#else
namespace casacore { //# NAMESPACE CASACORE - BEGIN

Int HostInfo::numCPUs(bool) { return 0; }
ptrdiff_t HostInfo::memoryTotal(bool) { return -1; }
ptrdiff_t HostInfo::memoryUsed( )  { return -1; }
ptrdiff_t HostInfo::memoryFree( )  { return -1; }
ptrdiff_t HostInfo::swapTotal( )   { return -1; }
ptrdiff_t HostInfo::swapUsed( )    { return -1; }
ptrdiff_t HostInfo::swapFree( )    { return -1; }

} //# NAMESPACE CASACORE - END

#endif

namespace casacore { //# NAMESPACE CASACORE - BEGIN

HostMachineInfo *HostInfo::info = 0;
ptrdiff_t HostInfo::resources_memory = 0;
Int HostInfo::resources_memfrac = 0;
Int HostInfo::resources_numCPUs = 0;

} //# NAMESPACE CASACORE - END
