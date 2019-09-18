#include "VoiceElement.h"

VoiceElement::VoiceElement()
{
	addModuleInput("trigger", trigger); // first = default
	addModuleInput("pitch", pitch);
	addModuleInput("level", outSignal.in_mod());

	addModuleOutput("signal", outSignal); // first = default
	1.0f >> outSignal.in_mod();
}

VoiceElement::~VoiceElement()
{
}
