#include "VEOscADSRFilter.h"

VEOscADSRFilter::VEOscADSRFilter()
{
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

	in("trigger") >> oscADSR.in_trig();
	in("trigger") >> filterADSR.in_trig();
	in("pitch") + detune + fine >> osc.in_pitch();

	filter >> out("signal");

	//
	// patch wave form generator
	//

	osc.out_sine() >> sineLevel;
	1.0f >> sineLevel.in_mod();
	osc.out_triangle() >> triangleLevel;
	0.0f >> triangleLevel.in_mod();
	osc.out_saw() >> sawLevel;
	0.0f >> sawLevel.in_mod();
	osc.out_pulse() >> pulseLevel;
	0.0f >> pulseLevel.in_mod();
	noise >> noiseLevel;
	0.0f >> noiseLevel.in_mod();

	sineLevel >> wavesSum;
	triangleLevel >> wavesSum;
	sawLevel >> wavesSum;
	pulseLevel >> wavesSum;
	noiseLevel >> wavesSum;

	wavesSum >> oscADSR >> filter;

	//
	// patch ADSR filter
	//
	
	filterType >> filter.in_mode();
	filterADSR >> cutoffLevel >> filter.in_cutoff();
}

VEOscADSRFilter::~VEOscADSRFilter()
{
}
