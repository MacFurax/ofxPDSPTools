#include "ofxImGuiLoadSavePatchs.h"

// ---------------------------------------------------------
ofxImGuiLoadSavePatchs::ofxImGuiLoadSavePatchs()
{
	patchStorage.reloadPatchsFileList();
}

// ---------------------------------------------------------
ofxImGuiLoadSavePatchs::ofxImGuiLoadSavePatchs(PatchParams * toSave, string baseFolder, string extention)
{
	patchParams = toSave;
	patchStorage.setup(baseFolder, extention);
	patchStorage.reloadPatchsFileList();
	
}

// ---------------------------------------------------------
ofxImGuiLoadSavePatchs::~ofxImGuiLoadSavePatchs()
{
}

// ---------------------------------------------------------
void ofxImGuiLoadSavePatchs::setup(PatchParams * toSave, string baseFolder, string extention)
{
	patchParams = toSave;
	patchStorage.setup(baseFolder, extention);
	patchStorage.reloadPatchsFileList();
}

void ofxImGuiLoadSavePatchs::setPatchParams(PatchParams * toSave)
{
	patchParams = toSave;
}

// ---------------------------------------------------------
void ofxImGuiLoadSavePatchs::draw()
{
	//auto mainSettings = ofxImGui::Settings();

	//ofxImGui::BeginWindow("Patchs", mainSettings, false);
	//if (patchStorage.numFiles() > 0)
	//{
	//	if (ofxImGui::VectorCombo("Patchs", &selectedPatch, patchStorage.patcheNames()))
	//	{
	//		// nothing yet
	//	}
	//	if (ImGui::Button("Load"))
	//	{
	//		// load current selected patchs
	//		patchStorage.Load(selectedPatch, patchParams->getParameterGroup());
	//		strcpy(name, patchParams->name().get().c_str());
	//		strcpy(description, patchParams->description().get().c_str());
	//	}
	//}
	//else
	//{
	//	ImGui::Text("No patches available");
	//}
	//ImGui::SameLine();
	//if (ImGui::Button("Refresh"))
	//{
	//	patchStorage.reloadPatchsFileList();
	//}

	//ImGui::InputText("Name", name, IM_ARRAYSIZE(name));
	//ImGui::InputTextMultiline("Description", description, IM_ARRAYSIZE(description));
	//if (ImGui::Button("Save"))
	//{
	//	if (patchStorage.numFiles() > 0)
	//	{
	//		
	//		if (patchParams->name().get() != name)
	//		{
	//			// name was changed, create a new patch
	//			patchParams->name().set(name);
	//			patchParams->description().set(description);
	//			patchStorage.Save(patchStorage.buildFullFilename(name), patchParams->getParameterGroup());
	//			patchStorage.reloadPatchsFileList(); // reload
	//			selectPatchByName(name);
	//		}
	//		else
	//		{
	//			// name was not changed, override current patch
	//			patchParams->name().set(name);
	//			patchParams->description().set(description);
	//			patchStorage.Save(selectedPatch, patchParams->getParameterGroup());
	//		}
	//	}
	//	else
	//	{
	//		// create new patch
	//		patchParams->name().set(name);
	//		patchParams->description().set(description);
	//		patchStorage.Save(patchStorage.buildFullFilename(name), patchParams->getParameterGroup());
	//		patchStorage.reloadPatchsFileList(); // reload 
	//		selectPatchByName(name);
	//	}
	//}


	//ofxImGui::EndWindow(mainSettings);
}

void ofxImGuiLoadSavePatchs::selectPatchByName(string name)
{
	int newIndex = 0;
	for (auto patchName : patchStorage.patcheNames())
	{
		if (patchName.find(name+".") == 0)
		{
			selectedPatch = newIndex;
		}
		newIndex++;
	}
}
