#pragma once

#include "ofxPDSP.h"
#include "VoiceBase.h"

class SynthBase : public pdsp::Patchable
{
public:

private:
	std::vector<VoiceBase> voices;

};
