#include "PatchParams.h"

// -------------------------------------------------------
PatchParams::PatchParams()
{
	_rootParamGroup = make_shared<ParamGroup>();
	_ofParameterRootGroup = make_shared<ofParameterGroup>();

	_ofParameterRootGroup->setName("patch");
	_patchVersion.set("version", "none");
	_ofParameterRootGroup->add(_patchVersion);
	_patchName.set("name", "");
	_ofParameterRootGroup->add(_patchName);
	_patchDescription.set("description", "");
	_ofParameterRootGroup->add(_patchDescription);
}

// -------------------------------------------------------
PatchParams::~PatchParams()
{
	_paramDescs.clear();
}

// -------------------------------------------------------
void PatchParams::AddParam(string fullname, float value, float minValue, float maxValue, float smoothingTime, ParamLayouts layout, ParamWidgets widget)
{
	AddParam(fullname, value, minValue, maxValue, minValue, smoothingTime, layout, widget);
}

// -------------------------------------------------------
void PatchParams::AddParam(string fullname, float value, float minValue, float maxValue, float zeroRef, float smoothingTime, ParamLayouts layout, ParamWidgets widget)
{
	vector<string> names;
	names = ofSplitString(fullname, ".");

	shared_ptr<ParamGroup> lastGroup = _rootParamGroup;
	shared_ptr<ofParameterGroup> lastOfParameterGroup = _ofParameterRootGroup;

	int tokenIndex = 0;
	for (string token : names)
	{
		if (tokenIndex == (names.size() - 1))
		{
			// this is the parameter name
			// add it to group
			//ofLogNotice() << "Parameter name:" << token;
			shared_ptr<pdsp::Parameter> param = make_shared<pdsp::Parameter>();

			shared_ptr<ParamDesc> paramDesc = make_shared<ParamDesc>();

			param->set(token, value, minValue, maxValue);
			param->enableSmoothing( smoothingTime);

			paramDesc->pdspParameter = param;
			paramDesc->layout = layout;
			paramDesc->type = ParamTypes::Float;
			paramDesc->widget = widget;
			paramDesc->zeroRef = zeroRef;

			_paramDescs[fullname] = paramDesc;
			lastGroup->getParams().push_back(paramDesc);

			lastOfParameterGroup->add(paramDesc->pdspParameter->getOFParameterFloat());

		}
		else {
			//ofLogNotice() << "Group name:" << token;

			// find or create sub group called token
			// It getOrCreateSubParamGroup create a new subGroup
			// it add it to the current group
			lastGroup = getOrCreateSubParamGroup(token, lastGroup );
			lastOfParameterGroup = getOrCreateSubOfParamGroup(token, lastOfParameterGroup);
		}
		
		tokenIndex++;
	}
}

// -------------------------------------------------------
void PatchParams::AddParam(string fullname, int value, vector<string> options, float smoothingTime, ParamLayouts layout, ParamWidgets widget)
{
	vector<string> names;
	names = ofSplitString(fullname, ".");

	shared_ptr<ParamGroup> lastGroup = _rootParamGroup;
	shared_ptr<ofParameterGroup> lastOfParameterGroup = _ofParameterRootGroup;

	int tokenIndex = 0;
	for (string token : names)
	{
		if (tokenIndex == (names.size() - 1))
		{
			// this is the parameter name
			// add it to group
			//ofLogNotice() << "Parameter name:" << token;
			shared_ptr<pdsp::Parameter> param = make_shared<pdsp::Parameter>();

			shared_ptr<ParamDesc> paramDesc = make_shared<ParamDesc>();

			param->set(token, value, 0, options.size()-1);
			param->enableSmoothing(smoothingTime);

			paramDesc->pdspParameter = param;
			paramDesc->layout = layout;
			paramDesc->type = ParamTypes::Combo;
			paramDesc->widget = widget;
			paramDesc->comboOptions = options;

			_paramDescs[fullname] = paramDesc;
			lastGroup->getParams().push_back(paramDesc);

			lastOfParameterGroup->add(paramDesc->pdspParameter->getOFParameterInt());

		}
		else {
			//ofLogNotice() << "Group name:" << token;

			// find or create sub group called token
			// It getOrCreateSubParamGroup create a new subGroup
			// it add it to the current group
			lastGroup = getOrCreateSubParamGroup(token, lastGroup);
			lastOfParameterGroup = getOrCreateSubOfParamGroup(token, lastOfParameterGroup);
		}

		tokenIndex++;
	}
}

