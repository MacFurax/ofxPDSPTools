#pragma once

#include "ofxPDSPTools.h"
#include "VEOscADSRFilter.h"
#include "VESingleOSC.h"
#include "VEOscLFO.h"

class SynthA : public SynthBase
{
public:
	SynthA();
	~SynthA();

	void setup(int voiceCount);

	vector<VoiceElement*> ves;

private:

	pdsp::SVFilter	filter;
	pdsp::LFO		filterLFO;
	pdsp::Switch	filterLFOType;
	pdsp::Amp		lfoToCutOff;

};
