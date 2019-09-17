#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "PatchParams.h"
#include "PatchFilesStore.h"

class ofxImGuiLoadSavePatchs
{
	public:
		ofxImGuiLoadSavePatchs();
		ofxImGuiLoadSavePatchs(PatchParams * toSave, string baseFolder = "./patches", string extention ="xml");
		~ofxImGuiLoadSavePatchs();

		void setup(PatchParams * toSave, string baseFolder = "./patches", string extention = "xml");
		void setPatchParams(PatchParams * toSave);
		void draw();

	private:
		void selectPatchByName(string name);
		PatchFilesStore	patchStorage;
		PatchParams * patchParams = nullptr;
		int  selectedPatch = 0;
		char name[512];
		char description[1024];

};
