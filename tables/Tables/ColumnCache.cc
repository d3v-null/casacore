//# ColumnCache.cc: A caching object for a table column
//# Copyright (C) 1997
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


//# Includes
#include <casacore/tables/Tables/ColumnCache.h>


namespace casacore { //# NAMESPACE CASACORE - BEGIN

ColumnCache::ColumnCache()
: itsIncr (1)
{
    invalidate();
}


void ColumnCache::set (rownr_t startRow, rownr_t endRow, const void* dataPtr)
{
    itsStart = startRow;
    itsEnd   = endRow;
    itsData  = dataPtr;
}

} //# NAMESPACE CASACORE - END

