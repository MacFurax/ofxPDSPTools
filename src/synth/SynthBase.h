#pragma once

#include "ofxPDSP.h"
#include "VoiceBase.h"

class SynthBase : public pdsp::Patchable
{
public:
	SynthBase();
	SynthBase(const SynthBase & other) {}
	~SynthBase();

	void virtual setup(int voiceCount) {}

	std::vector<VoiceBase*> getVoices();

protected:
	
	void addVoice(VoiceBase* voice);

	std::vector<VoiceBase*> voices;

	pdsp::Amp outSignal;

};
