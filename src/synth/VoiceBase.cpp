#include "VoiceBase.h"

VoiceBase::VoiceBase()
{
	addModuleInput("level", outSignal.in_mod()); // first = default
	addModuleInput("trigger", trigger); 
	addModuleInput("pitch", pitch);
	

	addModuleOutput("signal", outSignal); // first = default

	1.0f >> outSignal.in_mod();

}

VoiceBase::VoiceBase(int _index) : VoiceBase()
{
	index = _index;
}

VoiceBase::~VoiceBase()
{
}

void VoiceBase::addElement(VoiceElement& element)
{
	elements.push_back(element);

	trigger >> element.in("trigger");
	pitch >> element.in("pitch");

	element >> outSignal;
}

pdsp::Patchable & VoiceBase::in_trig()
{
	return trigger;
}

pdsp::Patchable & VoiceBase::in_pitch()
{
	return pitch;
}

