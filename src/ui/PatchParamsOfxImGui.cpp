#include "PatchParamsOfxImGui.h"

PatchParamsOfxImGui::PatchParamsOfxImGui()
{
}

PatchParamsOfxImGui::PatchParamsOfxImGui(PatchParams& pp)
{
  this->pp = pp;
}

PatchParamsOfxImGui::~PatchParamsOfxImGui()
{
}

void PatchParamsOfxImGui::setPatchParams(PatchParams& pp)
{
  this->pp = pp;
}

void PatchParamsOfxImGui::Draw()
{
  auto mainSettings = ofxImGui::Settings();
  // create windows and params from PatchParameters
  for (auto child : pp.childsGroups)
  {
    string groupName = child->getName();
    ofxImGui::BeginWindow(groupName, mainSettings, false);
    for (int x = 0; x < child->size(); x++)
    {
      ofAbstractParameter& param = child->get(x);
      string paramName = param.getName();
      shared_ptr<ParamDesc> paramDesc = pp.getParamDesc(groupName, paramName);
      if (paramDesc != nullptr)
      {

        if (paramDesc->layout == ParamDesc::Layouts::SameLine)
        {
          ImGui::SameLine();
        }

        switch (paramDesc->type)
        {
        case ParamDesc::ParamTypes::Float:
          ofxImGui::AddKnob(paramDesc->pdspParameter->getOFParameterFloat());
          break;
        case ParamDesc::ParamTypes::Int:
          break;
        case ParamDesc::ParamTypes::Combo:
          ofxImGui::AddCombo(paramDesc->pdspParameter->getOFParameterInt(), paramDesc->comboOptions);
          break;
        default:

          ofLogError() << "ofApp::draw - Unknow ParamDesc type";
        }
      }
      else
      {
        ofLogError() << "ofApp::draw - No ParamDesc for [" + groupName + "." + paramName + "]";
      }
    }
    ofxImGui::EndWindow(mainSettings);
  }
}
