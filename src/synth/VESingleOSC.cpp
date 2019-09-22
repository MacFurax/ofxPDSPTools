#include "VESingleOSC.h"

VESingleOSC::VESingleOSC() 
{
	trigger >> adsr.in_trig();
	pitch >> osc.in_pitch();

	10.f >> adsr.in_attack();
	200.f >> adsr.in_decay();
	0.8f >> adsr.in_sustain();
	500.f >> adsr.in_release();

	adsr >> adsrAmp.in_mod();

	osc.out_pulse() >> adsrAmp >> outSignal;
}

VESingleOSC::~VESingleOSC()
{
}
