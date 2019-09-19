#include "ofxImGuiPatchParamsUI.h"

ofxImGuiPatchParamsUI::ofxImGuiPatchParamsUI()
{
}

ofxImGuiPatchParamsUI::ofxImGuiPatchParamsUI(PatchParams& patchParam)
{
	_patchParams = patchParam;
}

ofxImGuiPatchParamsUI::~ofxImGuiPatchParamsUI()
{
}

void ofxImGuiPatchParamsUI::setPatchParams( PatchParams& patchParam)
{
	_patchParams = patchParam;
}

void ofxImGuiPatchParamsUI::draw()
{
	auto mainSettings = ofxImGui::Settings();

	for (auto subGroup : _patchParams.getRootParamGroup()->getSubGroups())
	{
		ofxImGui::BeginWindow(subGroup->getName(), mainSettings, false);

		drawParams(subGroup->getParams());
		drawGroups(subGroup);

		ofxImGui::EndWindow(mainSettings);
	}
}

void ofxImGuiPatchParamsUI::drawParams(vector<shared_ptr<ParamDesc>> & params)
{
	for (auto param : params)
	{
		if (param->layout == ParamLayouts::SameLine)
		{
			ImGui::SameLine();
		}

		switch (param->widget)
		{

		case ParamWidgets::Combo:
			ofxImGui::AddCombo(
				param->pdspParameter->getOFParameterInt(),
				param->comboOptions
			);
			break;

		case ParamWidgets::Knob:
			ofxImGui::AddKnob(
				param->pdspParameter->getOFParameterFloat()
			);
			break;

		case ParamWidgets::HSlider:
			ofLogError() << "Drawing HSlider not yet implemented";
				break;

		case ParamWidgets::VSlider:
			ofLogError() << "Drawing VSlider not yet implemented";

			break;
		default:
			ofLogError() << "Unknown widget type " << static_cast<int>(param->widget);
		}
	}
}

void ofxImGuiPatchParamsUI::drawGroups(shared_ptr<ParamGroup>& groups)
{
	for (auto subGroup : groups->getSubGroups())
	{
		if (ImGui::CollapsingHeader(subGroup->getName().c_str(), ImGuiTreeNodeFlags_DefaultOpen))
		{
			drawParams(subGroup->getParams());
			drawGroups(subGroup);
		}
	}
}
