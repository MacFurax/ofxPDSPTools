#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "VoiceElement.h"

//! VoiceBase, define a Voice in a SynthBase
/*!
 VoiceBase is the base class to compose voices of a Synth.
 VoiceBase are composed of one or more VoiceElement(s).

 Provide following default in/out 
 - (in) trigger : trigger this Voice (default)
 - (in) pitch : set Voice pitch
 - (in) level : set Voice output level
 - (out) signal : Voice output signal (default)

*/
class VoiceBase : public pdsp::Patchable
{
public:
	VoiceBase();
	VoiceBase( int _index);
	VoiceBase(const VoiceBase & other) {}
	~VoiceBase();

	//! Add and patch a VoiceElement to this Voice
	/*!
	 Add the VoiceElement and patch trigger, pitch and outSignal.
	*/
	void addElement(VoiceElement& element);

	pdsp::Patchable & in_trig();
	pdsp::Patchable & in_pitch();

protected:
	int index = 0;
	std::vector<VoiceElement> elements;

	pdsp::PatchNode trigger;
	pdsp::PatchNode pitch;

	pdsp::Amp outSignal;
};
