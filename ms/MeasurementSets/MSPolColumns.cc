//# MSPolarizationColumns.cc:  provides easy access to MeasurementSet columns
//# Copyright (C) 1999,2000
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

#include <casacore/ms/MeasurementSets/MSPolColumns.h>
#include <casacore/ms/MeasurementSets/MSPolarization.h>
#include <casacore/casa/Arrays/ArrayLogical.h>
#include <casacore/casa/Arrays/Matrix.h>
#include <casacore/casa/Arrays/Vector.h>
#include <casacore/casa/Exceptions/Error.h>
#include <casacore/casa/Utilities/Assert.h>
#include <casacore/casa/BasicSL/String.h>

namespace casacore { //# NAMESPACE CASACORE - BEGIN

MSPolarizationColumns::MSPolarizationColumns()
{
}

MSPolarizationColumns::
MSPolarizationColumns(const MSPolarization& msPolarization)
{
  attach(msPolarization);
}

MSPolarizationColumns::~MSPolarizationColumns() {}

void MSPolarizationColumns::
attach(const MSPolarization& msPolarization)
{
  corrProduct_p.attach(msPolarization, MSPolarization::
		       columnName(MSPolarization::CORR_PRODUCT));
  corrType_p.attach(msPolarization, MSPolarization::
		    columnName(MSPolarization::CORR_TYPE));
  flagRow_p.attach(msPolarization, MSPolarization::
		   columnName(MSPolarization::FLAG_ROW));
  numCorr_p.attach(msPolarization, MSPolarization::
		   columnName(MSPolarization::NUM_CORR));
}

Int64 MSPolarizationColumns::
match(const Vector<Stokes::StokesTypes>& polType, Int64 tryRow) {
  rownr_t r = nrow();
  if (r == 0) return -1;
  // Convert the corrType to Integers.
  const Int nCorr = polType.nelements();
  Vector<Int> polInt(nCorr);
  for (Int p = 0; p < nCorr; p++) {
    polInt(p) = polType(p);
  }
  // Main matching loop
  if (tryRow >= 0) {
    const rownr_t tr = tryRow;
    if (tr >= r) {
      throw(AipsError("MSPolarszationColumns::match(...) - "
                      "row " + String::toString(tr) +
                      " you suggest is too big"));
    }
    if (!flagRow()(tr) &&
	numCorr()(tr) == nCorr && 
	matchCorrType(tr, polInt)) {
      return tr;
    }
    if (tr == r-1) r--;
  }
  while (r > 0) {
    r--;
    if (!flagRow()(r) &&
	numCorr()(r) == nCorr && 
	matchCorrType(r, polInt)) {
      return r;
    }
  }
  return -1;
}

Bool MSPolarizationColumns::
matchCorrType(rownr_t row, const Vector<Int>& polType) const {
  DebugAssert(row < nrow(), AipsError);
  return allEQ(corrType()(row), polType);
}

Bool MSPolarizationColumns::
matchCorrProduct(rownr_t row, const Matrix<Int>& polProduct) const {
  DebugAssert(row < nrow(), AipsError);
    // The static cast is a work around for an SGI compiler Bug
  return allEQ(corrProduct()(row), static_cast< const Matrix<Int> &>(polProduct));
}

} //# NAMESPACE CASACORE - END
