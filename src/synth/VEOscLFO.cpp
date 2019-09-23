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

	addModuleInput("filter.type", filter.in_mode());
	addModuleInput("filter.cutoff", filter.in_cutoff());
	addModuleInput("filter.reso", filter.in_reso());

	addModuleInput("lfo.freq", lfo.in_freq());
	addModuleInput("lfo.sine", lfoSineLevel.in_mod());
	addModuleInput("lfo.triangle", lfoTriangleLevel.in_mod());
	addModuleInput("lfo.saw", lfoSawLevel.in_mod());
	addModuleInput("lfo.square", lfoSquareLevel.in_mod());

	addModuleInput("lfo.toPitch", lfoToPitch.in_mod());
	addModuleInput("lfo.toLevel", lfoToLevel.in_mod());
	addModuleInput("lfo.toPw", lfoToPw.in_mod());
	addModuleInput("lfo.toCutOff", lfoToCutOff.in_mod());
	
	addModuleInput("lfo.toSine", lfoToSine.in_mod());
	addModuleInput("lfo.toTriangle", lfoToTriangle.in_mod());
	addModuleInput("lfo.toSaw", lfoToSaw.in_mod());
	addModuleInput("lfo.toPulse", lfoToPulse.in_mod());
	addModuleInput("lfo.toNoise", lfoToNoise.in_mod());

	


	//
	// patch trigger, pitch and signal
	//

	trigger >> oscADSR.in_trig();

	pitch + detune + fine >> osc.in_pitch();

	oscADSR >> oscADSRAmp.in_mod();
	oscADSRAmp >> filter >> outSignal;

	//
	// patch wave form generator
	//

	osc.out_sine() >> sineLevel >> oscADSRAmp;
	osc.out_triangle() >> triangleLevel >> oscADSRAmp;
	osc.out_saw() >> sawLevel >> oscADSRAmp;
	osc.out_pulse() >> pulseLevel >> oscADSRAmp;
	noise >> noiseLevel >> oscADSRAmp;

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
	lfoWavesSum >> lfoToCutOff >> filter.in_cutoff();

	lfoWavesSum >> lfoToSine >> sineLevel.in_mod();
	lfoWavesSum >> lfoToTriangle >> triangleLevel.in_mod();
	lfoWavesSum >> lfoToSaw >> sawLevel.in_mod();
	lfoWavesSum >> lfoToPulse >> pulseLevel.in_mod();
	lfoWavesSum >> lfoToNoise >> noiseLevel.in_mod();
}

VEOscLFO::~VEOscLFO()
{
}
