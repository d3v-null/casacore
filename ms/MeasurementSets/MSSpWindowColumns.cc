//# MSSpWindowColumns.cc:  provides easy access to MeasurementSet columns
//# Copyright (C) 1996,1999,2000,2002
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

#include <casacore/ms/MeasurementSets/MSSpWindowColumns.h>
#include <casacore/casa/Arrays/ArrayLogical.h>
#include <casacore/casa/Arrays/IPosition.h>
#include <casacore/casa/Arrays/Vector.h>
#include <casacore/casa/Exceptions/Error.h>
#include <casacore/casa/BasicMath/Math.h>
#include <casacore/ms/MeasurementSets/MSSpectralWindow.h>
#include <casacore/measures/Measures/MeasRef.h>
#include <casacore/measures/Measures/MFrequency.h>
#include <casacore/measures/Measures/MeasConvert.h>
#include <casacore/measures/Measures/MDirection.h>
#include <casacore/measures/Measures/MRadialVelocity.h>
#include <casacore/measures/Measures/MEpoch.h>
#include <casacore/measures/Measures/MPosition.h>
#include <casacore/measures/Measures/MeasRef.h>
#include <casacore/casa/Quanta/MVFrequency.h>
#include <casacore/casa/Quanta/MVDirection.h>
#include <casacore/casa/Quanta/MVEpoch.h>
#include <casacore/casa/Quanta/MVFrequency.h>
#include <casacore/casa/Quanta/MVPosition.h>
#include <casacore/casa/Quanta/Quantum.h>
#include <casacore/casa/Quanta/UnitVal.h>
#include <casacore/tables/Tables/ColDescSet.h>
#include <casacore/tables/Tables/TableDesc.h>
#include <casacore/casa/Utilities/Assert.h>

