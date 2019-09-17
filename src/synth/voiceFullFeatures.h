
// voiceFullFeatures.h
// ofxPDSP_More based on ofxPDSP by Nicola Pisanti
// https://github.com/npisanti/ofxPDSP
// Constant Dupuis, MIT Licence, 2019
//
// Full featured voice with:
// - two oscillatores with detune
// - wave form selector
// - ADSR
// - LFO done on OSC 1
// - Filter 
// - Filter done on OSC 2
//

#pragma once

#include "ofxPDSP.h"

class VoiceFullFeatures : public pdsp::Patchable
{
public:
  VoiceFullFeatures();

  // OSC 1 nodes
  pdsp::VAOscillator    osc1;
  pdsp::WhiteNoise      whiteNoise1;
  pdsp::ADSR            adsr1;
  pdsp::Amp             osc1EnvAmp;
  pdsp::Switch          waveForm1;
  pdsp::PatchNode       detuneCoarse1;
  pdsp::PatchNode       detuneFine1;
  pdsp::Amp             osc1Level;
  // OSC 1 LFO
  pdsp::LFO             lfo1;
  pdsp::Switch          lfo1waveForm;
  pdsp::Amp             lfo1ToOSCPitchAmp;
  pdsp::Amp             lfo1ToOSCLevelAmp;
  pdsp::Amp             lfo1ToOSCPWAmp;



  // OSC 2 nodes
  pdsp::VAOscillator    osc2;
  pdsp::WhiteNoise      whiteNoise2;
  pdsp::ADSR            adsr2;
  pdsp::Amp             osc2EnvAmp;
  pdsp::Switch          waveForm2;
  pdsp::PatchNode       detuneCoarse2;
  pdsp::PatchNode       detuneFine2;
  pdsp::Amp             osc2Level;

  // OSC 2 Filter ADSR
  pdsp::SVFilter        osc2Filter;
  pdsp::ADSR            osc2FilterADSR;
  pdsp::Amp             osc2FilterADSRAmt;


  // voice outut amp
  pdsp::Amp             outSignal;

private:
  pdsp::PatchNode       trigger;
  pdsp::PatchNode       pitch;


};


