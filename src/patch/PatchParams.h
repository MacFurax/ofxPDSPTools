#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "ofxImGui.h"
#include "ofxXmlSettings.h"

enum class ParamTypes { None, Float, Int, Combo };
enum class ParamLayouts { NextLine, SameLine };

class ParamDesc
{
public:
  
  shared_ptr<pdsp::Parameter> pdspParameter;
  ParamTypes                  type = ParamTypes::None;
  ParamLayouts                layout = ParamLayouts::NextLine;
  vector<string>              comboOptions; // if paramType is StringList
};


class ParamGroup
{
public:
	ParamGroup() {}
	~ParamGroup() {
		_subGroups.clear();
		_params.clear();
	}

	map<string, shared_ptr<ParamGroup>> & getSubGroups();
	vector<shared_ptr<ParamDesc>> & getParams();
private:

	map<string, shared_ptr<ParamGroup>> _subGroups;
	vector<shared_ptr<ParamDesc>> _params;
};

class PatchParams
{
public:

  PatchParams();
  ~PatchParams();



  void AddParam(string fullname, float value, float minValue, float maxValue, float smoothingTime = 50.f, ParamLayouts layout = ParamLayouts::NextLine);
  shared_ptr<ParamDesc> getParamDesc(string fullname);
  shared_ptr<pdsp::Parameter> getPDSPParameter(string fullname);
  shared_ptr<ofParameterGroup> getOfParameterGroup();


private:

	shared_ptr<ParamGroup>	_rootParamGroup;

	map<string, shared_ptr<ParamDesc>>	_paramDescs;

	shared_ptr<ofParameterGroup>	_ofParameterRootGroup;
  
	ofParameter<string>	_patchVersion;
	ofParameter<string>	_patchName;
	ofParameter<string>	_patchDescription;

  

};


