#pragma once

#include "ofxPDSPTools.h"

class VESingleOSC : public VoiceElement
{
public:
	VESingleOSC();
	~VESingleOSC();
private:

	pdsp::VAOscillator	osc;
	pdsp::Amp			adsrAmp;
	pdsp::ADSR			adsr;
};
