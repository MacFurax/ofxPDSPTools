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

	pdsp::Amp			pulseWidth;

	pdsp::ADSR			oscADSR;
	pdsp::Amp			oscADSRAmp;

	// Filter
	pdsp::SVFilter		filter;
	//pdsp::PatchNode		filterType; // SVFilter mode 0.0 to 3.0

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
	pdsp::Amp			lfoToCutOff;

	pdsp::Amp			lfoToSine;
	pdsp::Amp			lfoToTriangle;
	pdsp::Amp			lfoToSaw;
	pdsp::Amp			lfoToPulse;
	pdsp::Amp			lfoToNoise;


};