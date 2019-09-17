#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "ofxImGui.h"

class ofxImGuiMIDIDevicesSelector
{
public:
	ofxImGuiMIDIDevicesSelector();
	ofxImGuiMIDIDevicesSelector(pdsp::midi::Input * input);
	~ofxImGuiMIDIDevicesSelector();

	void setPDSPMIDI(pdsp::midi::Input * input);
	void refreshDeviceList();
	std::tuple<int, string> getSelectedDevice();

	void draw();

private:
	std::vector<std::string> deviceNames;
	int	selectedDevice;
	pdsp::midi::Input * midiInput = nullptr;
};


