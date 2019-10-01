#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "ofxImGui.h"
#include "ofxXmlSettings.h"

enum class ParamTypes { None, Float, Int, Combo };
enum class ParamLayouts { NextLine, SameLine };
enum class ParamWidgets { HSlider, VSlider, Combo, Knob };

class ParamDesc
{
public:
  
  shared_ptr<pdsp::Parameter>	pdspParameter;
  ParamTypes					type = ParamTypes::None;
  ParamWidgets					widget = ParamWidgets::HSlider;
  ParamLayouts					layout = ParamLayouts::NextLine;
  vector<string>				comboOptions; // if paramType is StringList
  float							zeroRef; // centre value reference
};


class ParamGroup
{
public:
	ParamGroup() {}
	~ParamGroup() {
		_subGroups.clear();
		_params.clear();
	}

	string & getName();

	vector<shared_ptr<ParamGroup>> & getSubGroups();
	vector<shared_ptr<ParamDesc>> & getParams();
private:
	string _name = "none";
	vector<shared_ptr<ParamGroup>> _subGroups;
	vector<shared_ptr<ParamDesc>> _params;
};

class PatchParams
{
public:

  PatchParams();
  ~PatchParams();

  void AddParam(string fullname, float value, float minValue, float maxValue, float smoothingTime = 50.f, ParamLayouts layout = ParamLayouts::NextLine, ParamWidgets widget = ParamWidgets::Knob);
  void AddParam(string fullname, float value, float minValue, float maxValue, float zeroRef, float smoothingTime = 50.f, ParamLayouts layout = ParamLayouts::NextLine, ParamWidgets widget = ParamWidgets::Knob);
  void AddParam(string fullname, int value, vector<string> options, float smoothingTime = 50.f, ParamLayouts layout = ParamLayouts::NextLine, ParamWidgets widget = ParamWidgets::Combo);
  
  const string & getName();
  void setName( string name );
  const string & getDescription();
  void setDescription( string description);

  shared_ptr<ParamDesc> getParamDesc(string fullname);
  shared_ptr<pdsp::Parameter> getPDSPParameter(string fullname);
  pdsp::Parameter & patch(string fullname);
  shared_ptr<ofParameterGroup> getOfParameterGroup();

  const shared_ptr<ParamGroup>& getRootParamGroup();

private:

	shared_ptr<ParamGroup> getOrCreateSubParamGroup(string name, shared_ptr<ParamGroup> currentGroup);
	shared_ptr<ParamGroup> PatchParams::findSubGroup(string name, shared_ptr<ParamGroup> currentGroup);
	shared_ptr<ofParameterGroup> getOrCreateSubOfParamGroup(string name, shared_ptr<ofParameterGroup> currentGroup);

	shared_ptr<ParamGroup>	_rootParamGroup;

	map<string, shared_ptr<ParamDesc>>	_paramDescs;

	shared_ptr<ofParameterGroup>	_ofParameterRootGroup;
  
	ofParameter<string>	_patchVersion;
	ofParameter<string>	_patchName;
	ofParameter<string>	_patchDescription;

  

};


