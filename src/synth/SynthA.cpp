#include "SynthA.h"

SynthA::SynthA()
{
	addModuleInput("filter.type", filter.in_mode());
	addModuleInput("filter.cutoff", filter.in_cutoff());
	addModuleInput("filter.reso", filter.in_reso());

	addModuleInput("filter.lfo.type", filterLFOType.in_select());
	addModuleInput("filter.lfo.freq", filterLFO.in_freq());
	addModuleInput("filter.lfo.cutoff", lfoToCutOff.in_mod());

	addModuleInput("filter.modulation.reso", modulationToReso.in_mod());
	addModuleInput("filter.modulation.lfo freq", modulationToLFOFreq.in_mod());

	modulationToReso.set(0.0f);
	modulationToLFOFreq.set(0.0f);

	// Patch
	filterLFOType.resize(4);

	filterLFO.out_sine() >> filterLFOType.input(0);
	filterLFO.out_triangle() >> filterLFOType.input(1);
	filterLFO.out_saw() >> filterLFOType.input(2);
	filterLFO.out_square() >> filterLFOType.input(3);

	filterLFOType >> lfoToCutOff >> filter.in_cutoff();

	modulation >> modulationToReso >> filter.in_reso();
	modulation >> modulationToLFOFreq >> filterLFO.in_freq();
}

SynthA::~SynthA()
{
}

void SynthA::setup(int voiceCount)
{
	for (int i = 0; i < voiceCount; i++)
	{
		VEOscADSRFilter* ve = new VEOscADSRFilter();
		VEOscLFO* ve2 = new VEOscLFO();
		VoiceBase* vb = new VoiceBase(i);
		vb->addElement(ve);
		vb->addElement(ve2);
		vb->out_signal() >> filter >> outSignal;
		addVoice(vb);
	}

}
