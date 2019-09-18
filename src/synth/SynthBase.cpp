#include "SynthBase.h"

SynthBase::SynthBase()
{
	addModuleInput("level", outSignal.in_mod()); // first = default

	addModuleOutput("signal", outSignal); // first = default
}

SynthBase::~SynthBase()
{
}

void SynthBase::addVoice(std::shared_ptr<VoiceBase> voice)
{
	voices.push_back(voice);
	*(voice) >> outSignal;
}
