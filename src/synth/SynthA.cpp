#include "SynthA.h"

SynthA::SynthA()
{
	

}

SynthA::~SynthA()
{
}

void SynthA::setup(int voiceCount)
{
	for (int i = 0; i < voiceCount; i++)
	{
		VESingleOSC* voice = new VESingleOSC();
		44.f + i*10.f >> voice->in_pitch();
		voice->signal() >> outSignal;
		ves.push_back(voice);
	}
}
