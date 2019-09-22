#include "VoiceElement.h"

VoiceElement::VoiceElement()
{
	ofLogNotice() << "VoiceElement::VoiceElement";

	addModuleInput("level", outSignal.in_mod()); // first = default
	addModuleInput("trigger", trigger); 
	addModuleInput("pitch", pitch);
	

	addModuleOutput("signal", outSignal); // first = default
}

VoiceElement::~VoiceElement()
{
}

pdsp::Patchable & VoiceElement::out_signal()
{
	return outSignal;
}

pdsp::Patchable & VoiceElement::in_trig()
{
	return trigger;
}

pdsp::Patchable & VoiceElement::in_pitch()
{
	return pitch;
}

pdsp::Patchable & VoiceElement::in_level()
{
	return outSignal.in_mod();
}
