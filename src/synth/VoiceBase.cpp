#include "VoiceBase.h"

VoiceBase::VoiceBase()
{
	//ofLogNotice() << "VoiceBase::VoiceBase";

	addModuleInput("level", outSignal.in_mod()); // first = default
	addModuleInput("trigger", trigger); 
	addModuleInput("pitch", pitch);
	addModuleInput("modulation", modulation);

	addModuleOutput("signal", outSignal); // first = default

}

VoiceBase::VoiceBase(int _index) : VoiceBase()
{
	index = _index;
}

VoiceBase::~VoiceBase()
{
}

void VoiceBase::setElementCount(int count)
{
	elementCount = count;
}

void VoiceBase::addElement(VoiceElement* element)
{
	elements.push_back(element);

	trigger >> element->in_trig();
	pitch >> element->in_pitch();
	modulation >> element->in_modulation();

	element->out_signal() * (1.0f/(float)elementCount)>> outSignal;
}

VoiceElement * VoiceBase::getVoiceElementAt(int index)
{
	if (index >= elements.size())
	{
		return nullptr;
	}

	return elements[index];
}

int VoiceBase::getElementCount()
{
	return elements.size();
}

pdsp::Patchable & VoiceBase::in_trig()
{
	return trigger;
}

pdsp::Patchable & VoiceBase::in_pitch()
{
	return pitch;
}

pdsp::Patchable & VoiceBase::in_modulation()
{
	return modulation;
}

pdsp::Patchable & VoiceBase::out_signal()
{
	return outSignal;
}

