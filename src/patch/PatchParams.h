#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "ofxImGui.h"
#include "ofxXmlSettings.h"

class ParamDesc
{
public:
  enum ParamTypes { None, Float, Int, Combo };
  enum Layouts    { NextLine, SameLine};
  shared_ptr<pdsp::Parameter> pdspParameter;
  ParamTypes                  type = ParamTypes::None;
  Layouts                     layout = Layouts::NextLine;
  vector<string>              comboOptions; // if paramType is StringList
};


class PatchParams
{
public:

  PatchParams();
  ~PatchParams();

  void AddParam(string name, float value, float minValue, float maxValue, float smoothingTime = 50.f, ParamDesc::Layouts layout = ParamDesc::Layouts::NextLine);
  void AddParam(string name, int value, int minValue, int maxValue);
  void AddParam(string name, int value, vector<string> values);

  pdsp::Patchable Patch(string name);

  // set param value
  void Set(string name, int value);
  void Set(string name, float value);

  shared_ptr<ParamDesc>       getParamDesc(string name);
  shared_ptr<ParamDesc>       getParamDesc(string groupName, string paramName);
  shared_ptr<pdsp::Parameter> getPDSPParameter(string name);
  ofParameter<float>&         getOfParameterFloat(string name);
  ofParameter<int>&           getOfParameterInt(string name);

  ofParameter<string>&        version();
  ofParameter<string>&        name();
  ofParameter<string>&        description();
  
  bool Save(string path);
  bool Load(string path);

  ofParameterGroup& getParameterGroup();

//private:

//private:

  void Store(string name, string groupName, shared_ptr<ParamDesc> paramDesc);
  tuple<string, string> SplitParamName(string fullParamName);
  
  ofParameterGroup                          rootGroup;
  
  ofParameter<string>                       patchVersion;
  ofParameter<string>                       patchName;
  ofParameter<string>                       patchDescription;

  vector<shared_ptr<ParamDesc>>             parameters;
  vector<shared_ptr<ofParameterGroup>>      childsGroups;
  map<string, shared_ptr<ofParameterGroup>> groupsByName;
  map<string, shared_ptr<ParamDesc>>        parametersByName;
  map<string, vector<string>>               stringLists;

};