// -------------------------------------------------------
const string & PatchParams::getName()
{
	return _patchName.get();
}

// -------------------------------------------------------
void PatchParams::setName( string name)
{
	_patchName.set(name);
}

// -------------------------------------------------------
const string & PatchParams::getDescription()
{
	return _patchDescription.get();
}

// -------------------------------------------------------
void PatchParams::setDescription( string description )
{
	_patchDescription.set(description);
}

// -------------------------------------------------------
shared_ptr<ParamGroup> PatchParams::getOrCreateSubParamGroup( string name, shared_ptr<ParamGroup> currentGroup )
{
	// check if group already exists in ParamGroup
	auto g = findSubGroup(name, currentGroup);
	if (g)
	{
		// found, return it
		return g;
	}

	// not found create it
	shared_ptr<ParamGroup> newGroup = make_shared<ParamGroup>();
	newGroup->getName() = name;
	currentGroup->getSubGroups().push_back(newGroup);
	return newGroup;
}

shared_ptr<ParamGroup> PatchParams::findSubGroup(string name, shared_ptr<ParamGroup> currentGroup)
{
	for (auto g : currentGroup->getSubGroups())
	{
		if (g->getName() == name)
		{
			return g;
		}
	}
	return  nullptr;
}

// -------------------------------------------------------
shared_ptr<ofParameterGroup> PatchParams::getOrCreateSubOfParamGroup(string name, shared_ptr<ofParameterGroup> currentGroup )
{
	// check if group already exist in ofParameterGroup
	bool found = false;
	shared_ptr<ofParameterGroup> subGroup = nullptr;
	for (auto param : *(currentGroup))
	{
		subGroup = dynamic_pointer_cast<ofParameterGroup>(param);
		if (subGroup)
		{
			if (subGroup->getName() == name)
			{
				found = true;
				break;
			}
		}
	}

	if (found)
	{
		// found, set this group as lastOne
		return subGroup;
	}
	
	// not found, create one, add it to current group
	// set lastGroup to the new  one
	shared_ptr<ofParameterGroup> newGroup = make_shared<ofParameterGroup>();
	newGroup->setName(name);
	currentGroup->add(*(newGroup));
	return newGroup;
}

// -------------------------------------------------------
shared_ptr<ofParameterGroup> PatchParams::getOfParameterGroup()
{
	return _ofParameterRootGroup;
}

// -------------------------------------------------------
const shared_ptr<ParamGroup>& PatchParams::getRootParamGroup()
{
	return _rootParamGroup;
}

// -------------------------------------------------------
shared_ptr<ParamDesc> PatchParams::getParamDesc(string fullname)
{
	auto pair = _paramDescs.find(fullname);
	if (pair != _paramDescs.end())
	{
		return pair->second;
	}
	return nullptr;
}

// -------------------------------------------------------
shared_ptr<pdsp::Parameter> PatchParams::getPDSPParameter(string fullname)
{
	shared_ptr<ParamDesc> paramDesc = getParamDesc(fullname);
	if (paramDesc != nullptr)
	{
		return paramDesc->pdspParameter;
	}
	return nullptr;
}

// -------------------------------------------------------
pdsp::Parameter & PatchParams::patch(string fullname)
{
	shared_ptr<pdsp::Parameter> p = getPDSPParameter(fullname);
	if (p == nullptr)
	{
		ofLogFatalError() << "No param called ["<< fullname <<"]";
	}
	return *(p);
}

string & ParamGroup::getName()
{
	return _name;
}

// -------------------------------------------------------
vector<shared_ptr<ParamGroup>> & ParamGroup::getSubGroups()
{
	return _subGroups;
}

// -------------------------------------------------------
vector<shared_ptr<ParamDesc>>& ParamGroup::getParams()
{
	return _params;
}
