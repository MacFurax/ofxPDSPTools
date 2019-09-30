#include "ofxImGuiAudioMidiSettings.h"

ofxImGuiAudioMidiSettings::ofxImGuiAudioMidiSettings()
{
	refreshAudioDeviceList();
	refreshMIDIDeviceList();
}

ofxImGuiAudioMidiSettings::~ofxImGuiAudioMidiSettings()
{

}

int ofxImGuiAudioMidiSettings::selectedAudioOutDevice()
{
	return _selectedAudioOutDevice;
}

int ofxImGuiAudioMidiSettings::selectedMIDIInDevice()
{
	return _selectedMIDIInDevice;
}

void ofxImGuiAudioMidiSettings::refreshAudioDeviceList()
{
	_soundDevices = _audioInterfaces.getDeviceList(ofSoundDevice::Api::MS_WASAPI);

	_soundDeviceNames.clear();

	if (_soundDevices.size() > 0)
	{
		int devId = 0;
		for (auto dev : _soundDevices)
		{
			if (dev.isDefaultOutput)
			{
				_selectedAudioOutDevice = devId;
			}

			stringstream buildName;
			buildName << dev.name;
			buildName << " #" << devId << " In(" << dev.inputChannels << ")" 
					  << (dev.isDefaultInput?"Def":"") << ", Out("<< dev.outputChannels << ")" 
					  << (dev.isDefaultOutput?"Def":"");

			_soundDeviceNames.push_back(buildName.str());

			devId++;
		}
	} else {
		_selectedAudioOutDevice = -1;
	}

}

void ofxImGuiAudioMidiSettings::refreshMIDIDeviceList()
{
	_midiInDeviceNames = _midiIn.getInPortList();

	if (_midiInDeviceNames.size() > 0)
	{
		_selectedMIDIInDevice = 0;
	} else {
		_selectedMIDIInDevice = -1;
	}
}
