#include "VoiceElement.h"

VoiceElement::VoiceElement()
{
	ofLogNotice() << "VoiceElement::VoiceElement";

	addModuleInput("level", outSignal.in_mod()); // first = default
	addModuleInput("trigger", trigger); 
	addModuleInput("pitch", pitch);
	

	addModuleOutput("signal", outSignal); // first = default

	1.0f >> outSignal.in_mod();
}

VoiceElement::~VoiceElement()
{
}

pdsp::Patchable & VoiceElement::signal()
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
