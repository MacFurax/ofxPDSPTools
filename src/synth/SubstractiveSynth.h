#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "SubstractiveVoice.h"

class SubstractiveSynth : public pdsp::Patchable
{
public:
	SubstractiveSynth();
	~SubstractiveSynth();

	float meterOutput();
	void setVoiceCount(int voiceCount);
	vector<SubstractiveVoice>&	getVoices();
	void patchVoicesToSynth();


	//
	// class variables
	//
	vector<SubstractiveVoice>	voices;


	//
	// ofxPDSP variables
	// 

	// output level of the synth
	pdsp::Amp           outSignal;

	// after voices synth filter
	pdsp::SVFilter		filter;
	pdsp::LFO			filterLFO;
	pdsp::Switch		filterLFOOut;
	pdsp::Amp			filterLFOLevel;

};
