#include "SubstractiveSynth.h"

SubstractiveSynth::SubstractiveSynth()
{
	// add inputs/outputs
	addModuleInput("level", outSignal.in_mod());

	addModuleInput("filter.cutoff", filter.in_cutoff());
	addModuleInput("filter.reso", filter.in_reso());
	addModuleInput("filter.LFO.Freq", filterLFO.in_freq());
	addModuleInput("filter.LFO.Shape", filterLFOOut.in_select());
	addModuleInput("filter.LFO.Level", filterLFOLevel.in_mod());

	addModuleOutput("signal", outSignal);

	// ---------------------------------------------------
	// patch
	//
	// voice[] >> filter >> outSignale
	// filterLFO >> filter.in_cutoff
	//

	// ---------------------------------------------------
	// patch filter 
	//

	//// LFO wave forms selector
	//filterLFOOut.resize(4);
	//filterLFO.out_sine() >> filterLFOOut.input(0);
	//filterLFO.out_triangle() >> filterLFOOut.input(1);
	//filterLFO.out_saw() >> filterLFOOut.input(2);
	//filterLFO.out_square() >> filterLFOOut.input(3);

	////// selected LFO waveform out >> LFO level >> filter cutoff
	////// level should be provided in pitch between 0 and 180 ( 1 aquale a note)
	//filterLFOOut >> filterLFOLevel >> filter.in_cutoff();

	//// filter output to main synth output amp
	filter >> outSignal;

}

SubstractiveSynth::~SubstractiveSynth()
{
}

float SubstractiveSynth::meterOutput()
{
	return outSignal.meter_output();
}

void SubstractiveSynth::setVoiceCount(int voiceCount)
{
	voices.resize(voiceCount);
}

vector<SubstractiveVoice>& SubstractiveSynth::getVoices()
{
	return voices;
}

void SubstractiveSynth::patchVoicesToSynth()
{
	for (auto& voice : voices)
	{
		voice >> filter;
	}
	
}
