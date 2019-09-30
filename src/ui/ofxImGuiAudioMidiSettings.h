#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxMidi.h"

class ofxImGuiAudioMidiSettings
{
public:
	ofxImGuiAudioMidiSettings();
	~ofxImGuiAudioMidiSettings();

	int selectedAudioOutDevice();
	int selectedMIDIInDevice();

	void refreshAudioDeviceList();
	void refreshMIDIDeviceList();

private:
	int _selectedAudioOutDevice = -1;
	int _selectedMIDIInDevice = -1;

	ofxMidiIn				_midiIn;

	vector<string>			_midiInDeviceNames;

	ofSoundStream			_audioInterfaces;

	vector<ofSoundDevice>	_soundDevices;
	vector<string>			_soundDeviceNames;

};
