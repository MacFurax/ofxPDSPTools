#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
//! Base class for Voice element
/*!

A VoiceElement is a component of a voice that generate 
a audio signal. It provide more elaborated generator then a single OSC.
It can be a OSC with waveform selector and an LFO that can be applyed 
on pulse width, level or pitch.

It come with the following input/ouput:
	- (in) trigger : to trigger the VoiceElement (default)
	- (in) pitch : set VoiceElement pitch
	- (in) level : set VoiceElement out level
	- (out) signal : outpu audio signal of the VoiceElement (default)

*/
class VoiceElement : public pdsp::Patchable
{
public:
	VoiceElement();
	VoiceElement(const VoiceElement& other) {}
	~VoiceElement();

	pdsp::Patchable & out_signal();
	pdsp::Patchable & in_trig();
	pdsp::Patchable & in_pitch();
	pdsp::Patchable & in_level();

protected:
	pdsp::PatchNode trigger;
	pdsp::PatchNode pitch;

	pdsp::Amp		outSignal;
};
