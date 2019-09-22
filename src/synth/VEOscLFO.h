#pragma once

#include "ofxPDSPTools.h"


class VEOscLFO : public VoiceElement
{
public:
	VEOscLFO();
	~VEOscLFO();
private:

	// wave forms generator with ADSR
	pdsp::VAOscillator	osc;
	pdsp::WhiteNoise	noise;

	pdsp::PatchNode		detune; // coarse detune -12 to 12
	pdsp::PatchNode		fine; // fine detune -1 to 1

	pdsp::Amp			sineLevel;
	pdsp::Amp			triangleLevel;
	pdsp::Amp			sawLevel;
	pdsp::Amp			pulseLevel;
	pdsp::Amp			noiseLevel;

	pdsp::Amp			wavesSum;

	pdsp::Amp			pulseWidth;

	pdsp::ADSR			oscADSR;

	// LFO
	pdsp::LFO			lfo;
	
	pdsp::Amp			lfoSineLevel;
	pdsp::Amp			lfoTriangleLevel;
	pdsp::Amp			lfoSawLevel;
	pdsp::Amp			lfoSquareLevel;

	pdsp::PatchNode		lfoWavesSum;

	pdsp::Amp			lfoToPitch;
	pdsp::Amp			lfoToLevel;
	pdsp::Amp			lfoToPw;


};