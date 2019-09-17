#pragma once

//#include "ofMain.h"
//#include "ofxPDSP.h"
//#include "ofxImGui.h"
//#include "ofxXmlSettings.h"

#include "PatchParams.h"

class PatchParamsOfxImGui
{
public:
  PatchParamsOfxImGui();
  PatchParamsOfxImGui(PatchParams& pp);
  ~PatchParamsOfxImGui();

  void setPatchParams(PatchParams& pp);
  void Draw();

private:
  PatchParams pp;
};