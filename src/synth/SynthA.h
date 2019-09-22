#pragma once

#include "ofxPDSPTools.h"
#include "VEOscADSRFilter.h"
#include "VESingleOSC.h"

class SynthA : public SynthBase
{
public:
	SynthA();
	~SynthA();

	void setup(int voiceCount);

	vector<VoiceElement*> ves;

private:

	

};
