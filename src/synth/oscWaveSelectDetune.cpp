#include "oscWaveSelectDetune.h"

OscWaveSelectDetune::OscWaveSelectDetune()
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

  osc1Level.set(1.0f);
  osc1EnvAmp >> osc1Level;
  osc1Level >> outSignal;
  
  // OSC 2
  detuneCoarse2.set(0.f);
  detuneFine2.set(0.f);
  trigger >> adsr2.in_trig();
  pitch + detuneCoarse2 + detuneFine2 >> osc2.in_pitch();

  waveForm2.resize(5);
  osc2.out_sine() >> waveForm2.input(0);
  osc2.out_triangle() >> waveForm2.input(1);
  osc2.out_saw() >> waveForm2.input(2);
  osc2.out_pulse() >> waveForm2.input(3);
  whiteNoise2 >> waveForm2.input(4);

  adsr2 >> osc2EnvAmp.in_mod();
  waveForm2 >> osc2EnvAmp;

  osc2EnvAmp >> osc2Level;
  osc2Level >> outSignal;

  
  outSignal.set(1.f);

}