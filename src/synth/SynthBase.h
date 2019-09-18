#pragma once

#include "ofxPDSP.h"
#include "VoiceBase.h"

class SynthBase : public pdsp::Patchable
{
public:
	SynthBase();
	SynthBase(const SynthBase & other) {}
	~SynthBase();

	void addVoice(std::shared_ptr<VoiceBase> voice);

private:
	std::vector<std::shared_ptr<VoiceBase>> voices;

	pdsp::Amp outSignal;

};
