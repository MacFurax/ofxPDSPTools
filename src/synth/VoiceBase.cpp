#include "VoiceBase.h"

VoiceBase::VoiceBase()
{
	//ofLogNotice() << "VoiceBase::VoiceBase";

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

void VoiceBase::addElement(VoiceElement* element)
{
	elements.push_back(element);

	trigger >> element->in_trig();
	pitch >> element->in_pitch();
	//voiceElementLevel >> element->in_level();

	element->out_signal() >> outSignal;
}

VoiceElement * VoiceBase::getVoiceElementAt(int index)
{
	if (index >= elements.size())
	{
		return nullptr;
	}

	return elements[index];
}

pdsp::Patchable & VoiceBase::in_trig()
{
	return trigger;
}

pdsp::Patchable & VoiceBase::in_pitch()
{
	return pitch;
}

pdsp::Patchable & VoiceBase::out_signal()
{
	return outSignal;
}