namespace casacore { //# NAMESPACE CASACORE - BEGIN

MSSpWindowColumns::MSSpWindowColumns()
{
}

MSSpWindowColumns::MSSpWindowColumns(const MSSpectralWindow& msSpWindow)
{
  attach(msSpWindow);
}

MSSpWindowColumns::~MSSpWindowColumns() {}

void MSSpWindowColumns::attach(const MSSpectralWindow& msSpWindow)
{
  chanFreq_p.attach(msSpWindow, MSSpectralWindow::
		    columnName(MSSpectralWindow::CHAN_FREQ));
  chanWidth_p.attach(msSpWindow, MSSpectralWindow::
		     columnName(MSSpectralWindow::CHAN_WIDTH));
  effectiveBW_p.attach(msSpWindow, MSSpectralWindow::
		       columnName(MSSpectralWindow::EFFECTIVE_BW));
  flagRow_p.attach(msSpWindow, MSSpectralWindow::
		   columnName(MSSpectralWindow::FLAG_ROW));
  freqGroup_p.attach(msSpWindow, MSSpectralWindow::
		     columnName(MSSpectralWindow::FREQ_GROUP));
  freqGroupName_p.attach(msSpWindow, MSSpectralWindow::
			 columnName(MSSpectralWindow::FREQ_GROUP_NAME));
  ifConvChain_p.attach(msSpWindow, MSSpectralWindow::
		       columnName(MSSpectralWindow::IF_CONV_CHAIN));
  measFreqRef_p.attach(msSpWindow, MSSpectralWindow::
		       columnName(MSSpectralWindow::MEAS_FREQ_REF));
  name_p.attach(msSpWindow, MSSpectralWindow::
		columnName(MSSpectralWindow::NAME));
  netSideband_p.attach(msSpWindow, MSSpectralWindow::
		       columnName(MSSpectralWindow::NET_SIDEBAND));
  numChan_p.attach(msSpWindow, MSSpectralWindow::
		   columnName(MSSpectralWindow::NUM_CHAN));
  refFrequency_p.attach(msSpWindow, MSSpectralWindow::
			columnName(MSSpectralWindow::REF_FREQUENCY));
  resolution_p.attach(msSpWindow, MSSpectralWindow::
		      columnName(MSSpectralWindow::RESOLUTION));
  totalBandwidth_p.attach(msSpWindow, MSSpectralWindow::
			  columnName(MSSpectralWindow::TOTAL_BANDWIDTH));
  chanFreqMeas_p.attach(msSpWindow, MSSpectralWindow::
			columnName(MSSpectralWindow::CHAN_FREQ));
  refFrequencyMeas_p.attach(msSpWindow, MSSpectralWindow::
			    columnName(MSSpectralWindow::REF_FREQUENCY));
  chanFreqQuant_p.attach(msSpWindow, MSSpectralWindow::
			 columnName(MSSpectralWindow::CHAN_FREQ));
  chanWidthQuant_p.attach(msSpWindow, MSSpectralWindow::
			  columnName(MSSpectralWindow::CHAN_WIDTH));
  effectiveBWQuant_p.attach(msSpWindow, MSSpectralWindow::
			    columnName(MSSpectralWindow::EFFECTIVE_BW));
  refFrequencyQuant_p.attach(msSpWindow, MSSpectralWindow::
			     columnName(MSSpectralWindow::REF_FREQUENCY));
  resolutionQuant_p.attach(msSpWindow, MSSpectralWindow::
			   columnName(MSSpectralWindow::RESOLUTION));
  totalBandwidthQuant_p.attach(msSpWindow, MSSpectralWindow::
			       columnName(MSSpectralWindow::TOTAL_BANDWIDTH));
  attachOptionalCols(msSpWindow);
}

void MSSpWindowColumns::
attachOptionalCols(const MSSpectralWindow& msSpWindow)
{
  const ColumnDescSet& cds=msSpWindow.tableDesc().columnDescSet();
  const String& assocNature=
    MSSpectralWindow::columnName(MSSpectralWindow::ASSOC_NATURE);
  if (cds.isDefined(assocNature)) assocNature_p.attach(msSpWindow,assocNature);
  const String& assocSpwId=
    MSSpectralWindow::columnName(MSSpectralWindow::ASSOC_SPW_ID);
  if (cds.isDefined(assocSpwId)) assocSpwId_p.attach(msSpWindow,assocSpwId);
  const String& bbcNo=
    MSSpectralWindow::columnName(MSSpectralWindow::BBC_NO);
  if (cds.isDefined(bbcNo)) bbcNo_p.attach(msSpWindow,bbcNo);
  const String& bbcSideband=
    MSSpectralWindow::columnName(MSSpectralWindow::BBC_SIDEBAND);
  if (cds.isDefined(bbcSideband)) bbcSideband_p.attach(msSpWindow,bbcSideband);
  const String& dopplerId=
    MSSpectralWindow::columnName(MSSpectralWindow::DOPPLER_ID);
  if (cds.isDefined(dopplerId)) dopplerId_p.attach(msSpWindow,dopplerId);
  const String& receiverId=
    MSSpectralWindow::columnName(MSSpectralWindow::RECEIVER_ID);
  if (cds.isDefined(receiverId)) receiverId_p.attach(msSpWindow,receiverId);
}

Int64 MSSpWindowColumns::
matchSpw(const MFrequency& refFreq, uInt nChan, 
	 const Quantum<Double>& bandwidth, Int ifChain,
	 const Quantum<Double>& tolerance, Int64 tryRow) const {
  rownr_t r = nrow();
  if (r == 0) return -1;
  // Convert the reference frequency to Hz
  const MFrequency::Types refType = 
    MFrequency::castType(refFreq.getRef().getType());
  const Double refFreqInHz = refFreq.getValue().getValue();
  // Convert the totalBandwidth to Hz
  const Unit Hz("Hz");
  DebugAssert(bandwidth.check(Hz.getValue()), AipsError);
  const Double bandwidthInHz = bandwidth.getValue(Hz);

  // Convert the tolerance to Hz
  DebugAssert(tolerance.check(Hz.getValue()), AipsError);
  const Double tolInHz = tolerance.getValue(Hz);
  // Main matching loop
  if (tryRow >= 0) {
    const rownr_t tr = tryRow;
    if (tr >= r) {
      throw(AipsError("MSSpWindowColumns::match(...) - "
                      "row " + String::toString(tr) +
                      " you suggest is too big"));
    }
    if (!flagRow()(tr) &&
	matchNumChan(tr, nChan) &&
	matchIfConvChain(tr, ifChain) &&
	//matchTotalBandwidth(tr, bandwidthInHz, nChan*tolInHz/4) &&
	matchTotalBandwidth(tr, bandwidthInHz, bandwidthInHz/4.) &&
 	matchRefFrequency(tr, refType, refFreqInHz, tolInHz)) {
		 return tr;
    }
    if (tr == r-1) r--;
  }
  while (r > 0) {
    r--;
    if (!flagRow()(r) &&
	matchNumChan(r, nChan) &&
	matchIfConvChain(r, ifChain) &&
	//matchTotalBandwidth(r, bandwidthInHz, nChan*tolInHz/4) &&
	matchTotalBandwidth(r, bandwidthInHz, bandwidthInHz/4.) &&
 	matchRefFrequency(r, refType, refFreqInHz, tolInHz)) {
      return r;
    }
  }
  return -1;
}
// this version has info of MeasFrame.
Int64 MSSpWindowColumns::
matchSpw(const MFrequency& refFreq, const MFrequency& /*chanFreq1*/, const MeasFrame& measFrm,
    const MSDopplerColumns& msdopc, const MSSourceColumns& mssrcc, uInt nChan, 
	 const Quantum<Double>& bandwidth, Int ifChain,
	 const Quantum<Double>& tolerance, Int64 tryRow) const {
  rownr_t r = nrow();
  if (r == 0) return -1;
  // Convert the totalBandwidth to Hz
  const Unit Hz("Hz");
  DebugAssert(bandwidth.check(Hz.getValue()), AipsError);
  const Double bandwidthInHz = bandwidth.getValue(Hz);
  // Convert the tolerance to Hz
  DebugAssert(tolerance.check(Hz.getValue()), AipsError);
  const Double tolInHz = tolerance.getValue(Hz);
  // Main matching loop
  if (tryRow >= 0) {
    const rownr_t tr = tryRow;
    if (tr >= r) {
      throw(AipsError("MSSpWindowColumns::match(...) - "
                      "row " + String::toString(tr) +
                      " you suggest is too big"));
    }
    if (!flagRow()(tr) &&
	      matchNumChan(tr, nChan) &&
	      matchIfConvChain(tr, ifChain) &&
  	      //matchTotalBandwidth(tr, bandwidthInHz, nChan*tolInHz/4) &&
			matchTotalBandwidth(tr, bandwidthInHz, bandwidthInHz/4.) &&
	      ( /*matchRefFreqCnvtrd(tr, chanFreq1, False, measFrm, msdopc, mssrcc, tolInHz)||*/
	      matchRefFreqCnvtrd(tr, refFreq, True, measFrm, msdopc, mssrcc, tolInHz))) {
		   return tr;
    }
    if (tr == r-1) r--;
  }
  while (r > 0) {
    r--;
    if (!flagRow()(r) &&
	      matchNumChan(r, nChan) &&
	      matchIfConvChain(r, ifChain) &&
	      //matchTotalBandwidth(r, bandwidthInHz, nChan*tolInHz/4) &&
			matchTotalBandwidth(r, bandwidthInHz, bandwidthInHz/4.) &&
	      ( /*matchRefFreqCnvtrd(r, chanFreq1, False, measFrm, msdopc, mssrcc, tolInHz)||*/
	        matchRefFreqCnvtrd(r, refFreq, True, measFrm, msdopc, mssrcc, tolInHz))) {
         return r;
    }
  }
  return -1;
}

RowNumbers MSSpWindowColumns::
allMatchedSpw(const MFrequency& refFreq, uInt nChan, 
	 const Quantum<Double>& bandwidth, Int ifChain,
	 const Quantum<Double>& tolerance) const {
  rownr_t r = nrow();
  RowNumbers matched;
  if (r == 0) return matched;
  // Convert the reference frequency to Hz
  const MFrequency::Types refType = 
    MFrequency::castType(refFreq.getRef().getType());
  const Double refFreqInHz = refFreq.getValue().getValue();
  // Convert the totalBandwidth to Hz
  const Unit Hz("Hz");
  DebugAssert(bandwidth.check(Hz.getValue()), AipsError);
  const Double bandwidthInHz = bandwidth.getValue(Hz);
  // Convert the tolerance to Hz
  DebugAssert(tolerance.check(Hz.getValue()), AipsError);
  const Double tolInHz = tolerance.getValue(Hz);


  size_t numMatch=0;
  for (rownr_t k=0; k < r; ++k){
    

    if (!flagRow()(k) &&
	matchNumChan(k, nChan) &&
	matchIfConvChain(k, ifChain) &&
	//matchTotalBandwidth(k, bandwidthInHz, nChan*tolInHz/4) &&
	matchTotalBandwidth(k, bandwidthInHz, bandwidthInHz/4.) &&
 	matchRefFrequency(k, refType, refFreqInHz, tolInHz)) {
	//matchRefFreqCnvtrd(r, refFreq, True, measFrm, msdopc, mssrcc, tolInHz))) {
      ++numMatch;
      matched.resize(numMatch, True);
      matched(numMatch-1)=k;
    }

  }

  return matched;

}


Int64 MSSpWindowColumns::
matchSpw(const MFrequency& refFreq, uInt nChan, 
	 const Quantum<Double>& bandwidth, Int ifChain,
	 const Quantum<Double>& tolerance, Vector<Double>& otherFreqs, 
	 Bool& reversed) const
{
  reversed=False;
  
  Int matchedSpw=-1;

  RowNumbers allMatchSpw=
    allMatchedSpw(refFreq, nChan, bandwidth, ifChain, tolerance);
 
  size_t nMatches=allMatchSpw.size();
  if(nMatches==0) return -1;

  // if only one channel then return the first match
  if (nChan == 1) return allMatchSpw[0];
  Double tolInHz= tolerance.get("Hz").getValue();
  for (size_t k=0; k < nMatches; ++k){

    matchedSpw=allMatchSpw[k];
      
    if(matchChanFreq(matchedSpw, otherFreqs, tolInHz)){ 
      return matchedSpw;
    }
    else{ 
      Vector<Double> reverseFreq(otherFreqs.shape());
      for (uInt f=0; f < nChan ; ++f){
	reverseFreq[f]=otherFreqs[nChan-1-f];
      }
      if(matchChanFreq(matchedSpw, reverseFreq, tolInHz)){
	reversed=True;
	return matchedSpw;
      }
    }
  }
 
  return -1;
}


Bool MSSpWindowColumns::
matchRefFrequency(rownr_t row, MFrequency::Types refType, 
		  Double refFreqInHz, Double tolInHz) const {
  DebugAssert(row < nrow(), AipsError);
  const MFrequency rowFreq = refFrequencyMeas()(row); 
  if (MFrequency::castType(rowFreq.getRef().getType()) != refType) {
    return False;
  }
  return nearAbs(rowFreq.getValue().getValue(), refFreqInHz, tolInHz);
}
Bool MSSpWindowColumns::
matchRefFreqCnvtrd(rownr_t row, MFrequency refFreq, const Bool isRefFreq, const MeasFrame& measFrm,
        const MSDopplerColumns& msdopc, const MSSourceColumns& mssrcc, Double tolInHz) const {
  // measFrm is the frame info for the current spw.
  DebugAssert(row < nrow(), AipsError);
  // Since sometimes when the channel frequency does not match, the reference frequency actually matches.
  // So we check both and so we may receive either a refrence frequency or a channel frequency.
  MFrequency rowFreq;
  if( isRefFreq ) { 
     rowFreq = refFrequencyMeas()(row);
	  //cout<< "[MSSpWindowColumns::matchRefFreqCnvtr()] match reference frequency. "<< endl;
  }else{
     rowFreq = Vector<MFrequency>(chanFreqMeas()(row))(0);
	  //cout<< "[MSSpWindowColumns::matchRefFreqCnvtr()] match first channel frequency. " << endl;
  }
  //const MFrequency refFreqCtrd;
  const MFrequency::Types refType = MFrequency::castType(refFreq.getRef().getType());
  const MFrequency::Types rowType = MFrequency::castType(rowFreq.getRef().getType());
  //cout.precision(8);
  const Double refFreqInHz = refFreq.getValue().getValue();
  const Double rowFreqInHz = rowFreq.getValue().getValue();

  Double refFreqInHzCnvtrd = refFreqInHz;
  Double rowFreqInHzCnvtrd = rowFreqInHz;
  if (rowType != refType) {
    MFrequency::Convert freqCnvtr;
	 if( rowType == MFrequency::TOPO ){ // One match for NGC7538
 	    // combined conversion
		  MeasFrame measFrmFrom = MeasFrame( *(measFrm.epoch()), *(measFrm.position()), *(measFrm.direction()));
		  //MRadialVelocity radialVelocity(MVRadialVelocity ( -59000.0 ), MRadialVelocity::Ref (MRadialVelocity::LSRK, measFrmFrom ));
        //measFrmFrom.set ( radialVelocity);
		  MFrequency::Ref refFrom( refType, measFrmFrom );
	     MeasFrame measFrmTo = MeasFrame();
	     // the info for MEpoch of the previous spw are not persisted. Hard coding it in for now.
	     measFrmTo.set( *(measFrm.position()) );
		  // get the epoch
		  uInt doppler_id = dopplerId()( row );
		  // Note what is required in operator () of ScalarColumns< Measures > is the row number of the 
		  // table. But for subtable DOPPLER, doppler_id is the same as row number. So we can use the
		  // source_id directly in the call below.
		  uInt source_id = msdopc.sourceId()(doppler_id );
		  MEpoch epochTo = mssrcc.timeMeas()( source_id );
		  // set the Epoch to that of rowFreq.
		  measFrmTo.set( epochTo );
	     measFrmTo.set( *(measFrm.direction()));
		  //measFrmTo.set( radialVelocity );
        MFrequency::Ref refTo( rowType, measFrmTo );
		  Unit unit(String("Hz"));
        MFrequency::Convert cnvtMachine(unit, refFrom, refTo);
		  MFrequency freqFromConverted = cnvtMachine( refFreq );
		  refFreqInHzCnvtrd = freqFromConverted.getValue().getValue();
	 }else if ( refType == MFrequency::TOPO ){ // One match for G192
        // combined conversion. Should produce the same results as the step by step conversion.
	     MeasFrame measFrmFrom = MeasFrame();
	     // the info for MEpoch and MDirection of the previous spw are not persisted. Hard coding it in for now.
	     measFrmFrom.set( *(measFrm.position()) );
		  // get the epoch
		  uInt doppler_id = dopplerId()( row );
		  // Note what is required in operator () of ScalarColumns< Measures > is the row number of the 
		  // table. But for subtable SOURCE, source_id is the same as row number. So we can use the
		  // source_id directly in the call below.
		  uInt source_id = msdopc.sourceId()( doppler_id );
		  MEpoch epochFrom = mssrcc.timeMeas()( source_id );
		  // get the field direction
		  MDirection fieldDirFrom = mssrcc.directionMeas()(source_id);
		  measFrmFrom.set( epochFrom );
		  measFrmFrom.set( fieldDirFrom );
		  //MRadialVelocity radialVelocity(MVRadialVelocity ( 5700.0 ), MRadialVelocity::Ref (MRadialVelocity::LSRK, measFrmFrom ));
        //measFrmFrom.set ( radialVelocity);
		  
        MFrequency::Ref refFrom( rowType, measFrmFrom );
		  MeasFrame measFrmTo = MeasFrame();
		  measFrmTo.set( *(measFrm.position()) );
		  measFrmTo.set( fieldDirFrom );
		  measFrmTo.set( *(measFrm.epoch()) );
		  //measFrmTo.set( radialVelocity );
		  // check the effects of epoch. Comment out the following line after test.
		  // measFrm.set( *(measFrmFrom.epoch())); // This does not afftect the result or maybe the effects is small.
		  MFrequency::Ref refTo( refType, measFrmTo );
		  
	     Unit unit(String("Hz"));
        MFrequency::Convert cnvtMachine(unit, refFrom, refTo);
		  // rowFreq does not have frame info in it. So add it in to see if it will affect anything.
		  // did not see any effects of this.
		  // MFrequency freqFrom = MFrequency( MVFrequency( Quantity( rowFreq.getValue().getValue(),"Hz" )),refFrom );
		  // MFrequency freqFromConverted = cnvtMachine( freqFrom );
		  MFrequency freqFromConverted = cnvtMachine( rowFreq );
		  rowFreqInHzCnvtrd = freqFromConverted.getValue().getValue();
     }else{ // none of the frequency is of type TOPO
	     MFrequency::Ref refFrom( refType, measFrm );
	     MeasFrame measFrmTo = MeasFrame();
	     measFrmTo.set( *(measFrm.position()) );
		  // get the epoch
		  uInt doppler_id = dopplerId()( row );
		  // Note what is required in operator () of ScalarColumns< Measures > is the row number of the 
		  // table. But for subtable DOPPLER, doppler_id is the same as row number. So we can use the
		  // source_id directly in the call below.
		  uInt source_id = msdopc.sourceId()(doppler_id );
		  // Note what is required in operator () of ScalarColumns< Measures > is the row number of the 
		  // table. But for subtable SOURCE, source_id is the same as row number. So we can use the
		  // source_id directly in the call below.
		  MEpoch epochTo = mssrcc.timeMeas()( source_id );
		  // set the Epoch to that of rowFreq.
	     // measFrmTo.set( MEpoch( MVEpoch( 49856, 0.391493 )));
		  measFrmTo.set( epochTo );
	     measFrmTo.set( *(measFrm.direction()));
		  //measFrmTo.set( radialVelocity );
        MFrequency::Ref refTo( rowType, measFrmTo );
	     Unit unit(String("Hz"));
        MFrequency::Convert cnvtMachine(unit, refFrom, refTo);
		  MFrequency freqFromConverted = cnvtMachine( refFreq );
		  refFreqInHzCnvtrd = freqFromConverted.getValue().getValue();	 
	 }
  }

  return nearAbs(rowFreqInHzCnvtrd, refFreqInHzCnvtrd, tolInHz);
}

Bool MSSpWindowColumns::
matchChanFreq(rownr_t row, const Vector<Double>& chanFreqInHz,
	      Double tolInHz) const {
  DebugAssert(row < nrow(), AipsError);
  DebugAssert(chanFreq().ndim(row) == 1, AipsError);
  // Check the number of channels
  const uInt nChan = chanFreq().shape(row)(0);
  if (nChan != chanFreqInHz.nelements()) return False;
  // Check the values in each channel
  return allNearAbs(chanFreq()(row), chanFreqInHz, tolInHz);
}
  
Bool MSSpWindowColumns::
matchIfConvChain(rownr_t row, Int ifChain) const {
  DebugAssert(row < nrow(), AipsError);
  return ifChain == ifConvChain()(row);
}

Bool MSSpWindowColumns::
matchTotalBandwidth(rownr_t row, Double bandwidthInHz,
		    Double tolInHz) const {
  DebugAssert(row < nrow(), AipsError);
  return nearAbs(totalBandwidth()(row), bandwidthInHz, fabs(tolInHz));
}

Bool MSSpWindowColumns::
matchNumChan(rownr_t row, Int nChan) const {
  DebugAssert(row < nrow(), AipsError);
  return nChan == numChan()(row);
}


} //# NAMESPACE CASACORE - END
