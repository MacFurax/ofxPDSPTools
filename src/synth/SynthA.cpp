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
		VEOscADSRFilter* ve = new VEOscADSRFilter();
		VoiceBase* vb = new VoiceBase(i);
		vb->addElement(ve);
		vb->out_signal() >> outSignal;
		addVoice(vb);
	}

}
