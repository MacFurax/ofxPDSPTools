#include "SynthBase.h"

SynthBase::SynthBase()
{
	ofLogNotice() << "SynthBase::SynthBase";
	addModuleInput("level", outSignal.in_mod()); // first = default
	addModuleInput("modulation", modulation); // first = default

	addModuleOutput("signal", outSignal); // first = default
}

SynthBase::~SynthBase()
{
}

std::vector<VoiceBase*> SynthBase::getVoices()
{
	return voices;
}

void SynthBase::addVoice(VoiceBase* voice)
{
	voices.push_back(voice);
	modulation >> voice->in_modulation();
	voice->out_signal() >> outSignal;
}
