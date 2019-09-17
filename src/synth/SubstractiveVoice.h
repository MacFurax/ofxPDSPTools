#pragma once

#include "ofxPDSP.h"

class SubstractiveVoice : public pdsp::Patchable
{
public:
	SubstractiveVoice();
	SubstractiveVoice(SubstractiveVoice& other) {}
	~SubstractiveVoice();

	// voice in and out
	pdsp::Amp			signalOut;
	pdsp::PatchNode		trigger;
	pdsp::PatchNode		pitch;

	// ------------------------------------------
	// OSC 1
	//

	// wave generators
	pdsp::VAOscillator	osc1;
	pdsp::Amp			osc1SineLevel;
	pdsp::Amp			osc1TriangleLevel;
	pdsp::Amp			osc1SawLevel;
	pdsp::Amp			osc1PulseLevel;
	pdsp::Amp			osc1NoiseLevel;
	pdsp::WhiteNoise	osc1Noise;

	// ADSR
	pdsp::ADSR			osc1ADSR;
	pdsp::Amp			osc1ADSRAmp;

	// Detune
	pdsp::PatchNode		osc1coarseDetune;
	pdsp::PatchNode		osc1FineDetune;

	// LFO
	pdsp::LFO			osc1LFO;

	pdsp::Amp			osc1LFOSineLevel;
	pdsp::Amp			osc1LFOTriangleLevel;
	pdsp::Amp			osc1LFOSawLevel;
	pdsp::Amp			osc1LFOSquareLevel;
	pdsp::PatchNode		osc1LFOSum;

	pdsp::Amp			osc1PitchAmp;
	pdsp::Amp			osc1LevelAmp;
	pdsp::Amp			osc1PWAmp;
	

};