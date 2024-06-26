//# MSMainColumns.cc: Easy access to MeasurementSet main table columns
//# Copyright (C) 2000
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

#include <casacore/ms/MeasurementSets/MSMainColumns.h>
#include <casacore/ms/MeasurementSets/MeasurementSet.h>
#include <casacore/tables/Tables/ColDescSet.h>
#include <casacore/tables/Tables/TableDesc.h>
#include <casacore/tables/Tables/TableRecord.h>
#include <casacore/casa/BasicSL/String.h>
#include <casacore/casa/Arrays/Vector.h>
#include <casacore/casa/Arrays/IPosition.h>
#include <casacore/casa/Utilities/Assert.h>
#include <casacore/casa/Utilities/DataType.h>
#include <casacore/casa/Containers/RecordFieldId.h>
#include <casacore/casa/Exceptions/Error.h>

namespace casacore { //# NAMESPACE CASACORE - BEGIN

MSMainColumns::MSMainColumns()
{
}

MSMainColumns::MSMainColumns(const MeasurementSet& ms)
{
  attach(ms);
}

MSMainColumns::~MSMainColumns() {}

void MSMainColumns::attach(const MeasurementSet& ms)
{
  antenna1_p.attach(ms, MS::columnName(MS::ANTENNA1));
  antenna2_p.attach(ms, MS::columnName(MS::ANTENNA2));
  arrayId_p.attach(ms, MS::columnName(MS::ARRAY_ID));
  dataDescId_p.attach(ms, MS::columnName(MS::DATA_DESC_ID));
  exposure_p.attach(ms, MS::columnName(MS::EXPOSURE));
  feed1_p.attach(ms, MS::columnName(MS::FEED1));
  feed2_p.attach(ms, MS::columnName(MS::FEED2));
  fieldId_p.attach(ms, MS::columnName(MS::FIELD_ID));
  flag_p.attach(ms, MS::columnName(MS::FLAG));
  flagCategory_p.attach(ms, MS::columnName(MS::FLAG_CATEGORY));
  flagRow_p.attach(ms, MS::columnName(MS::FLAG_ROW));
  interval_p.attach(ms, MS::columnName(MS::INTERVAL));
  observationId_p.attach(ms, MS::columnName(MS::OBSERVATION_ID));
  processorId_p.attach(ms, MS::columnName(MS::PROCESSOR_ID));
  scanNumber_p.attach(ms, MS::columnName(MS::SCAN_NUMBER));
  sigma_p.attach(ms, MS::columnName(MS::SIGMA));
  stateId_p.attach(ms, MS::columnName(MS::STATE_ID));
  time_p.attach(ms, MS::columnName(MS::TIME));
  timeCentroid_p.attach(ms, MS::columnName(MS::TIME_CENTROID));
  uvw_p.attach(ms, MS::columnName(MS::UVW));
  weight_p.attach(ms, MS::columnName(MS::WEIGHT));
  timeMeas_p.attach(ms, MS::columnName(MS::TIME)),
  timeCentroidMeas_p.attach(ms, MS::columnName(MS::TIME_CENTROID)),
  uvwMeas_p.attach(ms, MS::columnName(MS::UVW)),
  exposureQuant_p.attach(ms, MS::columnName(MS::EXPOSURE)),
  intervalQuant_p.attach(ms, MS::columnName(MS::INTERVAL)),
  timeQuant_p.attach(ms, MS::columnName(MS::TIME)),
  timeCentroidQuant_p.attach(ms, MS::columnName(MS::TIME_CENTROID)),
  uvwQuant_p.attach(ms, MS::columnName(MS::UVW)),
  attachOptionalCols(ms);
}

void MSMainColumns::attachOptionalCols(const MeasurementSet& ms)
{
  const ColumnDescSet& cds=ms.tableDesc().columnDescSet();
  if (cds.isDefined(MS::columnName(MS::ANTENNA3))) {
    antenna3_p.attach(ms,MS::columnName(MS::ANTENNA3));
  }
  if (cds.isDefined(MS::columnName(MS::BASELINE_REF))) {
    baselineRef_p.attach(ms,MS::columnName(MS::BASELINE_REF));
  }
  if (cds.isDefined(MS::columnName(MS::DATA))) {
    data_p.attach(ms,MS::columnName(MS::DATA));
  }
  if (cds.isDefined(MS::columnName(MS::FEED3))) {
    feed3_p.attach(ms,MS::columnName(MS::FEED3));
  }
  if (cds.isDefined(MS::columnName(MS::FLOAT_DATA))) {
    floatData_p.attach(ms,MS::columnName(MS::FLOAT_DATA));
  }
  if (cds.isDefined(MS::columnName(MS::LAG_DATA))) {
    lagData_p.attach(ms,MS::columnName(MS::LAG_DATA));
  }
  if (cds.isDefined(MS::columnName(MS::PHASE_ID))) {
    phaseId_p.attach(ms,MS::columnName(MS::PHASE_ID));
  }
  if (cds.isDefined(MS::columnName(MS::PULSAR_BIN))) {
    pulsarBin_p.attach(ms,MS::columnName(MS::PULSAR_BIN));
  }
  if (cds.isDefined(MS::columnName(MS::PULSAR_GATE_ID))) {
    pulsarGateId_p.attach(ms,MS::columnName(MS::PULSAR_GATE_ID));
  }
  if (cds.isDefined(MS::columnName(MS::SIGMA_SPECTRUM))) {
    sigmaSpectrum_p.attach(ms,MS::columnName(MS::SIGMA_SPECTRUM));
  }
  if (cds.isDefined(MS::columnName(MS::TIME_EXTRA_PREC))) {
    timeExtraPrec_p.attach(ms,MS::columnName(MS::TIME_EXTRA_PREC));
    timeExtraPrecQuant_p.attach(ms,MS::columnName(MS::TIME_EXTRA_PREC));
  }
  if (cds.isDefined(MS::columnName(MS::UVW2))) {
    uvw2_p.attach(ms,MS::columnName(MS::UVW2));
    uvw2Meas_p.attach(ms,MS::columnName(MS::UVW2));
    uvw2Quant_p.attach(ms,MS::columnName(MS::UVW2));
  }
  if (cds.isDefined(MS::columnName(MS::VIDEO_POINT))) {
    videoPoint_p.attach(ms,MS::columnName(MS::VIDEO_POINT));
  }
  if (cds.isDefined(MS::columnName(MS::WEIGHT_SPECTRUM))) {
    weightSpectrum_p.attach(ms,MS::columnName(MS::WEIGHT_SPECTRUM));
  }
  if (cds.isDefined(MS::columnName(MS::CORRECTED_WEIGHT_SPECTRUM))) {
    weightSpectrumCorrected_p.attach(ms,MS::columnName(MS::CORRECTED_WEIGHT_SPECTRUM));
  }
  if (cds.isDefined(MS::columnName(MS::CORRECTED_DATA))) {
    correctedData_p.attach(ms,MS::columnName(MS::CORRECTED_DATA));
  }
  if (cds.isDefined(MS::columnName(MS::IMAGING_WEIGHT))) {
    imagingWeight_p.attach(ms,MS::columnName(MS::IMAGING_WEIGHT));
  }
  if (cds.isDefined(MS::columnName(MS::MODEL_DATA))) {
    modelData_p.attach(ms,MS::columnName(MS::MODEL_DATA));
  }
}

