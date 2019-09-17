#include "voiceFullFeatures.h"

VoiceFullFeatures::VoiceFullFeatures()
{
  addModuleInput("trigger", trigger); // first = default
  addModuleInput("pitch", pitch);

  addModuleOutput("signal", outSignal); // first = default


  // OSC 1
  detuneCoarse1.set(0.f);
  detuneFine1.set(0.f);
  trigger >> adsr1.in_trig();
  pitch + detuneCoarse1 + detuneFine1 >> osc1.in_pitch();

  waveForm1.resize(5);
  osc1.out_sine() >> waveForm1.input(0);
  osc1.out_triangle() >> waveForm1.input(1);
  osc1.out_saw() >> waveForm1.input(2);
  osc1.out_pulse() >> waveForm1.input(3);
  whiteNoise1 >> waveForm1.input(4);

  adsr1 >> osc1EnvAmp.in_mod();
  waveForm1 >> osc1EnvAmp;

  lfo1waveForm.resize(4);
  lfo1.out_sine() >> lfo1waveForm.input(0);
  lfo1.out_triangle() >> lfo1waveForm.input(1);
  lfo1.out_saw() >> lfo1waveForm.input(2);
  lfo1.out_square() >> lfo1waveForm.input(3);

  lfo1waveForm >> lfo1ToOSCPitchAmp;
  lfo1waveForm >> lfo1ToOSCLevelAmp;
  lfo1waveForm >> lfo1ToOSCPWAmp;

  lfo1ToOSCPitchAmp >> osc1.in_pitch();
  lfo1ToOSCLevelAmp >> osc1Level.in_mod();
  lfo1ToOSCPWAmp >> osc1.in_pw();

  osc1Level.set(1.0f);
  osc1EnvAmp >> osc1Level;
  osc1Level >> outSignal;

  // OSC 2
  // set detune to 0
  detuneCoarse2.set(0.f);
  detuneFine2.set(0.f);

  // patch external trigger to OSC ADSR 
  trigger >> adsr2.in_trig();
  // patch external pitch to osc pitch trough detune
  pitch + detuneCoarse2 + detuneFine2 >> osc2.in_pitch();

  // set and patch waveform switch
  waveForm2.resize(5);
  osc2.out_sine() >> waveForm2.input(0);
  osc2.out_triangle() >> waveForm2.input(1);
  osc2.out_saw() >> waveForm2.input(2);
  osc2.out_pulse() >> waveForm2.input(3);
  whiteNoise2 >> waveForm2.input(4);

  // patch ADSR out to osc envvelope amp mod
  adsr2 >> osc2EnvAmp.in_mod();
  // patch selected wave form to OSC output amp 
  waveForm2 >> osc2EnvAmp;

  // patch external trigger to osc2 filter ADSR 
  trigger >> osc2FilterADSR.in_trig();
  osc2FilterADSR >> osc2FilterADSRAmt >> osc2Filter.in_cutoff();

  osc2EnvAmp >> osc2Filter;
  osc2Filter >> osc2Level;
  osc2Level >> outSignal;

  outSignal.set(1.f);

}