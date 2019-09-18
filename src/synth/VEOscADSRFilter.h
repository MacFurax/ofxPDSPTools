#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "VoiceElement.h"

//! VEOscADSRFilter : a VoiceElement that combine and OSC with ADSR and a filter with ADSR
/*!
	VoiceElement that combine:
		- OSC + Noise
		- control level of each wave form
		- OSC detune, fine and coarse
		- filter with ADSR control of the cutoff

	Exposed inputs:
		- detune :
		- fine :
		- sineLevel :
		- triangleLevel :
		...
*/
class VEOscADSRFilter : public VoiceElement
{
public:
	VEOscADSRFilter();
	~VEOscADSRFilter();
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
	
	// Filter with ADSR
	pdsp::SVFilter		filter;
	pdsp::PatchNode		filterType; // SVFilter mode 0.0 to 3.0
	pdsp::ADSR			filterADSR;
	pdsp::Amp			cutoffLevel; // amplitude of filter cutoff control


};
