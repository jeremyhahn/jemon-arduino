//--------------------------------------------------------------------------------------
// Mains AC Non-Invasive Energy Monitor (2 channel)
// Last revision 27th Oct 2010
// Licence: GNU GPL
// By Trystan Lea (updated to support two channel energy monitoring by Glyn Hudson)
// Modified by Jeremy Hahn for JEMon project
//--------------------------------------------------------------------------------------

#ifndef JEMONCHANNEL_H
#define JEMONCHANNEL_H

#include "Arduino.h"

class JEMonChannel {

  private: // Variable declaration for emon_calc procedure
    int lastSampleV,sampleV; //sample_ holds the raw analog read value, lastSample_ holds the last sample_
    int lastSampleI,sampleI;

    double lastFilteredV,filteredV; //Filtered_ is the raw analog value minus the DC offset
    double lastFilteredI, filteredI;
    
    double phaseShiftedV; //Holds the calibrated phase shifted voltage.
    
    double sqV,sumV,sqI,sumI,instP,sumP; //sq = squared, sum = Sum, inst = instantaneous
    
    int startV; //Instantaneous voltage at start of sample window.
    
    boolean lastVCross, checkVCross; //Used to measure number of times threshold is crossed.
    int crossCount; // ''
    
    unsigned long lwhtime, whtime; //used to calculate energy used.

    // Constructor arguments
    int _wavelengths, _inPinV, _emon_timeout;
    double _VCAL, _PHASECAL;

  public:
    JEMonChannel(int wavelengths, int inPinV, double VCAL, double PHASECAL, int emon_timeout);
    void emon_calc(int,double); // create pulse function
    double realPower, //Output variables
       apparentPower,
       powerFactor,
       Vrms,
       Irms,
       whInc,
       wh;

};

#endif
