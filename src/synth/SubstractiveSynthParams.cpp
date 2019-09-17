#include "SubstractiveSynthParams.h"

SubstractiveSynthParams::SubstractiveSynthParams() : PatchParams()
{
  
  AddParam("SYNTH.Filter Type", 0, {"LowPass", "BandPass", "HighPass", "Notch"});
  AddParam("SYNTH.Filter Cutoff", 180.0f, 0.0f, 180.0f, 100.f); // because filter type is default to LowPass, set cutoff on higher frequencey (pitch)
  AddParam("SYNTH.Filter Reso", 0.0f, 0.0f, 1.0f);

  AddParam("SYNTH.Filter LFO WF", 0.0f, {"sine","triangle", "saw", "square"});
  AddParam("SYNTH.Filter LFO Freq", 1.0f, 0.0f, 30.0f);
  AddParam("SYNTH.Filter LFO Amp", 0.0f, 0.0f, 40.0f);


  AddParam("OSC1.Detune", 0.0f, -12.0f, 12.0f);
  AddParam("OSC1.Fine", 0.0f, -1.0f, 1.0f, 50.f, ParamDesc::Layouts::SameLine);
  AddParam("OSC1.Level", 0.5f, 0.0f, 1.0f, 50.f, ParamDesc::Layouts::SameLine);
  AddParam("OSC1.PW", 0.5f, 0.1f, 0.9f, 50.f, ParamDesc::Layouts::SameLine);

  AddParam("OSC1.Sine", 1.0f, 0.0f, 1.0f);
  AddParam("OSC1.Triangle", 0.0f, 0.0f, 1.0f, 50.f, ParamDesc::Layouts::SameLine);
  AddParam("OSC1.Saw", 0.0f, 0.0f, 1.0f, 50.f, ParamDesc::Layouts::SameLine);
  AddParam("OSC1.Pulse", 0.0f, 0.0f, 1.0f, 50.f, ParamDesc::Layouts::SameLine);
  AddParam("OSC1.Noise", 0.0f, 0.0f, 0.5f, 50.f, ParamDesc::Layouts::SameLine);

  AddParam("OSC1.A", 10.0f, 0.0f, 3000.0f);
  AddParam("OSC1.D", 200.0f, 0.0f, 3000.0f, 50.f, ParamDesc::Layouts::SameLine);
  AddParam("OSC1.S", 0.5f, 0.0f, 1.0f, 50.f, ParamDesc::Layouts::SameLine);
  AddParam("OSC1.R", 400.0f, 0.0f, 3000.0f, 50.f, ParamDesc::Layouts::SameLine);

  AddParam("OSC1.LFO Sine", 1.0f, 0.0f, 1.0f);
  AddParam("OSC1.LFO Triangle", 0.0f, 0.0f, 1.0f, 50.f, ParamDesc::Layouts::SameLine);
  AddParam("OSC1.LFO Saw", 0.0f, 0.0f, 1.0f, 50.f, ParamDesc::Layouts::SameLine);
  AddParam("OSC1.LFO Square", 0.0f, 0.0f, 1.0f, 50.f, ParamDesc::Layouts::SameLine);

  AddParam("OSC1.LFO Freq", 1.0f, 0.0f, 30.0f);
  AddParam("OSC1.LFO Pitch", 0.0f, 0.0f, 20.0f, 50.f, ParamDesc::Layouts::SameLine);
  AddParam("OSC1.LFO Level", 0.0f, 0.0f, 1.0f, 50.f, ParamDesc::Layouts::SameLine);
  AddParam("OSC1.LFO PW", 0.0f, 0.0f, 0.5f, 50.f, ParamDesc::Layouts::SameLine);
}

SubstractiveSynthParams::~SubstractiveSynthParams()
{

}
