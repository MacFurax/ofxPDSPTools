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

	addModuleInput("lfo.freq", lfo.in_freq());
	addModuleInput("lfo.sine", lfoSineLevel.in_mod());
	addModuleInput("lfo.triangle", lfoTriangleLevel.in_mod());
	addModuleInput("lfo.saw", lfoSawLevel.in_mod());
	addModuleInput("lfo.square", lfoSquareLevel.in_mod());

	addModuleInput("lfo.toPitch", lfoToPitch.in_mod());
	addModuleInput("lfo.toLevel", lfoToLevel.in_mod());
	addModuleInput("lfo.toPw", lfoToPw.in_mod());
	addModuleInput("lfo.toCutOff", filter.in_cutoff());

	//TODO add filter and lfo to wave form amp


	//
	// patch trigger, pitch and signal
	//

	trigger >> oscADSR.in_trig();

	pitch + detune + fine >> osc.in_pitch();

	oscADSR >> oscADSRAmp.in_mod();
	oscADSRAmp >> outSignal;

	//
	// patch wave form generator
	//

	osc.out_sine() >> sineLevel >> oscADSRAmp;
	//1.0f >> sineLevel.in_mod();
	osc.out_triangle() >> triangleLevel >> oscADSRAmp;
	//0.0f >> triangleLevel.in_mod();
	osc.out_saw() >> sawLevel >> oscADSRAmp;
	//0.0f >> sawLevel.in_mod();
	osc.out_pulse() >> pulseLevel >> oscADSRAmp;
	//0.0f >> pulseLevel.in_mod();
	noise >> noiseLevel >> oscADSRAmp;
	//0.0f >> noiseLevel.in_mod();

	/*sineLevel >> wavesSum;
	triangleLevel >> wavesSum;
	sawLevel >> wavesSum;
	pulseLevel >> wavesSum;
	noiseLevel >> wavesSum;

	wavesSum >> oscADSRAmp;*/


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
