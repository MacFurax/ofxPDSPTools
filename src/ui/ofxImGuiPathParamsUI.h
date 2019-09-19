#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "PatchParams.h"

/*! \brief Class to draw PatchParams using ofxImgui (ImGui)

This class take an PatchParam as input and will draw UI to control 
the patch parameters.

Root level group will produce window, all shild group will produce
a seperator.

*/
class ofxImGuiPatchParamsUI
{
	public:
		ofxImGuiPatchParamsUI();
		ofxImGuiPatchParamsUI( PatchParams& patchParam);
		~ofxImGuiPatchParamsUI();

		void setPatchParams(PatchParams& patchParam);
		
		void draw();

	private:

		void drawParams(vector<shared_ptr<ParamDesc>> & params);
		void drawGroups(shared_ptr<ParamGroup> & groups);

		PatchParams _patchParams;
};