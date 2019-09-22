#include "SynthBase.h"

SynthBase::SynthBase()
{
	ofLogNotice() << "SynthBase::SynthBase";
	addModuleInput("level", outSignal.in_mod()); // first = default

	addModuleOutput("signal", outSignal); // first = default
	1.0f >> outSignal.in_mod();
}

SynthBase::~SynthBase()
{
}

std::vector<VoiceBase>& SynthBase::getVoices()
{
	return voices;
}

void SynthBase::addVoice(VoiceBase& voice)
{
	voices.push_back(voice);
	voice >> outSignal;
}
