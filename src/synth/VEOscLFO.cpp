#include "VEOscLFO.h"

VEOscLFO::VEOscLFO()
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

	//
	// patch trigger, pitch and signal
	//

	in("trigger") >> oscADSR.in_trig();

	in("pitch") + detune + fine >> osc.in_pitch();

	oscADSR >> out("signal");

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

	wavesSum >> oscADSR;

	//
	// LFO
	//

	lfo.out_sine() >> lfoSineLevel >> lfoWavesSum;
	lfo.out_triangle() >> lfoTriangleLevel >> lfoWavesSum;
	lfo.out_saw() >> lfoSawLevel >> lfoWavesSum;
	lfo.out_square() >> lfoSquareLevel >> lfoWavesSum;

	lfoWavesSum >> lfoToPitch >> detune;
	lfoWavesSum >> lfoToLevel >> outSignal.in_mod();
	lfoWavesSum >> lfoToPw >> osc.in_pw();
}

VEOscLFO::~VEOscLFO()
{
}
