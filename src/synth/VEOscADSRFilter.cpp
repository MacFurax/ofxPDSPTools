#include "VEOscADSRFilter.h"

VEOscADSRFilter::VEOscADSRFilter()
{
	ofLogNotice() << "VEOscADSRFilter::VEOscADSRFilter";

	//
	// export in/out
	//

	// for wave form generator
	addModuleInput("detune", detune);
	addModuleInput("fine", fine);

	addModuleInput("sineLevel", sineLevel.in_mod());
	addModuleInput("triangleLevel", triangleLevel.in_mod());
	addModuleInput("sawLevel", sawLevel.in_mod());
	addModuleInput("pulseLevel", pulseLevel.in_mod());
	addModuleInput("noiseLevel", noiseLevel.in_mod());

	addModuleInput("pulseWidth", osc.in_pw());

	addModuleInput("attack", oscADSR.in_attack());
	addModuleInput("decay", oscADSR.in_decay());
	addModuleInput("sustain", oscADSR.in_sustain());
	addModuleInput("release", oscADSR.in_release());

	//for filter ADSR

	addModuleInput("filter.cutoff", filter.in_cutoff());
	addModuleInput("filter.reso", filter.in_reso());

	addModuleInput("filter.attack", filterADSR.in_attack());
	addModuleInput("filter.decay", filterADSR.in_decay());
	addModuleInput("filter.sustain", filterADSR.in_sustain());
	addModuleInput("filter.release", filterADSR.in_release());

	addModuleInput("filter.level", cutoffLevel);

	//
	// patch trigger, pitch and signal
	//

	trigger >> oscADSR.in_trig();
	trigger >> filterADSR.in_trig();
	pitch + detune + fine >> osc.in_pitch();

	oscADSR >> oscADSRAmp.in_mod();
	oscADSRAmp >> outSignal;

	osc.out_sine() >> sineLevel >> oscADSRAmp;
	osc.out_triangle() >> triangleLevel >> oscADSRAmp;
	osc.out_saw() >> sawLevel >> oscADSRAmp;
	osc.out_pulse() >> pulseLevel >> oscADSRAmp;
	noise >> noiseLevel >> oscADSRAmp;
}

VEOscADSRFilter::~VEOscADSRFilter()
{
}
