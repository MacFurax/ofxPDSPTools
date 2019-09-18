#include "VoiceBase.h"

VoiceBase::VoiceBase()
{
	addModuleInput("trigger", trigger); // first = default
	addModuleInput("pitch", pitch);
	addModuleInput("level", outSignal.in_mod());

	addModuleOutput("signal", outSignal); // first = default
	1.0f >> outSignal.in_mod();
}

VoiceBase::~VoiceBase()
{
}

void VoiceBase::addElement(shared_ptr<VoiceElement> element)
{
	elements.push_back(element);

	trigger >> element->in("trigger");
	pitch >> element->in("pitch");

	*(element) >> outSignal;
}
