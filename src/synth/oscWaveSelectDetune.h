#pragma once

#include "ofxPDSP.h"

class OscWaveSelectDetune : public pdsp::Patchable
{
public:
  OscWaveSelectDetune();

  // OSC 1 nodes
  pdsp::VAOscillator    osc1;
  pdsp::WhiteNoise      whiteNoise1;
  pdsp::ADSR            adsr1;
  pdsp::Amp             osc1EnvAmp;
  pdsp::Switch          waveForm1;
  pdsp::PatchNode       detuneCoarse1;
  pdsp::PatchNode       detuneFine1;
  pdsp::Amp             osc1Level;
  
  
  // OSC 2 nodes
  pdsp::VAOscillator    osc2;
  pdsp::WhiteNoise      whiteNoise2;
  pdsp::ADSR            adsr2;
  pdsp::Amp             osc2EnvAmp;
  pdsp::Switch          waveForm2;
  pdsp::PatchNode       detuneCoarse2;
  pdsp::PatchNode       detuneFine2;
  pdsp::Amp             osc2Level;

  // voice outut amp
  pdsp::Amp             outSignal;

private:
  pdsp::PatchNode       trigger;
  pdsp::PatchNode       pitch;

  
}; 