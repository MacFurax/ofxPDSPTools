#include "SubstractiveVoice.h"

SubstractiveVoice::SubstractiveVoice()
{
	addModuleInput("trigger", trigger); // first = default
	addModuleInput("pitch", pitch);
	addModuleInput("level", signalOut.in_mod());
	addModuleInput("pulseWidth", osc1.in_pw());

	addModuleOutput("signal", signalOut); // first = default

	//
	// Patch
	//

	// OSC  1
	//
	// Patch output to ADSR node
	//
	pitch + osc1coarseDetune  + osc1FineDetune >> osc1.in_pitch();
	osc1.out_sine() >> osc1SineLevel;
	osc1.out_triangle() >> osc1TriangleLevel;
	osc1.out_saw() >> osc1SawLevel;
	osc1.out_pulse() >> osc1PulseLevel;
	osc1Noise >> osc1NoiseLevel;
	
	osc1SineLevel >> osc1ADSRAmp;
	osc1TriangleLevel >> osc1ADSRAmp;
	osc1SawLevel >> osc1ADSRAmp;
	osc1PulseLevel >> osc1ADSRAmp;
	osc1NoiseLevel >> osc1ADSRAmp;

	// ADSR
	//
	trigger >> osc1ADSR.in_trig();
	osc1ADSR >> osc1ADSRAmp.in_mod();
	osc1ADSRAmp >> signalOut;

	// LFO
	//
	osc1LFO.out_sine() >> osc1LFOSineLevel;
	osc1LFO.out_triangle() >> osc1LFOTriangleLevel;
	osc1LFO.out_saw() >> osc1LFOSawLevel;
	osc1LFO.out_square() >> osc1LFOSquareLevel;

	osc1LFOSineLevel >> osc1LFOSum;
	osc1LFOTriangleLevel >> osc1LFOSum;
	osc1LFOSawLevel >> osc1LFOSum;
	osc1LFOSquareLevel >> osc1LFOSum;

	osc1LFOSum >> osc1PitchAmp;
	osc1LFOSum >> osc1LevelAmp;
	osc1LFOSum >> osc1PWAmp;

	osc1PitchAmp >> osc1.in_pitch();
	osc1LevelAmp >> signalOut.in_mod();
	osc1PWAmp >> osc1.in_pw();

	// OSC  2
	//
	osc2 >> signalOut;
	trigger >> osc2.in("trigger");
	pitch >> osc2.in("pitch");


}

SubstractiveVoice::~SubstractiveVoice()
{
}


