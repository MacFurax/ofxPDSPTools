#include "ofxImGuiMIDIDevicesSelector.h"

// ---------------------------------------------------------
ofxImGuiMIDIDevicesSelector::ofxImGuiMIDIDevicesSelector()
{
	
}

// ---------------------------------------------------------
ofxImGuiMIDIDevicesSelector::ofxImGuiMIDIDevicesSelector(pdsp::midi::Input * input) : ofxImGuiMIDIDevicesSelector()
{
	midiInput = input;
	refreshDeviceList();
}

// ---------------------------------------------------------
ofxImGuiMIDIDevicesSelector::~ofxImGuiMIDIDevicesSelector()
{
}

// ---------------------------------------------------------
void ofxImGuiMIDIDevicesSelector::setPDSPMIDI(pdsp::midi::Input * input)
{
	midiInput = input;
	refreshDeviceList();
}

// ---------------------------------------------------------
void ofxImGuiMIDIDevicesSelector::refreshDeviceList()
{
	deviceNames = midiInput->getPortList();
}

// ---------------------------------------------------------
std::tuple<int, string> ofxImGuiMIDIDevicesSelector::getSelectedDevice()
{
	return std::tuple<int, string>(selectedDevice, deviceNames[selectedDevice]);
}

// ---------------------------------------------------------
void ofxImGuiMIDIDevicesSelector::draw()
{
	auto mainSettings = ofxImGui::Settings();

	ofxImGui::BeginWindow("MIDI devices", mainSettings, false);

	if (deviceNames.size() > 0)
	{
		if (ofxImGui::VectorCombo("MIDI IN", &selectedDevice, deviceNames))
		{
			midiInput->closePort();
			midiInput->openPort(selectedDevice);
		}
	}
	else
	{
		ImGui::Text("No MIDI IN interfaces available");
	}
	if (ImGui::Button("Refresh device list"))
	{
		refreshDeviceList();
	}


	ofxImGui::EndWindow(mainSettings);
}