  Vector<String> MSMainColumns::flagCategories() const {
  const TableRecord& keywords = flagCategory().keywordSet();
  const RecordFieldId key("CATEGORY");
  DebugAssert(keywords.isDefined(key.fieldName()), AipsError);
  DebugAssert(keywords.dataType(key) == TpArrayString, AipsError);
  DebugAssert(keywords.shape(key).nelements() == 1, AipsError);
  DebugAssert(nrow() == 0 || 
 	      keywords.shape(key)(0) == flagCategory().shape(0)(2), AipsError);
  return Vector<String>(keywords.asArrayString(key));
}

void MSMainColumns::setFlagCategories(const Vector<String>& categories) {
  TableRecord& keywords = flagCategory().rwKeywordSet();
  const RecordFieldId key("CATEGORY");
  DebugAssert(nrow() == 0 || 
 	      categories.nelements() == 
	      static_cast<uInt>(flagCategory().shape(0)(2)), AipsError);
  keywords.define(key, categories);
}

void MSMainColumns::setEpochRef(MEpoch::Types ref, Bool tableMustBeEmpty) {
  timeMeas_p.setDescRefCode(ref, tableMustBeEmpty);
  timeCentroidMeas_p.setDescRefCode(ref, tableMustBeEmpty);
}

void MSMainColumns::setUVWRef(Muvw::Types ref)
{
  uvwMeas_p.setDescRefCode(ref);
  if (!uvw2_p.isNull()) {
    uvw2Meas_p.setDescRefCode(ref);
  }
}

} //# NAMESPACE CASACORE - END

